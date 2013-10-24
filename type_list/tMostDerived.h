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
/*!\file    rrlib/util/type_list/tMostDerived.h
 *
 * \author  Tobias Foehst
 *
 * \date    2011-03-25
 *
 * \brief   Contains tMostDerived
 *
 * \b tMostDerived
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__type_list__include_guard__
#error Invalid include directive. Try #include "rrlib/util/tTypeList.h" instead.
#endif

#ifndef __rrlib__util__type_lists__tMostDerived_h__
#define __rrlib__util__type_lists__tMostDerived_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <type_traits>

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
namespace type_list
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
namespace
{

template <bool, typename TThen, typename TElse>
struct tIfThenElse
{
  typedef TThen tResult;
};

template <typename TThen, typename TElse>
struct tIfThenElse<false, TThen, TElse>
{
  typedef TElse tResult;
};

}

template <typename TList, typename TBase>
class tMostDerived
{
  typedef typename tMostDerived<typename TList::tTail, TBase>::tResult tCandidate;
  static const bool cHEAD_DERIVED_FROM_CANDIDATE = std::is_base_of<tCandidate, typename TList::tHead>::value;
public:
  typedef typename tIfThenElse<cHEAD_DERIVED_FROM_CANDIDATE, typename TList::tHead, tCandidate>::tResult tResult;
};

template <typename TBase>
struct tMostDerived<tEmptyList, TBase>
{
  typedef TBase tResult;
};

//----------------------------------------------------------------------
// End of namespace declartMostDerivedion
//----------------------------------------------------------------------
}
}
}

#endif
