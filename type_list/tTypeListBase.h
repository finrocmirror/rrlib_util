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
/*!\file    rrlib/util/type_list/tTypeListBase.h
 *
 * \author  Tobias Foehst
 *
 * \date    2012-10-24
 *
 * \brief   Contains tTypeListBase
 *
 * \b tTypeListBase
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__type_list__include_guard__
#error Invalid include directive. Try #include "rrlib/util/tTypeList.h" instead.
#endif

#ifndef __rrlib__util__type_lists__tTypeListBase_h__
#define __rrlib__util__type_lists__tTypeListBase_h__

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
template <typename TList>
struct tTypeListBase
{
  static const size_t cSIZE;

  template <size_t Tindex>
  struct tAt
  {
    typedef typename type_list::tAt<TList, Tindex>::tResult tResult;
  };

  template <typename T>
  struct tIndexOf
  {
    static const size_t cVALUE;
  };

  template <typename T>
  struct tAppend
  {
    typedef typename type_list::tAppend<TList, T>::tResult tResult;
  };

  template <typename TOtherList>
  struct tAppendList
  {
    typedef typename type_list::tAppendList<TList, TOtherList>::tResult tResult;
  };

  template <typename T>
  struct tRemove
  {
    typedef typename type_list::tRemove<TList, T>::tResult tResult;
  };

  template <typename T>
  struct tRemoveAll
  {
    typedef typename type_list::tRemoveAll<TList, T>::tResult tResult;
  };

  struct tUnique
  {
    typedef typename type_list::tUnique<TList>::tResult tResult;
  };

  template <typename TOld, typename TNew>
  struct tReplace
  {
    typedef typename type_list::tReplace<TList, TOld, TNew>::tResult tResult;
  };

  template <typename TOld, typename TNew>
  struct tReplaceAll
  {
    typedef typename type_list::tReplaceAll<TList, TOld, TNew>::tResult tResult;
  };

  template <typename TBase>
  struct tMostDerived
  {
    typedef typename type_list::tMostDerived<TList, TBase>::tResult tResult;
  };

  struct tDerivedToFront
  {
    typedef typename type_list::tDerivedToFront<TList>::tResult tResult;
  };
};

template <typename TList>
const size_t tTypeListBase<TList>::cSIZE = type_list::tSizeOf<TList>::cVALUE;

template <typename TList>
template <typename T>
const size_t tTypeListBase<TList>::tIndexOf<T>::cVALUE = type_list::tFind<TList, T>::cINDEX;

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}

#endif
