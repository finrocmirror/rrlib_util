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
/*!\file    rrlib/util/type_list/tReplace.h
 *
 * \author  Tobias Foehst
 *
 * \date    2011-03-25
 *
 * \brief   Contains tReplace
 *
 * \b tReplace
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__type_list__include_guard__
#error Invalid include directive. Try #include "rrlib/util/tTypeList.h" instead.
#endif

#ifndef __rrlib__util__type_lists__tReplace_h__
#define __rrlib__util__type_lists__tReplace_h__

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
template <typename TList, typename TOld, typename TNew>
class tReplace
{
  typedef typename tReplace<typename TList::tTail, TOld, TNew>::tResult tProcessedTail;
public:
  typedef typename tAppendList<tTypeList<typename TList::tHead>, tProcessedTail>::tResult tResult;
};

template <typename TOld, typename TNew>
struct tReplace<tEmptyList, TOld, TNew>
{
  typedef tEmptyList tResult;
};

template <typename TList, typename TNew>
struct tReplace<TList, typename TList::tHead, TNew>
{
  typedef typename tAppendList<tTypeList<TNew>, typename TList::tTail>::tResult tResult;
};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}

#endif
