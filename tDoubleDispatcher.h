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
/*!\file    tDoubleDispatcher.h
 *
 * \author  Tobias Foehst
 *
 * \date    2011-03-26
 *
 * \brief Contains tDoubleDispatcher
 *
 * \b tDoubleDispatcher
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tDoubleDispatcher_h__
#define __rrlib__util__tDoubleDispatcher_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <boost/type.hpp>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/tTypeList.h"

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

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
template <
typename TExecutor,
         typename TLeftBase,
         typename TLeftTypes,
         bool Tsymmetric = true,
         typename TRightBase = TLeftBase,
         typename TRightTypes = TLeftTypes,
         typename TReturn = void
         >
class tDoubleDispatcher
{

//----------------------------------------------------------------------
// Public typedefs and methods
//----------------------------------------------------------------------
public:

  static TReturn Execute(TLeftBase &left, TRightBase &right)
  {
    DispatchLeft(left, right, boost::type<typename TLeftTypes::tUnique::tResult::tDerivedToFront::tResult>());
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  template <bool Tswap_arguments, typename TLeft, typename TRight>
  struct tCallTrait
  {
    static TReturn Execute(TLeft &left, TRight &right)
    {
      return TExecutor::Execute(left, right);
    }
  };
  template <typename TLeft, typename TRight>
  struct tCallTrait<true, TLeft, TRight>
  {
    static TReturn Execute(TLeft &left, TRight &right)
    {
      return TExecutor::Execute(right, left);
    }
  };

  static TReturn DispatchLeft(TLeftBase &left, TRightBase &right, boost::type<type_list::tEmptyList>)
  {
    TExecutor::OnError(left, right);
  }
  template <typename TTypes>
  static TReturn DispatchLeft(TLeftBase &left, TRightBase &right, boost::type<TTypes>)
  {
    typedef typename TTypes::tHead tHead;
    typedef typename TTypes::tTail tTail;
    if (tHead *left_dispatched = dynamic_cast<tHead *>(&left))
    {
      return DispatchRight(*left_dispatched, right, boost::type<typename TRightTypes::tUnique::tResult::tDerivedToFront::tResult>());
    }
    DispatchLeft(left, right, boost::type<tTail>());
  }

  template <typename TLeft>
  static TReturn DispatchRight(TLeft &left_dispatched, TRightBase &right, boost::type<type_list::tEmptyList>)
  {
    TExecutor::OnError(left_dispatched, right);
  }
  template <typename TLeft, typename TTypes>
  static TReturn DispatchRight(TLeft &left_dispatched, TRightBase &right, boost::type<TTypes>)
  {
    typedef typename TTypes::tHead tHead;
    typedef typename TTypes::tTail tTail;
    if (tHead *right_dispatched = dynamic_cast<tHead *>(&right))
    {
      const bool cSWAP_ARGUMENTS = Tsymmetric && type_list::tFind<TRightTypes, tHead>::cINDEX < type_list::tFind<TLeftTypes, TLeft>::cINDEX;
      return tCallTrait<cSWAP_ARGUMENTS, TLeft, tHead>::Execute(left_dispatched, *right_dispatched);
    }
    return DispatchRight(left_dispatched, right, boost::type<tTail>());
  }

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
