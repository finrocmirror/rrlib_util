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
/*!\file    rrlib/util/string.h
 *
 * \author  Max Reichardt
 *
 * \date    2014-03-10
 *
 * Functions for string processing.
 *
 * This selection is supposed to be very lightweight and only contain
 * functionality that could arguably be provided by the standard string
 * class (and actually is in other programming languages such as e.g.
 * Java).
 * In particular, there should be no dependencies to 3rd party libraries.
 *
 * Some functions such as StartsWith or EndsWith are quite simple - but
 * added to increase readability of the code.
 *
 * In the mid-term, we want to get rid of sStringUtils class.
 *
 * If you need special string processing functionality that is typically
 * not covered by standard string classes, you should either:
 * (1) use such functionality from a library such as boost
 * (2) implement that functionality in the library where you need it
 *     (it can stay there until it is needed in some other library as well)
 * (3) move it to some dedicated (string processing?) rrlib
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__string_h__
#define __rrlib__util__string_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <string>
#include <cstring>

//----------------------------------------------------------------------
// Internal includes with ""
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
// Function declarations
//----------------------------------------------------------------------

/*!
 * \param string String to check
 * \param suffix Suffix
 * \return True if string ends with the provided suffix (true also if suffix is the empty string)
 *
 * (for efficiency reasons, there are 4 overloads)
 */
inline bool EndsWith(const std::string& string, const std::string& suffix)
{
  return string.length() >= suffix.length() && (string.compare(string.length() - suffix.length(), suffix.length(), suffix) == 0);
}
inline bool EndsWith(const std::string& string, const char* suffix)
{
  size_t suffix_length = strlen(suffix);
  return string.length() >= suffix_length && (string.compare(string.length() - suffix_length, suffix_length, suffix) == 0);
}
inline bool EndsWith(const char* string, const std::string& suffix)
{
  size_t string_length = strlen(string);
  return string_length >= suffix.length() && (suffix.compare(0, suffix.length(), string + (string_length - suffix.length()), suffix.length()) == 0);
}
inline bool EndsWith(const char* string, const char* suffix)
{
  size_t string_length = strlen(string);
  size_t suffix_length = strlen(suffix);
  return string_length >= suffix_length && (strncmp(string + (string_length - suffix_length), suffix, suffix_length) == 0);
}


/*!
 * \param string String to check
 * \param prefix Prefix
 * \return True if string starts with the provided prefix (true also if prefix is the empty string)
 *
 * (for efficiency reasons, there are 4 overloads)
 */
inline bool StartsWith(const std::string& string, const std::string& prefix)
{
  return string.compare(0, prefix.length(), prefix) == 0;
}
inline bool StartsWith(const std::string& string, const char* prefix)
{
  return string.compare(0, strlen(prefix), prefix) == 0;
}
inline bool StartsWith(const char* string, const std::string& prefix)
{
  return prefix.compare(0, prefix.length(), string, prefix.length()) == 0;
}
inline bool StartsWith(const char* string, const char* prefix)
{
  return strncmp(string, prefix, strlen(prefix)) == 0;
}

/*!
 * Removes whitespace from the beginning and the end of the string
 *
 * \param string String to trim
 */
void TrimWhitespace(std::string& string);


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
