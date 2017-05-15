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
/*!\file    rrlib/util/function_info.h
 *
 * \author  Tobias Föhst
 *
 * \date    2017-05-14
 *
 * A type trait that extracts information about a given callable (function,
 * functor, lambda, everything with an operator())
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__function_info_h__
#define __rrlib__util__function_info_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/tTypeList.h"

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
// Type Traits
//----------------------------------------------------------------------

namespace
{
//! Declarations that are shared amongst all specializations of the trait
template <typename TReturn, typename ... TArgs>
struct FunctionInfoHelper
{
  static const size_t cARITY = sizeof...(TArgs);

  using tReturnType = TReturn;

  template <size_t i>
  using tArgumentType = typename rrlib::util::tTypeList<TArgs...>::template tAt<i>::tResult;

  using tSignature = TReturn(TArgs...);
};
}



//! General trait that assumes an existing operator()
template <typename T>
struct FunctionInfo : FunctionInfo<decltype(&T::operator())>
{};

//! Partial specialization for free functions
template <typename TReturn, typename ... TArgs>
struct FunctionInfo<TReturn(*)(TArgs...)> : FunctionInfoHelper<TReturn, TArgs...>
{};

//! Partial specialization for member functions
template <typename TClass, typename TReturn, typename ... TArgs>
struct FunctionInfo<TReturn(TClass::*)(TArgs...)> : FunctionInfoHelper<TReturn, TArgs...>
{};

//! Partial specialization for const member functions
template <typename TClass, typename TReturn, typename ... TArgs>
struct FunctionInfo<TReturn(TClass::*)(TArgs...) const> : FunctionInfoHelper<TReturn, TArgs...>
{};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
