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
/*!\file    tReplaceAllAll.h
 *
 * \author  Tobias Foehst
 *
 * \date    2011-03-25
 *
 * \brief Contains tReplaceAllAll
 *
 * \b tReplaceAllAll
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__type_list__include_guard__
#error Invalid include directive. Try #include "rrlib/util/tTypeList.h" instead.
#endif

#ifndef __rrlib__util__type_lists__tReplaceAllAll_h__
#define __rrlib__util__type_lists__tReplaceAllAll_h__

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
template <typename TList, typename TOldType, typename TNewType> class tReplaceAll;

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
template <typename TOldType, typename TNewType>
struct tReplaceAll<tEmptyList, TOldType, TNewType>
{
  typedef tEmptyList tResult;
};

template <typename TOldType, typename TNewType, typename ... TTail>
struct tReplaceAll<tTypeList<TOldType, TTail...>, TOldType, TNewType>
{
  typedef tTypeList<TNewType, typename tReplaceAll<typename tTypeList<TOldType, TTail...>::tTail, TOldType, TNewType>::tResult> tResult;
};

template <typename TOldType, typename TNewType, typename THead, typename ... TTail>
struct tReplaceAll<tTypeList<THead, TTail...>, TOldType, TNewType>
{
  typedef tTypeList<THead, typename tReplaceAll<typename tTypeList<THead, TTail...>::tTail, TOldType, TNewType>::tResult> tResult;
};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}

#endif
