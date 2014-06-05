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
/*!\file    rrlib/util/tUnitTestSuite.h
 *
 * \author  Tobias Foehst
 *
 * \date    2011-03-24
 *
 * \brief
 *
 * \b
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tUnitTestSuite_h__
#define __rrlib__util__tUnitTestSuite_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

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
#define RRLIB_UNIT_TESTS_REGISTER_SUITE(suite_typename) CPPUNIT_TEST_SUITE_REGISTRATION(suite_typename)
#define RRLIB_UNIT_TESTS_BEGIN_SUITE(suite_typename) CPPUNIT_TEST_SUITE(suite_typename)
#define RRLIB_UNIT_TESTS_ADD_TEST(test_function_name) CPPUNIT_TEST(test_function_name)
#define RRLIB_UNIT_TESTS_END_SUITE CPPUNIT_TEST_SUITE_END()

#define RRLIB_UNIT_TESTS_ASSERT(expression) CPPUNIT_ASSERT(expression)
#define RRLIB_UNIT_TESTS_ASSERT_MESSAGE(msg, expression) CPPUNIT_ASSERT_MESSAGE(msg, expression)
#define RRLIB_UNIT_TESTS_EQUALITY(expected, actual) CPPUNIT_ASSERT_EQUAL(expected, actual)
#define RRLIB_UNIT_TESTS_EQUALITY_MESSAGE(msg, expected, actual) CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, expected, actual)
#define RRLIB_UNIT_TESTS_EQUALITY_DOUBLE(expected, actual, delta) CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, actual, delta)
#define RRLIB_UNIT_TESTS_EQUALITY_DOUBLE_MESSAGE(msg, expected, actual, delta) CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(msg, expected, actual, delta)
#define RRLIB_UNIT_TESTS_EXCEPTION(expression, exception_type) CPPUNIT_ASSERT_THROW(expression, exception_type)
#define RRLIB_UNIT_TESTS_EXCEPTION_MESSAGE(msg, expression, exception_type) CPPUNIT_ASSERT_THROW_MESSAGE(msg, expression, exception_type)

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
class tUnitTestSuite : public CPPUNIT_NS::TestFixture
{

public:

  ~tUnitTestSuite() = 0;

  void setUp();

  void tearDown();

private:

  virtual void InitializeTests()
  {};

  virtual void CleanUp()
  {};

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
