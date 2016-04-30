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
/*!\file    rrlib/util/tests/string.cpp
 *
 * \author  Max Reichardt
 *
 * \date    2014-03-11
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/tUnitTestSuite.h"
#include "rrlib/util/string.h"

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
namespace test
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

class TestString : public util::tUnitTestSuite
{
  RRLIB_UNIT_TESTS_BEGIN_SUITE(TestString);
  RRLIB_UNIT_TESTS_ADD_TEST(TestFunctions);
  RRLIB_UNIT_TESTS_END_SUITE;

private:

  virtual void TestFunctions()
  {
    TestStartsWith("", "", true);
    TestStartsWith("same string", "same string", true);
    TestStartsWith(" string", "string", false);
    TestStartsWith("string", " string", false);
    TestStartsWith("string ", "string", true);
    TestStartsWith("string", "string ", false);

    TestEndsWith("", "", true);
    TestEndsWith("same string", "same string", true);
    TestEndsWith(" string", "string", true);
    TestEndsWith("string", " string", false);
    TestEndsWith("string ", "string", false);
    TestEndsWith("string", "string ", false);

    TestTrimWhitespace("", "");
    TestTrimWhitespace(" ", "");
    TestTrimWhitespace("  ", "");
    TestTrimWhitespace("s ", "s");
    TestTrimWhitespace(" s", "s");
    TestTrimWhitespace(" s ", "s");
    TestTrimWhitespace("string", "string");
    TestTrimWhitespace("\t\n string", "string");
    TestTrimWhitespace("string \t  \n ", "string");
    TestTrimWhitespace("\t  string \n ", "string");
    TestTrimWhitespace("\n two strings  ", "two strings");

    std::vector<std::string> tokens, expected;
    const size_t cZERO = 0;
    Tokenize("", tokens, ",;");
    RRLIB_UNIT_TESTS_ASSERT(expected == tokens);
    Tokenize(";,;", tokens, ",;");
    RRLIB_UNIT_TESTS_ASSERT(expected == tokens);
    Tokenize(" ;;", tokens, ",;");
    expected = { " " };
    RRLIB_UNIT_TESTS_ASSERT(expected == tokens);
    Tokenize(";; String1,;String2, ", tokens, ",;");
    expected = { " String1", "String2", " " };
    RRLIB_UNIT_TESTS_ASSERT(expected == tokens);
    Tokenize("(V1,V2,V3)", tokens, "(,)");
    expected = { "V1", "V2", "V3" };
    RRLIB_UNIT_TESTS_ASSERT(expected == tokens);
    Tokenize("  x1,  x2,  x3", tokens, " ,");
    expected = { "x1", "x2", "x3" };
    RRLIB_UNIT_TESTS_ASSERT(expected == tokens);
  }

  void TestStartsWith(const char* string, const char* prefix, bool expected_result)
  {
    std::string message = std::string("StartsWith(\"") + string + "\", \"" + prefix + "\") must return " + std::to_string(expected_result) + ".";
    RRLIB_UNIT_TESTS_EQUALITY_MESSAGE("(1): " + message, expected_result, StartsWith(string, prefix));
    RRLIB_UNIT_TESTS_EQUALITY_MESSAGE("(2): " + message, expected_result, StartsWith(std::string(string), prefix));
    RRLIB_UNIT_TESTS_EQUALITY_MESSAGE("(3): " + message, expected_result, StartsWith(string, std::string(prefix)));
    RRLIB_UNIT_TESTS_EQUALITY_MESSAGE("(4): " + message, expected_result, StartsWith(std::string(string), std::string(prefix)));
  }

  void TestEndsWith(const char* string, const char* suffix, bool expected_result)
  {
    std::string message = std::string("EndsWith(\"") + string + "\", \"" + suffix + "\") must return " + std::to_string(expected_result) + ".";
    RRLIB_UNIT_TESTS_EQUALITY_MESSAGE("(1): " + message, expected_result, EndsWith(string, suffix));
    RRLIB_UNIT_TESTS_EQUALITY_MESSAGE("(2): " + message, expected_result, EndsWith(std::string(string), suffix));
    RRLIB_UNIT_TESTS_EQUALITY_MESSAGE("(3): " + message, expected_result, EndsWith(string, std::string(suffix)));
    RRLIB_UNIT_TESTS_EQUALITY_MESSAGE("(4): " + message, expected_result, EndsWith(std::string(string), std::string(suffix)));
  }

  void TestTrimWhitespace(const char* string, const char* expected_result)
  {
    std::string test_string = string;
    TrimWhitespace(test_string);
    std::string message = std::string("TrimWhitespace(\"") + string + "\") must return \"" + expected_result + "\".";
    RRLIB_UNIT_TESTS_EQUALITY_MESSAGE(message, std::string(expected_result), test_string);
  }

};

RRLIB_UNIT_TESTS_REGISTER_SUITE(TestString);

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}
