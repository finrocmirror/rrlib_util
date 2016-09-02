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
/*!\file    rrlib/util/tManagedConstCharPointer.h
 *
 * \author  Max Reichardt
 *
 * \date    2016-07-29
 *
 * \brief   Contains tManagedConstCharPointer
 *
 * \b tManagedConstCharPointer
 *
 * Smart pointer class for const char*
 *
 * The constructor takes a const char* argument together with info on whether it needs to be copied on construction and deleted on destruction.
 *
 * Primary use case of this class is memory-efficient storage of a huge number of strings...
 * (1) ... that are often string literals, but not always (no copies are created for literals)
 * (2) ... that have multiple copies across a system (e.g. also used as keys in STL containers, which would be additional copies with a std::string)
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tManagedConstCharPointer_h__
#define __rrlib__util__tManagedConstCharPointer_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <cstring>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/tNoncopyable.h"

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
// Class declaration
//----------------------------------------------------------------------
//! Smart pointer class for const char*
/*!
 * Smart pointer class for const char*
 *
 * The constructor takes a const char* argument together with info on whether it needs to be copied on construction and deleted on destruction.
 *
 * Primary use case of this class is memory-efficient storage of a huge number of strings...
 * (1) ... that are often string literals, but not always (no copies are created for literals)
 * (2) ... that have multiple copies across a system (e.g. also used as keys in STL containers, which would be additional copies with a std::string)
 */
class tManagedConstCharPointer : public rrlib::util::tNoncopyable
{
  /*! Character that marks string copies to be deleted */
  static const char cOWNS_BUFFER_MARKER = 1;

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  tManagedConstCharPointer() : pointer(nullptr) {}

  /*!
   * \param pointer Wrapped pointer
   * \param copy_and_delete_string If true, makes a copy of the string pointed to by 'pointer' and deletes the copy on destruction.
   *                               Should only be false for string literals (and possibly other constant strings with longer lifetime).
   */
  tManagedConstCharPointer(const char* pointer, bool copy_and_delete_string);

  /*! Move constructor */
  tManagedConstCharPointer(tManagedConstCharPointer && other) :
    pointer(nullptr)
  {
    std::swap(pointer, other.pointer);
  }

  /*! Move assigment */
  tManagedConstCharPointer& operator=(tManagedConstCharPointer && other)
  {
    std::swap(pointer, other.pointer);
    return *this;
  }

  ~tManagedConstCharPointer()
  {
    if (OwnsBuffer())
    {
      delete[] pointer;
    }
  }

  /*!
   * \return Wrapped pointer
   */
  const char* Get() const
  {
    return OwnsBuffer() ? (pointer + 1) : pointer;
  }

  /*!
   * \return Does this smart pointer own the buffer it points to?
   */
  bool OwnsBuffer() const
  {
    return pointer ? pointer[0] == cOWNS_BUFFER_MARKER : false;
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  /*! Wrapped pointer; for string copies to be deleted a cOWNS_BUFFER_MARKER is prepended */
  const char* pointer;

};

inline bool operator<(const tManagedConstCharPointer& pointer1, const tManagedConstCharPointer& pointer2)
{
  const char* p1 = pointer1.Get();
  const char* p2 = pointer2.Get();
  if (p1 == p2 || p2 == nullptr)
  {
    return false;
  }
  if (p1 == nullptr)
  {
    return true;
  }
  return strcmp(p1, p2) < 0;
}


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
