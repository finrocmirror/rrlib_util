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
/*!\file    tFunctorHandler.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-10-24
 *
 * \brief Contains tFunctorHandler
 *
 * \b tFunctorHandler
 *
 */
//----------------------------------------------------------------------
#ifndef _rrlib_util_patterns_command_tFunctorHandler_h_
#define _rrlib_util_patterns_command_tFunctorHandler_h_

#include "rrlib/util/patterns/command/tFunctorHandlerBase.h"
//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

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
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
template <typename TFunctor, typename TReturn, typename ... TParameters>
class tFunctorHandler : public tFunctorHandlerBase<TReturn, TParameters...>
{

  TFunctor functor;

public:

  tFunctorHandler(const TFunctor &functor)
      : functor(functor)
  {}

  TReturn operator()(TParameters... parameters)
  {
    return this->functor(parameters...);
  }

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
