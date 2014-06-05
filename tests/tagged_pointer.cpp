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
class TestTaggedPointer : public util::tUnitTestSuite
{
  RRLIB_UNIT_TESTS_BEGIN_SUITE(TestTaggedPointer);
  RRLIB_UNIT_TESTS_ADD_TEST(RunAllTests);
  RRLIB_UNIT_TESTS_END_SUITE;

private:

  std::uniform_int_distribution<uint> uniform_int_distribution;
  std::mt19937 engine;

  virtual void InitializeTests() override
  {
    this->engine = std::mt19937(1234);
  }

  template <typename T, bool ALIGNED_POINTERS, uint TAG_BIT_WIDTH>
  void RunTests()
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
    RRLIB_UNIT_TESTS_ASSERT(pointer.GetPointer() == &array[7] && pointer.GetStamp() == 1);
    pointer.SetPointer(&single_value);
    RRLIB_UNIT_TESTS_ASSERT(pointer.GetPointer() == &single_value && pointer.GetStamp() == 1);
    pointer.SetStamp(0xCAFE7 & tPointer::cSTAMP_MASK);
    RRLIB_UNIT_TESTS_ASSERT(pointer.GetPointer() == &single_value && pointer.GetStamp() == (0xCAFE7 & tPointer::cSTAMP_MASK));

    // Test operators
    array[0] = *pointer;
    typename tPointer::tStorage storage = pointer;
    pointer = storage - 1;
    std::atomic<typename tPointer::tStorage> atomic_storage;
    atomic_storage = pointer;
    pointer = atomic_storage + 1;
    RRLIB_UNIT_TESTS_ASSERT(pointer.GetPointer() == &single_value && pointer.GetStamp() == (0xCAFE7 & tPointer::cSTAMP_MASK));

    // Test with allocated values and random stamp
    for (size_t i = 0; i < 1000; ++i)
    {
      size_t idx = i % 10;
      uint random = uniform_int_distribution(this->engine) & tPointer::cSTAMP_MASK;
      pointer.Set(allocated_values[idx].get(), random);
      RRLIB_UNIT_TESTS_ASSERT(pointer.GetPointer() == allocated_values[idx].get() && pointer.GetStamp() == random);
      random = uniform_int_distribution(this->engine) & tPointer::cSTAMP_MASK;
      pointer.SetPointer(&array[idx]);
      pointer.SetStamp(random);
      RRLIB_UNIT_TESTS_ASSERT(pointer.GetPointer() == &array[idx] && pointer.GetStamp() == random);
    }
  }

  void RunAllTests()
  {
    struct tTestType
    {
      int64_t i;
    };

    RunTests<tTestType, true, 1>();
    RunTests<tTestType, true, 2>();
    RunTests<tTestType, true, 3>();
    RunTests<tTestType, true, 4>();
    RunTests<tTestType, true, 5>();
    RunTests<tTestType, true, 6>();
    RunTests<tTestType, true, 7>();
    RunTests<tTestType, true, 8>();
    RunTests<tTestType, true, 9>();
    RunTests<tTestType, true, 10>();
    RunTests<tTestType, true, 11>();
    RunTests<tTestType, true, 12>();
    RunTests<tTestType, true, 13>();
    RunTests<tTestType, true, 14>();
    RunTests<tTestType, true, 15>();
    RunTests<tTestType, true, 16>();
    RunTests<tTestType, true, 17>();
    RunTests<tTestType, true, 18>();
    RunTests<tTestType, true, 19>();
    RunTests<int16_t, false, 1>();
    RunTests<int16_t, false, 2>();
    RunTests<int16_t, false, 3>();
    RunTests<int16_t, false, 4>();
    RunTests<int16_t, false, 5>();
    RunTests<int16_t, false, 6>();
    RunTests<int16_t, false, 7>();
    RunTests<int16_t, false, 8>();
    RunTests<int16_t, false, 9>();
    RunTests<int16_t, false, 10>();
    RunTests<int16_t, false, 11>();
    RunTests<int16_t, false, 12>();
    RunTests<int16_t, false, 13>();
    RunTests<int16_t, false, 14>();
    RunTests<int16_t, false, 15>();
    RunTests<int16_t, false, 16>();
  }
};

RRLIB_UNIT_TESTS_REGISTER_SUITE(TestTaggedPointer);

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
