//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
//----------------------------------------------------------------------
/*!\file    rrlib/util/fstream/fileno.hpp
 *
 * \author  Tobias Foehst
 *
 * \date    2010-07-29
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <cstdio>
#include <fstream>
#include <cerrno>

#if defined(__GLIBCXX__) || (defined(__GLIBCPP__) && __GLIBCPP__>=20020514)  // GCC >= 3.1.0
# include <ext/stdio_filebuf.h>
#endif
#if defined(__GLIBCXX__) // GCC >= 3.4.0
# include <ext/stdio_sync_filebuf.h>
#endif

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace util
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

namespace
{

template <typename charT, typename traits>
inline int fileno_hack(std::basic_streambuf<charT, traits> *stream_buffer)
{
  // Some C++ runtime libraries shipped with ancient GCC, Sun Pro,
  // Sun WS/Forte 5/6, Compaq C++ supported non-standard file descriptor
  // access basic_filebuf<>::fd().  Alas, starting from GCC 3.1, the GNU C++
  // runtime removes all non-standard std::filebuf methods and provides an
  // extension template class __gnu_cxx::stdio_filebuf on all systems where
  // that appears to make sense (i.e. at least all Unix systems).  Starting
  // from GCC 3.4, there is an __gnu_cxx::stdio_sync_filebuf, in addition.
  // Sorry, darling, I must get brutal to fetch the darn file descriptor!
  // Please complain to your compiler/libstdc++ vendor...
#if defined(__GLIBCXX__) || defined(__GLIBCPP__)
  // OK, stop reading here, because it's getting obscene.  Cross fingers!
# if defined(__GLIBCXX__)  // >= GCC 3.4.0
  // This applies to cin, cout and cerr when not synced with stdio:
  typedef __gnu_cxx::stdio_filebuf<charT, traits> unix_filebuf_t;
  unix_filebuf_t *fbuf = dynamic_cast<unix_filebuf_t *>(stream_buffer);
  if (fbuf != NULL)
  {
    return fbuf->fd();
  }

  // This applies to filestreams:
  typedef std::basic_filebuf<charT, traits> filebuf_t;
  filebuf_t *bbuf = dynamic_cast<filebuf_t *>(stream_buffer);
  if (bbuf != NULL)
  {
    // This subclass is only there for accessing the FILE*.  Ouuwww, sucks!
    struct my_filebuf : public std::basic_filebuf<charT, traits>
    {
      int fd()
      {
        return this->_M_file.fd();
      }
    };
    return static_cast<my_filebuf *>(bbuf)->fd();
  }

  // This applies to cin, cout and cerr when synced with stdio:
  typedef __gnu_cxx::stdio_sync_filebuf<charT, traits> sync_filebuf_t;
  sync_filebuf_t *sbuf = dynamic_cast<sync_filebuf_t *>(stream_buffer);
  if (sbuf != NULL)
  {
#  if (__GLIBCXX__<20040906) // GCC < 3.4.2
    // This subclass is only there for accessing the FILE*.
    // See GCC PR#14600 and PR#16411.
    struct my_filebuf : public sync_filebuf_t
    {
      my_filebuf();  // Dummy ctor keeps the compiler happy.
      // Note: stdio_sync_filebuf has a FILE* as its first (but private)
      // member variable.  However, it is derived from basic_streambuf<>
      // and the FILE* is the first non-inherited member variable.
      FILE* c_file()
      {
        return *(FILE **)((char*)this + sizeof(std::basic_streambuf<charT, traits>));
      }
    };
    return ::fileno(static_cast<my_filebuf *>(sbuf)->c_file());
#  else
    return ::fileno(sbuf->file());
#  endif
  }
# else  // GCC < 3.4.0 used __GLIBCPP__
#  if (__GLIBCPP__>=20020514)  // GCC >= 3.1.0
  // This applies to cin, cout and cerr:
  typedef __gnu_cxx::stdio_filebuf<charT, traits> unix_filebuf_t;
  unix_filebuf_t *buf = dynamic_cast<unix_filebuf_t *>(stream_buffer);
  if (buf != NULL)
  {
    return buf->fd();
  }

  // This applies to filestreams:
  typedef std::basic_filebuf<charT, traits> filebuf_t;
  filebuf_t *bbuf = dynamic_cast<filebuf_t *>(stream.rdbuf());
  if (bbuf != NULL)
  {
    // This subclass is only there for accessing the FILE*.  Ouuwww, sucks!
    struct my_filebuf : public std::basic_filebuf<charT, traits>
    {
      // Note: _M_file is of type __basic_file<char> which has a
      // FILE* as its first (but private) member variable.
      FILE *c_file()
      {
        return *(FILE **)(&this->_M_file);
      }
    };
    FILE *c_file = static_cast<my_filebuf*>(bbuf)->c_file();
    if (c_file != NULL)    // Could be NULL for failed ifstreams.
    {
      return ::fileno(c_file);
    }
  }
#  else  // GCC 3.0.x
  typedef std::basic_filebuf<charT, traits> filebuf_t;
  filebuf_t *fbuf = dynamic_cast<filebuf_t *>(stream_buffer);
  if (fbuf != NULL)
  {
    struct my_filebuf : public filebuf_t
    {
      // Note: basic_filebuf<charT, traits> has a __basic_file<charT>* as
      // its first (but private) member variable.  Since it is derived
      // from basic_streambuf<charT, traits> we can guess its offset.
      // __basic_file<charT> in turn has a FILE* as its first (but
      // private) member variable.  Get it by brute force.  Oh, geez!
      FILE *c_file()
      {
        std::__basic_file<charT> *ptr_M_file = *(std::__basic_file<charT> **)((char*)this + sizeof(std::basic_streambuf<charT, traits>));
#  if _GLIBCPP_BASIC_FILE_INHERITANCE
        // __basic_file<charT> inherits from __basic_file_base<charT>
        return *(FILE **)((char *)ptr_M_file + sizeof(std::__basic_file_base<charT>));
#  else
        // __basic_file<charT> is base class, but with vptr.
        return *(FILE **)((char *)ptr_M_file + sizeof(void*));
#  endif
      }
    };
    return ::fileno(static_cast<my_filebuf *>(fbuf)->c_file());
  }
#  endif
# endif
#else
#  error "Does anybody know how to fetch the bloody file descriptor?"
  return stream.rdbuf()->fd();  // Maybe a good start?
#endif
  errno = EBADF;
  return -1;
}

}

//! 8-Bit character instantiation: GetFileDescriptor(ios).
template <>
int GetFileDescriptor<char>(const std::streambuf *stream_buffer)
{
  return fileno_hack(const_cast<std::streambuf *>(stream_buffer));
}

#if !(defined(__GLIBCXX__) || defined(__GLIBCPP__)) || (defined(_GLIBCPP_USE_WCHAR_T) || defined(_GLIBCXX_USE_WCHAR_T))
//! Wide character instantiation: GetFileDescriptor(wios).
template <>
int GetFileDescriptor<wchar_t>(const std::wstreambuf *stream_buffer)
{
  return fileno_hack(const_cast<std::wstreambuf *>(stream_buffer));
}
#endif

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
