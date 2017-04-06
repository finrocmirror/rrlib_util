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
/*!\file    rrlib/util/tIteratorRange.h
 *
 * \author  Max Reichardt
 * \author  Tobias Foehst
 *
 * \date    2017-02-01
 *
 * \brief   Contains tIteratorRange
 *
 * \b tIteratorRange
 *
 * Wraps a begin and end iterator (one past the last element).
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tIteratorRange_h__
#define __rrlib__util__tIteratorRange_h__

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
//! Iterator range
/*!
 * Wraps a begin and end iterator (one past the last element).
 */
template <typename TIterator>
class tIteratorRange
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  tIteratorRange() : begin_iterator(), end_iterator()
  {}

  /*!
   * \param begin Begin iterator
   * \param end End iterator
   */
  tIteratorRange(const TIterator& begin, const TIterator& end) :
    begin_iterator(begin),
    end_iterator(end)
  {}

  /*!
   * \return Begin iterator
   */
  const TIterator& Begin() const
  {
    return begin_iterator;
  }
  const TIterator& begin() const
  {
    return begin_iterator;
  }

  /*!
   * \return Whether range is empty
   */
  bool Empty()
  {
    return begin_iterator == end_iterator;
  }

  /*!
   * \return End iterator
   */
  const TIterator& End() const
  {
    return end_iterator;
  }
  const TIterator& end() const
  {
    return end_iterator;
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  /*! Begin and end iterator */
  TIterator begin_iterator, end_iterator;
};


template <typename TIterator>
tIteratorRange<TIterator> MakeRange(TIterator begin, TIterator end)
{
  return tIteratorRange<TIterator>(begin, end);
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

namespace std
{
template <typename TIterator>
TIterator begin(rrlib::util::tIteratorRange<TIterator>& range)
{
  return range.Begin();
}
template <typename TIterator>
TIterator end(rrlib::util::tIteratorRange<TIterator>& range)
{
  return range.End();
}
}


#endif
