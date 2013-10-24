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
/*!\file    rrlib/util/tIntegerSequence.h
 *
 * \author  Max Reichardt
 *
 * \date    2012-12-08
 *
 * \brief   Contains tIntegerSequence
 *
 * \b tIntegerSequence
 *
 * Struct to store a parameter pack with a sequence of n integers,
 * which can be pretty useful when dealing with variadic templates - see
 * http://stackoverflow.com/questions/7858817/unpacking-a-tuple-to-call-a-matching-function-pointer
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tIntegerSequence_h__
#define __rrlib__util__tIntegerSequence_h__

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
namespace internal
{
template <int ... SEQUENCE>
struct tIntegerSequenceGeneratorHelper;
}

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//! Integer sequence
/*!
 * Struct to store a parameter pack with a sequence of n integers,
 * which can be pretty useful when dealing with variadic templates - see
 * http://stackoverflow.com/questions/7858817/unpacking-a-tuple-to-call-a-matching-function-pointer
 */
template <int ... SEQUENCE>
struct tIntegerSequence
{};

/*!
 * Class to build parameter pack of n integers:
 * 0, 1, 2 ... (n-1)
 *
 * \tparam SIZE Size n of parameter pack
 */
template <int SIZE>
struct tIntegerSequenceGenerator
{
  /*! typedef on tIntegerSequence<0, 1, ... (SIZE-1)> */
  typedef typename internal::tIntegerSequenceGeneratorHelper<SIZE>::type type;
};




// Internal helper struct
namespace internal
{
template <int ... SEQUENCE>
struct tIntegerSequenceGeneratorHelper;

template <int SIZE, int ... SEQUENCE>
struct tIntegerSequenceGeneratorHelper<SIZE, SEQUENCE...> : tIntegerSequenceGeneratorHelper < SIZE - 1, SIZE - 1, SEQUENCE... >
{
};

template <int ... SEQUENCE>
struct tIntegerSequenceGeneratorHelper<0, SEQUENCE...>
{
  typedef tIntegerSequence<SEQUENCE...> type;
};
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
