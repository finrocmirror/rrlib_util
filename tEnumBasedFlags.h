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
/*!\file    rrlib/util/tEnumBasedFlags.h
 *
 * \author  Max Reichardt
 *
 * \date    2013-10-18
 *
 * \brief   Contains tEnumBasedFlags
 *
 * \b tEnumBasedFlags
 *
 * Set of flags with possible flags defined by an enum.
 * As enums do not support e.g. OR operations, this type is used to handle combining of flags.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tEnumBasedFlags_h__
#define __rrlib__util__tEnumBasedFlags_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

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
// Class declaration
//----------------------------------------------------------------------
//! Set of flags
/*!
 * Set of flags with possible flags defined by an enum.
 * As enums do not support e.g. OR operations, this type is used to handle combining of flags.
 *
 * \tparam TFlag Enum type that defines possible flags
 * \tparam TStorage Integer class that stores flags internally (must have at least as many bits as there are enum constants)
 *
 * Usage:
 *
 * 1) define enum with possible flags
 *
 *    enum class tExampleFlag
 *    {
 *      FLAG1,
 *      FLAG2,
 *      ...
 *    }
 *
 * 2) create a typedef to the tEnumBasedFlags class
 *
 *    typedef tEnumBasedFlags<tExampleFlag> tExampleFlags
 *
 * 3) define operator(s)
 *
 *    constexpr tExampleFlags operator | (const tExampleFlags& flags1, const tExampleFlags& flags2)
 *    {
 *      return tExampleFlags(flags1.Raw() | flags2.Raw());
 *    }
 */
template <typename TFlag, typename TStorage = uint>
class tEnumBasedFlags
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  constexpr tEnumBasedFlags(TFlag flag) :
    wrapped(1 << static_cast<TStorage>(flag))
  {}

  constexpr tEnumBasedFlags() :
    wrapped(0)
  {}

  /*!
   * It should only be necessary to call this for deserialization
   * (explicit to not accept ints and bools etc. and e.g. offer operators for those)
   */
  explicit constexpr tEnumBasedFlags(TStorage flags) :
    wrapped(flags)
  {}

  /*!
   * \flag Flag to check
   * \return Is specified flag currently set?
   */
  bool Get(TFlag flag) const
  {
    return this->wrapped & (1 << static_cast<TStorage>(flag));
  }

  /*!
   * \return Flags as raw integer value
   */
  constexpr TStorage Raw() const
  {
    return this->wrapped;
  }

  /*!
   * Set or remove specified flag
   *
   * \param flag Flag to set or remove
   * \param value Set flag? (false will remove it)
   */
  inline tEnumBasedFlags &Set(TFlag flag, bool value = true)
  {
    if (value)
    {
      this->wrapped |= (1 << static_cast<TStorage>(flag));
    }
    else
    {
      this->wrapped &= (~(1 << static_cast<TStorage>(flag)));
    }
    return *this;
  }

  /*! Reset all flags
   *
   */
  inline tEnumBasedFlags &Reset()
  {
    this->wrapped = TStorage();
    return *this;
  }

  /*! Reset given flag to false
   *
   * \param flag   The Flag to reset
   */
  inline tEnumBasedFlags &Reset(TFlag flag)
  {
    return this->Set(flag, false);
  }

  tEnumBasedFlags& operator |= (const tEnumBasedFlags& other)
  {
    this->wrapped |= other.wrapped;
    return *this;
  }

  /*! Checks if any flag is set
   *
   * \return True if at least one flag is set
   */
  inline bool Any() const
  {
    return this->wrapped;
  }

  /*! Checks if no flag is set to true
   *
   * \return True if no flag is set
   */
  inline bool None() const
  {
    return !this->Any();
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  /*! Wrapped integer containing flag set */
  TStorage wrapped;
};

template <typename TFlag, typename TStorage = uint>
inline bool operator==(const tEnumBasedFlags<TFlag, TStorage>& flags1, const tEnumBasedFlags<TFlag, TStorage>& flags2)
{
  return flags1.Raw() == flags2.Raw();
}
template <typename TFlag, typename TStorage = uint>
inline bool operator!=(const tEnumBasedFlags<TFlag, TStorage>& flags1, const tEnumBasedFlags<TFlag, TStorage>& flags2)
{
  return flags1.Raw() != flags2.Raw();
}
template <typename TFlag, typename TStorage = uint>
inline bool operator<(const tEnumBasedFlags<TFlag, TStorage>& flags1, const tEnumBasedFlags<TFlag, TStorage>& flags2)
{
  return flags1.Raw() < flags2.Raw();
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
