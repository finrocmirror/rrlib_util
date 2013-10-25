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
/*!\file    rrlib/util/join.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-07-31
 *
 * \brief
 *
 * \b join
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__join_h__
#define __rrlib__util__join_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <ostream>
#include <string>

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
// Function declaration
//----------------------------------------------------------------------

template <typename TIterator>
inline void Join(TIterator first, TIterator last, std::ostream &destination, const char *delimiter = ", ");

template <typename TContainer>
inline void Join(TContainer container, std::ostream &destination, const char *delimiter = ", ");

template <typename TIterator>
inline const std::string Join(TIterator first, TIterator last, const char *delimiter = ", ");

template <typename TContainer>
inline const std::string Join(const TContainer &container, const char *delimiter = ", ");

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#include "rrlib/util/join.hpp"

#endif
