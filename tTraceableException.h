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
/*!\file    rrlib/util/tTraceableException.h
 *
 * \author  Tobias Föhst
 *
 * \date    2014-01-24
 *
 * \brief   Contains tTraceableException
 *
 * \b tTraceableException
 *
 * This class implements an augmentation class that can be used to add a
 * stacktrace to every other exception class.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tTraceableException_h__
#define __rrlib__util__tTraceableException_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/exception/tTraceableExceptionBase.h"

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
//! Adds backtracing capability to exception classes
/*!
 * This class implements an augmentation class that can be used to add a
 * stacktrace to every other exception class.
 */
template <typename T>
class tTraceableException : public T, public tTraceableExceptionBase
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  template <typename ... TArgs>
explicit tTraceableException(const TArgs &... args) noexcept :
  T(args...)
  {}

  ~tTraceableException() noexcept
  {}

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
