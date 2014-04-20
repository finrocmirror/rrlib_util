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
/*!\file    rrlib/util/tests/tagged_pointer.cpp
 *
 * \author  Max Reichardt
 *
 * \date    2012-10-09
 *
 * Tests tagged pointers with different template arguments.
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/util/tUnitTestSuite.h"

#include <random>
#include <memory>
#include <atomic>

#include "rrlib/util/tTaggedPointer.h"

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
class tTestTaggedPointer : public util::tUnitTestSuite
{
  RRLIB_UNIT_TESTS_BEGIN_SUITE(tTestTaggedPointer);
  RRLIB_UNIT_TESTS_ADD_TEST(RunAllTests);
  RRLIB_UNIT_TESTS_END_SUITE;

private:

  std::uniform_int_distribution<uint> uniform_int_distribution;
  std::mt19937 engine;

  virtual void InitializeTests()
  {
    this->engine = std::mt19937(1234);
  }

  virtual void CleanUp()
  {}

  template <typename T, bool ALIGNED_POINTERS, uint TAG_BIT_WIDTH>
  void TestTaggedPointer()
  {
    // Some variables of type T
    __attribute__((aligned(8))) // aligment required on 32 bit platforms
    T array[10];
    __attribute__((aligned(8))) // aligment required on 32 bit platforms
    T single_value;
    std::vector<std::unique_ptr<T>> allocated_values;
    for (size_t i = 0; i < 10; ++i)
    {
      allocated_values.emplace_back(new T());
    }

    typedef tTaggedPointer<T, ALIGNED_POINTERS, TAG_BIT_WIDTH> tPointer;
    tPointer pointer;

    // Test all methods
    pointer.Set(&array[7], 1);
    assert(pointer.GetPointer() == &array[7] && pointer.GetStamp() == 1);
    pointer.SetPointer(&single_value);
    assert(pointer.GetPointer() == &single_value && pointer.GetStamp() == 1);
    pointer.SetStamp(0xCAFE7 & tPointer::cSTAMP_MASK);
    assert(pointer.GetPointer() == &single_value && pointer.GetStamp() == (0xCAFE7 & tPointer::cSTAMP_MASK));

    // Test operators
    array[0] = *pointer;
    typename tPointer::tStorage storage = pointer;
    pointer = storage - 1;
    std::atomic<typename tPointer::tStorage> atomic_storage;
    atomic_storage = pointer;
    pointer = atomic_storage + 1;
    assert(pointer.GetPointer() == &single_value && pointer.GetStamp() == (0xCAFE7 & tPointer::cSTAMP_MASK));

    // Test with allocated values and random stamp
    for (size_t i = 0; i < 1000; ++i)
    {
      size_t idx = i % 10;
      uint random = uniform_int_distribution(this->engine) & tPointer::cSTAMP_MASK;
      pointer.Set(allocated_values[idx].get(), random);
      assert(pointer.GetPointer() == allocated_values[idx].get() && pointer.GetStamp() == random);
      random = uniform_int_distribution(this->engine) & tPointer::cSTAMP_MASK;
      pointer.SetPointer(&array[idx]);
      pointer.SetStamp(random);
      assert(pointer.GetPointer() == &array[idx] && pointer.GetStamp() == random);
    }
  }

  void RunAllTests()
  {
    struct tTestType
    {
      int64_t i;
    };

    TestTaggedPointer<tTestType, true, 1>();
    TestTaggedPointer<tTestType, true, 2>();
    TestTaggedPointer<tTestType, true, 3>();
    TestTaggedPointer<tTestType, true, 4>();
    TestTaggedPointer<tTestType, true, 5>();
    TestTaggedPointer<tTestType, true, 6>();
    TestTaggedPointer<tTestType, true, 7>();
    TestTaggedPointer<tTestType, true, 8>();
    TestTaggedPointer<tTestType, true, 9>();
    TestTaggedPointer<tTestType, true, 10>();
    TestTaggedPointer<tTestType, true, 11>();
    TestTaggedPointer<tTestType, true, 12>();
    TestTaggedPointer<tTestType, true, 13>();
    TestTaggedPointer<tTestType, true, 14>();
    TestTaggedPointer<tTestType, true, 15>();
    TestTaggedPointer<tTestType, true, 16>();
    TestTaggedPointer<tTestType, true, 17>();
    TestTaggedPointer<tTestType, true, 18>();
    TestTaggedPointer<tTestType, true, 19>();
    TestTaggedPointer<int16_t, false, 1>();
    TestTaggedPointer<int16_t, false, 2>();
    TestTaggedPointer<int16_t, false, 3>();
    TestTaggedPointer<int16_t, false, 4>();
    TestTaggedPointer<int16_t, false, 5>();
    TestTaggedPointer<int16_t, false, 6>();
    TestTaggedPointer<int16_t, false, 7>();
    TestTaggedPointer<int16_t, false, 8>();
    TestTaggedPointer<int16_t, false, 9>();
    TestTaggedPointer<int16_t, false, 10>();
    TestTaggedPointer<int16_t, false, 11>();
    TestTaggedPointer<int16_t, false, 12>();
    TestTaggedPointer<int16_t, false, 13>();
    TestTaggedPointer<int16_t, false, 14>();
    TestTaggedPointer<int16_t, false, 15>();
    TestTaggedPointer<int16_t, false, 16>();
  }
};

RRLIB_UNIT_TESTS_REGISTER_SUITE(tTestTaggedPointer);

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
