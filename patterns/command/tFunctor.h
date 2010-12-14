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
/*!\file    tFunctor.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-10-24
 *
 * \brief Contains tFunctor
 *
 * \b tFunctor
 *
 */
//----------------------------------------------------------------------
#ifndef _rrlib_util_patterns_command_tFunctor_h_
#define _rrlib_util_patterns_command_tFunctor_h_

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <tr1/memory>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/patterns/command/tFunctorHandlerBase.h"
#include "rrlib/util/patterns/command/tFunctorHandler.h"
#include "rrlib/util/patterns/command/tMemberFunctionHandler.h"

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
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
template <typename TReturn, typename ... TParameters>
class tFunctor
{

  std::shared_ptr<tFunctorHandlerBase<TReturn, TParameters...>> handler;

  tFunctor();

public:

  tFunctor(const tFunctor &other)
      : handler(other.handler)
  {}

  explicit tFunctor(std::shared_ptr<tFunctorHandlerBase<TReturn, TParameters...>> handler)
      : handler(handler)
  {}

  template <typename TFunctor>
  tFunctor(const TFunctor &functor)
      : handler(new tFunctorHandler<TFunctor, TReturn, TParameters...>(functor))
  {}

  template <typename TObject, typename TFunction>
  tFunctor(TObject &object, const TFunction &function)
      : handler(new tMemberFunctionHandler<TObject, TFunction, TReturn, TParameters...>(object, function))
  {}

  TReturn operator()(TParameters... parameters) const
  {
    return (*this->handler)(parameters...);
  }

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
