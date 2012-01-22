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
/*!\file    tTypeList.h
 *
 * \author  Tobias Foehst
 *
 * \date    2011-03-25
 *
 * \brief Contains tTypeList
 *
 * \b tTypeList
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tTypeList_h__
#define __rrlib__util__tTypeList_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#define __rrlib__util__type_list__include_guard__

#include "rrlib/util/type_list/definitions.h"

#include "rrlib/util/type_list/tSizeOf.h"
#include "rrlib/util/type_list/tAt.h"
#include "rrlib/util/type_list/tFind.h"
#include "rrlib/util/type_list/tAppend.h"
#include "rrlib/util/type_list/tRemove.h"
#include "rrlib/util/type_list/tRemoveAll.h"
#include "rrlib/util/type_list/tUnique.h"
#include "rrlib/util/type_list/tReplace.h"
#include "rrlib/util/type_list/tReplaceAll.h"
#include "rrlib/util/type_list/tMostDerived.h"
#include "rrlib/util/type_list/tDerivedToFront.h"

#undef __rrlib__util__type_list__include_guard__

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
namespace
{

template <typename THead, typename TTail>
class tTypeListBase
{
  typedef tTypeList<THead, TTail> tList;

public:

  typedef THead tHead;
  typedef TTail tTail;

  static const size_t cSIZE = type_list::tSizeOf<tList>::cVALUE;

  template <size_t Tindex>
  struct tAt
  {
    typedef typename type_list::tAt<tList, Tindex>::tResult tResult;
  };

  template <typename TType>
  struct tIndexOf
  {
    static const size_t cVALUE = type_list::tFind<tList, TType>::cINDEX;
  };

  template <typename TType>
  struct tAppend
  {
    typedef typename type_list::tAppend<tList, TType>::tResult tResult;
  };

  template <typename TType>
  struct tRemove
  {
    typedef typename type_list::tRemove<tList, TType>::tResult tResult;
  };

  template <typename TType>
  struct tRemoveAll
  {
    typedef typename type_list::tRemoveAll<tList, TType>::tResult tResult;
  };

  struct tUnique
  {
    typedef typename type_list::tUnique<tList>::tResult tResult;
  };

  template <typename TOldType, typename TNewType>
  struct tReplace
  {
    typedef typename type_list::tReplace<tList, TOldType, TNewType>::tResult tResult;
  };

  template <typename TOldType, typename TNewType>
  struct tReplaceAll
  {
    typedef typename type_list::tReplaceAll<tList, TOldType, TNewType>::tResult tResult;
  };

  template <typename TBase>
  struct tMostDerived
  {
    typedef typename type_list::tMostDerived<tList, TBase>::tResult tResult;
  };

  struct tDerivedToFront
  {
    typedef typename type_list::tDerivedToFront<tList>::tResult tResult;
  };

};

}

template <typename THead>
struct tTypeList<THead> : public tTypeListBase<THead, type_list::tEmptyList>
{};

template <typename THead, typename ... TTail>
struct tTypeList<THead, TTail...> : public tTypeListBase<THead, tTypeList<TTail...>>
{};

template <typename THead, typename ... TTail>
struct tTypeList<THead, tTypeList<TTail...>> : public tTypeListBase<THead, tTypeList<TTail...>>
{};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
