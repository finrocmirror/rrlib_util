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
/*!\file    rrlib/util/time.h
 *
 * \author  Tobias Föhst
 *
 * \date    2017-06-01
 *
 */
//----------------------------------------------------------------------

// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/util/tUnitTestSuite.h"

#include "rrlib/util/tTime.h"
#include "rrlib/time/time.h"

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

//----------------------------------------------------------------------
// Namespace usage
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
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------
class TestTime : public util::tUnitTestSuite
{
  RRLIB_UNIT_TESTS_BEGIN_SUITE(TestTime);
  RRLIB_UNIT_TESTS_ADD_TEST(Conversion);
  RRLIB_UNIT_TESTS_END_SUITE;

private:

  void Conversion()
  {
    auto now = rrlib::time::tTimestamp() + std::chrono::seconds(100000) + std::chrono::microseconds(500);
    RRLIB_UNIT_TESTS_EQUALITY(rrlib::util::tTime(100000, 500), rrlib::util::tTime(now));
  }

};

RRLIB_UNIT_TESTS_REGISTER_SUITE(TestTime);

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
