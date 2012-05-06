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
/*!\file    join.h
 *
 * \author  Tobias Foehst
 *
 * \date    2012-05-04
 *
 * \brief
 *
 * \b join
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__variadic_templates_h__
#define __rrlib__util__variadic_templates_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <functional>

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

template <typename THead>
inline void ProcessVariadicValues(std::function<void(const THead &)> process_value)
{}

template <typename THead, typename ... TTail>
//inline void ProcessVariadicValues(const THead &head, const TTail &... tail, std::function<void(const THead &)> process_value) FIXME: will probably be valid with gcc 4.6 and does not need hints at instantiation
inline void ProcessVariadicValues(std::function<void(const THead &)> process_value, const THead &head, const TTail &... tail)
{
  process_value(head);
  ProcessVariadicValues(process_value, tail...);
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
