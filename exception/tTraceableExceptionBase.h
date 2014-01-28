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
/*!\file    rrlib/util/exception/tTraceableExceptionBase.h
 *
 * \author  Tobias Föhst
 *
 * \date    2014-01-24
 *
 * \brief   Contains tTraceableExceptionBase
 *
 * \b tTraceableExceptionBase
 *
 * This is the base class for all exceptions that are augmented with
 * stacktrace capabilities. Usually, it is not used as base class
 * directly but incorporated via tTraceableException.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__exception__tTraceableExceptionBase_h__
#define __rrlib__util__exception__tTraceableExceptionBase_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
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
const size_t cMAX_STACK_TRACE_DEPTH = 20;

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//! Baseclass with backtracing capability
/*!
 * This is the base class for all exceptions that are augmented with
 * stacktrace capabilities. Usually, it is not used as base class
 * directly but incorporated via tTraceableException.
 */
class tTraceableExceptionBase
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  tTraceableExceptionBase();

  virtual ~tTraceableExceptionBase() = 0;

  const char *Backtrace() const noexcept;

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  void *stack_trace[cMAX_STACK_TRACE_DEPTH];
  size_t stack_trace_depth;

  mutable std::string buffered_backtrace;

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
