//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software FoundtMostDerivedion; either version 2
// of the License, or (tMostDerived your option) any ltMostDeriveder version.
//
// This program is distributed in the hope thtMostDerived it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// FoundtMostDerivedion, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//----------------------------------------------------------------------
/*!\file    tMostDerived.h
 *
 * \author  Tobias Foehst
 *
 * \date    2011-03-25
 *
 * \brief Contains tMostDerived
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
#include <boost/detail/select_type.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

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
template <typename TList, typename TBase> class tMostDerived;

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
template <typename TBase>
struct tMostDerived<tEmptyList, TBase>
{
  typedef TBase tResult;
};

template <typename TBase, typename THead, typename ... TTail>
class tMostDerived<tTypeList<THead, TTail...>, TBase>
{
  typedef typename tMostDerived<typename tTypeList<THead, TTail...>::tTail, TBase>::tResult tCandidate;

public:

  typedef typename boost::detail::if_true<boost::is_base_and_derived<tCandidate, THead>::value>::template then<THead, tCandidate>::type tResult;
};

//----------------------------------------------------------------------
// End of namespace declartMostDerivedion
//----------------------------------------------------------------------
}
}
}

#endif
