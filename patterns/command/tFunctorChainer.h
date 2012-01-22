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
/*!\file    tFunctorChainer.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-10-24
 *
 * \brief Contains tFunctorChainer
 *
 * \b tFunctorChainer
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__patterns__command__tFunctorChainer_h__
#define __rrlib__util__patterns__command__tFunctorChainer_h__

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
template <typename TFirstFunctor, typename TSecondFunctor>
class tFunctorChainer : public tFunctorHandlerBase<void>
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  tFunctorChainer(const TFirstFunctor &first_functor, const TSecondFunctor &second_functor)
    : first_functor(first_functor),
      second_functor(second_functor)
  {}

  void operator()()
  {
    this->first_functor();
    this->second_functor();
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  TFirstFunctor first_functor;
  TSecondFunctor second_functor;

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
