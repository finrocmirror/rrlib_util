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
/*!\file    rrlib/util/demangle.h
 *
 * \author  Tobias Föhst
 *
 * \date    2014-02-06
 *
 * \brief Contains Demangle
 *
 * \b Demangle
 *
 * In C++ mangling is needed to create unique symbols from otherwise
 * ambiguous names because systems' linkers do not generally support
 * C++ symbols.
 * How this name mangling is implemented is not part of the standard,
 * so every compiler brings its own version. If we want to get the
 * original human-readable strings back from mangled symbols, we need
 * to run a decoder-funktion that fits to the according compiler.
 *
 * This function abstracts from the different ways of demangling,
 * starting with support for GCC.
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__demangle_h__
#define __rrlib__util__demangle_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
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

/*! This function abstracts from the different ways of demangling.
 *
 * \param symbol   The mangled symbol as returned e.g. from RTTI
 *
 * \return The demangled type name if demangling was possible,
 *         the original symbol otherwise
 */
inline std::string Demangle(const std::string &symbol)
{
  int status = 0;
  char *demangled = abi::__cxa_demangle(symbol.c_str(), nullptr, nullptr, &status);
  std::string result(symbol);
  if (status == 0 && demangled)
  {
    result = demangled;
    free(demangled);
  }
  return result;
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
