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
/*!\file    rrlib/util/tests/fileio.cpp
 *
 * \author  Jens Wettach
 *
 * \date    2016-05-09
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
#include "rrlib/util/fileio.h"

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
using namespace fileio;
using namespace std;
//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

class TestFileio : public util::tUnitTestSuite
{
  RRLIB_UNIT_TESTS_BEGIN_SUITE(TestFileio);
  RRLIB_UNIT_TESTS_ADD_TEST(TestFunctions);
  RRLIB_UNIT_TESTS_END_SUITE;

private:

  virtual void TestFunctions()
  {
    TestFileAccess();
    TestDirectoryAccess();
  }


  void TestFileAccess()
  {
    string result(""), expected(""), absolute_file_name(""), file_name("");
    char* env_home(getenv("HOME"));
    RRLIB_UNIT_TESTS_ASSERT(env_home != nullptr);
    CPPUNIT_ASSERT_NO_THROW(absolute_file_name = CreateTempFile(env_home));
    RRLIB_UNIT_TESTS_ASSERT(FileExists(absolute_file_name));
    file_name = absolute_file_name;
    auto pos = absolute_file_name.find_last_of("/");
    if (pos != string::npos)
    {
      file_name = absolute_file_name.substr(pos + 1);
    }
    string search(string("$HOME/") + file_name);
    expected = absolute_file_name;
    bool ok(false);
    CPPUNIT_ASSERT_NO_THROW(ok = ShellExpandFilename(result, search));
    RRLIB_UNIT_TESTS_ASSERT(ok);
    RRLIB_UNIT_TESTS_ASSERT(result == expected);

    ofstream file(absolute_file_name);
    RRLIB_UNIT_TESTS_ASSERT(file.good());
    file << "\n\n\n";
    file.close();
    RRLIB_UNIT_TESTS_ASSERT(file.good());
    RRLIB_UNIT_TESTS_ASSERT(CountLineNumbers(absolute_file_name) == 3);

    CPPUNIT_ASSERT_NO_THROW(DeleteFile(expected));
    RRLIB_UNIT_TESTS_ASSERT(!FileExists(absolute_file_name));
  }

  void TestDirectoryAccess()
  {
    string temp_dir("");
    CPPUNIT_ASSERT_NO_THROW(temp_dir = CreateTempDirectory());
    RRLIB_UNIT_TESTS_ASSERT(FileExists(temp_dir));
    CPPUNIT_ASSERT_NO_THROW(ChangeCurrentDirectory(temp_dir));
    std::vector<std::string> files;
    RRLIB_UNIT_TESTS_ASSERT(GetAllFilesInDirectory(temp_dir, files));
    RRLIB_UNIT_TESTS_ASSERT(files.size() == 2);

    string test_dir(temp_dir + "/test_fileio/");
    CPPUNIT_ASSERT_NO_THROW(CreateDirectory(test_dir));
    RRLIB_UNIT_TESTS_ASSERT(FileExists(test_dir));
    RRLIB_UNIT_TESTS_ASSERT(GetAllFilesInDirectory(temp_dir, files));
    RRLIB_UNIT_TESTS_ASSERT(files.size() == 3);
    CPPUNIT_ASSERT_NO_THROW(ChangeCurrentDirectory(test_dir));
    string cur_dir;
    CPPUNIT_ASSERT_NO_THROW(cur_dir = GetCurrentDirectory());
    RRLIB_UNIT_TESTS_ASSERT(cur_dir == test_dir);

    string temp_file("");
    CPPUNIT_ASSERT_NO_THROW(temp_file = CreateTempFile(test_dir));
    RRLIB_UNIT_TESTS_ASSERT(GetAllFilesInDirectory(test_dir, files));
    RRLIB_UNIT_TESTS_ASSERT(files.size() == 3);

    string file_dir(""), file_base(""), file_ext("");
    SplitFullQualifiedFilename(temp_file, file_dir, file_base, file_ext);
    RRLIB_UNIT_TESTS_ASSERT(file_dir == test_dir.substr(0, test_dir.size() - 1));
    RRLIB_UNIT_TESTS_ASSERT(file_dir == test_dir.substr(0, test_dir.find_last_of("/")));
    RRLIB_UNIT_TESTS_ASSERT(file_base == temp_file.substr(test_dir.size(), temp_file.find_last_of(".") - test_dir.size()));
    RRLIB_UNIT_TESTS_ASSERT(file_ext == temp_file.substr(temp_file.find_last_of(".")));

    RRLIB_UNIT_TESTS_EXCEPTION(DeleteDirectory(test_dir), runtime_error);
    CPPUNIT_ASSERT_NO_THROW(DeleteFile(temp_file));
    RRLIB_UNIT_TESTS_ASSERT(!FileExists(temp_file));
    RRLIB_UNIT_TESTS_EXCEPTION(DeleteDirectory(temp_dir), runtime_error);
    CPPUNIT_ASSERT_NO_THROW(DeleteDirectory(test_dir));
    RRLIB_UNIT_TESTS_ASSERT(!FileExists(test_dir));
    CPPUNIT_ASSERT_NO_THROW(DeleteDirectory(temp_dir));
    RRLIB_UNIT_TESTS_ASSERT(!FileExists(temp_dir));
  }

};

RRLIB_UNIT_TESTS_REGISTER_SUITE(TestFileio);

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}
