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
/*!\file    rrlib/util/tests/type_list.cpp
 *
 * \author  Tobias Foehst
 *
 * \date    2011-03-25
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/util/tUnitTestSuite.h"

#include <type_traits>

#include "rrlib/util/tTypeList.h"

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
class tTestTypeList : public util::tUnitTestSuite
{
  RRLIB_UNIT_TESTS_BEGIN_SUITE(tTestTypeList);
  RRLIB_UNIT_TESTS_ADD_TEST(Size);
  RRLIB_UNIT_TESTS_ADD_TEST(At);
  RRLIB_UNIT_TESTS_ADD_TEST(IndexOf);
  RRLIB_UNIT_TESTS_ADD_TEST(Append);
  RRLIB_UNIT_TESTS_ADD_TEST(Remove);
  RRLIB_UNIT_TESTS_ADD_TEST(Complex);
  RRLIB_UNIT_TESTS_END_SUITE;

private:

  struct A {};
  struct B {};
  struct C {};
  struct D {};
  struct E {};

  typedef tTypeList<A, C, B, C, D> tList;

  virtual void InitializeTests()
  {}

  virtual void CleanUp()
  {}

  void Size()
  {
    RRLIB_UNIT_TESTS_EQUALITY(size_t(0), tTypeList<>::cSIZE);
    RRLIB_UNIT_TESTS_EQUALITY(size_t(1), tTypeList<A>::cSIZE);
    RRLIB_UNIT_TESTS_EQUALITY(size_t(2), (tTypeList<A, C>::cSIZE));
    RRLIB_UNIT_TESTS_EQUALITY(size_t(3), (tTypeList<A, C, B>::cSIZE));
    RRLIB_UNIT_TESTS_EQUALITY(size_t(4), (tTypeList<A, C, B, C>::cSIZE));
    RRLIB_UNIT_TESTS_EQUALITY(size_t(5), tList::cSIZE);
  }

  void At()
  {
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tList::tAt<0>::tResult, A>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tList::tAt<1>::tResult, C>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tList::tAt<2>::tResult, B>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tList::tAt<3>::tResult, C>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tList::tAt<4>::tResult, D>::value));
  }

  void IndexOf()
  {
    RRLIB_UNIT_TESTS_EQUALITY(size_t(0), tList::tIndexOf<A>::cVALUE);
    RRLIB_UNIT_TESTS_EQUALITY(size_t(2), tList::tIndexOf<B>::cVALUE);
    RRLIB_UNIT_TESTS_EQUALITY(size_t(1), tList::tIndexOf<C>::cVALUE);
    RRLIB_UNIT_TESTS_EQUALITY(size_t(4), tList::tIndexOf<D>::cVALUE);
    RRLIB_UNIT_TESTS_EQUALITY(type_list::cNOT_IN_LIST, tList::tIndexOf<E>::cVALUE);
    RRLIB_UNIT_TESTS_EQUALITY(type_list::cNOT_IN_LIST, tTypeList<>::tIndexOf<A>::cVALUE);
  }

  void Append()
  {
    typedef tList::tAppend<E>::tResult tListWithE;
    RRLIB_UNIT_TESTS_EQUALITY(size_t(6), tListWithE::cSIZE);
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tListWithE::tAt<5>::tResult, E>::value));

    RRLIB_UNIT_TESTS_ASSERT((std::is_same<type_list::tAppend<tTypeList<>, A>::tResult, tTypeList<A>>::value));
//    RRLIB_UNIT_TESTS_ASSERT((std::is_same<type_list::tAppend<tTypeList<>, tTypeList<A, B>>::tResult, tTypeList<A, B>>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tTypeList<A>::tAppend<B>::tResult, tTypeList<A, B>>::value));
//    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tTypeList<A>::tAppend<tTypeList<B, C>>::tResult, tTypeList<A, B, C>>::value));
  }

  void Remove()
  {
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tTypeList<A, C, B, C, D, E>::tRemove<C>::tResult, tTypeList<A, B, C, D, E>>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tTypeList<A, B, C, D, E>::tRemove<B>::tResult, tTypeList<A, C, D, E>>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tTypeList<A, C, D, E>::tRemove<D>::tResult, tTypeList<A, C, E>>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tTypeList<A, C, B, C, D, E>::tRemoveAll<C>::tResult, tTypeList<A, B, D, E>>::value));
  }

  void Complex()
  {
    struct Aa : public A {};
    struct Ab : public A {};
    struct Ac : public A {};
    struct Ba : public B {};
    struct Bb : public B {};
    struct Aba : public Ab {};
    struct Baa : public Ba {};

    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tTypeList<A, B, B, A, C, B, A, A>::tUnique::tResult, tTypeList<A, B, C>>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tTypeList<A, B, B>::tReplace<B, D>::tResult, tTypeList<A, D, B>>::value));
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tTypeList<A, B, B>::tReplaceAll<B, D>::tResult, tTypeList<A, D, D>>::value));

    typedef tTypeList<A, B, C, D, E, Aa, Ab, Ac, Ba, Bb, Aba> tListWithDerived;
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tListWithDerived::tMostDerived<A>::tResult, Aba>::value));

    typedef tTypeList<Aba, Bb, C, D, E, Aa, Ab, Ac, Ba, B, A> tSortedList;
    RRLIB_UNIT_TESTS_ASSERT((std::is_same<tListWithDerived::tDerivedToFront::tResult, tSortedList>::value));
  }
};

RRLIB_UNIT_TESTS_REGISTER_SUITE(tTestTypeList);

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
