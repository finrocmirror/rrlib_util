//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//----------------------------------------------------------------------
/*!\file    fileno.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-07-29
 *
 * \brief Contains an implementation of fileno for iostreams
 *
 * \b fileno
 *
 * In the POSIX world of C, all I/O operations are performed by the
 * operating system and incorporate file descriptors. While C has the
 * abstraction FILE * to be portable and usually has a suitable function
 * fileno(FILE *) that gives the user the underlying file descriptor,
 * C++ uses std::iostream and totally hides the underlying mechanisms.
 * Living in the POSIX world, obviously below the std::iostreams you will
 * find some pure file descriptors. But there is no chance to get a grip of
 * them to e.g. check if they belong to a TTY or not.
 *
 * This implementation of a template function called GetFileDescriptor is
 * meant to give access to the underlying file descriptor of a given stream
 * buffer, if it exists to allow use of further POSIX functionality. In a
 * non-POSIX context, the function returns -1 and is therefore perfectly
 * portable.
 *
 * See http://www.ginac.de/~kreckel/fileno for more information.
 *
 * I kept this behind the guards of rrlib_logging because this lib is meant
 * to deal with output to the console and files. So there should not be any
 * use for it outside.
 *
 * \note The original code works on complete streams. For the use within
 *       this library it was altered to work directly on std::basic_streambuf.
 *
 * \note The syntax in this file is not conforming to the RRLib Coding Style
 *       guidelines because it is a copy of code from public domain.
 */
//----------------------------------------------------------------------
#ifndef ___rrlib__util__fstream__fileno_h___
#define ___rrlib__util__fstream__fileno_h___

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <streambuf>

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
// Function declaration
//----------------------------------------------------------------------
//! A fileno implementation for C++ iostreams
/*! In the POSIX world of C, all I/O operations are performed by the
 *  operating system and incorporate file descriptors. While C has the
 *  abstraction FILE * to be portable and usually has a suitable function
 *  fileno(FILE *) that gives the user the underlying file descriptor,
 *  C++ uses std::iostream and totally hides the underlying mechanisms.
 *  Living in the POSIX world, obviously below the std::iostreams you will
 *  find some pure file descriptors. But there is no chance to get a grip of
 *  them to e.g. check if they belong to a TTY or not.
 *
 *  This implementation of a template function called GetFileDescriptor is
 *  meant to give access to the underlying file descriptor of a given stream
 *  buffer, if it exists to allow use of further POSIX functionality. In a
 *  non-POSIX context, the function returns -1 and is therefore perfectly
 *  portable.
 *
 * Similar to fileno(3), but taking a C++ streambuf as argument instead of a
 * FILE*. Note that there is no way for the library to track what you do with
 * the descriptor, so be careful.
 *
 * \param stream_buffer   The stream buffer of which the file descriptor should be determined
 *
 * \returns  The integer file descriptor associated with the streambuf, or -1 if that streambuf is invalid.
 *           In the latter case, for the sake of keeping the code as similar to fileno(3), errno is set to EBADF.
 */
template <typename charT, typename traits>
int GetFileDescriptor(const std::basic_streambuf<charT, traits> *stream_buffer);

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#include "rrlib/util/fstream/fileno.hpp"

#endif
