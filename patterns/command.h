//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) AG Robotersysteme TU Kaiserslautern
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
/*!\file    command.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-10-24
 *
 * \brief Contains command
 *
 * \b command
 *
 */
//----------------------------------------------------------------------
#ifndef _rrlib_util_patterns_command_h_
#define _rrlib_util_patterns_command_h_

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/patterns/command/tFunctor.h"
#include "rrlib/util/patterns/command/tFirstParameterBinder.h"
#include "rrlib/util/patterns/command/tFunctorChainer.h"

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
template <typename TReturn, typename TBoundParameter, typename ... TFreeParameters>
tFunctor<TReturn, TFreeParameters...> BindFirstParameter(const tFunctor<TReturn, TBoundParameter, TFreeParameters...> &functor, const TBoundParameter &bound_parameter)
{
  return tFunctor<TReturn, TFreeParameters...>(std::shared_ptr<tFunctorHandlerBase<TReturn, TFreeParameters...>>(new tFirstParameterBinder<TReturn, TBoundParameter, TFreeParameters...>(functor, bound_parameter)));
}

template <typename TFirstReturn, typename TSecondReturn>
tFunctor<void> ChainFunctors(const tFunctor<TFirstReturn> &first_functor, const tFunctor<TSecondReturn> &second_functor)
{
  return tFunctor<void>(std::shared_ptr<tFunctorHandlerBase<void>>(new tFunctorChainer<tFunctor<TFirstReturn>, tFunctor<TSecondReturn>>(first_functor, second_functor)));
}
//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
