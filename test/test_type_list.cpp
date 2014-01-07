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
/*!\file    rrlib/util/test/test_type_list.cpp
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
#include <cstdlib>
#include <iostream>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/tTypeList.h"

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Namespace usage
//----------------------------------------------------------------------
using namespace rrlib::util;

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

struct A {};
struct B {};
struct C {};
struct D {};
struct E {};

struct Aa : public A {};
struct Ab : public A {};
struct Ac : public A {};
struct Ba : public B {};
struct Bb : public B {};
struct Aba : public Ab {};
struct Baa : public Ba {};


template <typename T> const char *Name()
{
  return ".";
}
template <> const char *Name<type_list::tEmptyList>()
{
  return "!";
}
template <> const char *Name<A>()
{
  return "A";
}
template <> const char *Name<B>()
{
  return "B";
}
template <> const char *Name<C>()
{
  return "C";
}
template <> const char *Name<D>()
{
  return "D";
}
template <> const char *Name<E>()
{
  return "E";
}

template <> const char *Name<Aa>()
{
  return "Aa";
}
template <> const char *Name<Ab>()
{
  return "Ab";
}
template <> const char *Name<Ac>()
{
  return "Ac";
}
template <> const char *Name<Ba>()
{
  return "Ba";
}
template <> const char *Name<Bb>()
{
  return "Bb";
}
template <> const char *Name<Aba>()
{
  return "Aba";
}
template <> const char *Name<Baa>()
{
  return "Baa";
}


template <typename TList>
void PrintListElements()
{
  std::cout << Name<typename TList::tHead>();
  PrintListElements<typename TList::tTail>();
}
template <>
void PrintListElements<type_list::tEmptyList>()
{
  std::cout << Name<type_list::tEmptyList>();
}
template <typename TList>
void PrintList()
{
  std::cout << "size: " << TList::cSIZE << " \telements: <";
  PrintListElements<TList>();
  std::cout << ">" << std::endl;
}

int main(int argc, char **argv)
{
  std::cout << "Testing type_list" << std::endl;

  PrintList<tTypeList<>>();
  PrintList<tTypeList<A>>();
  PrintList<tTypeList<A, C>>();
  PrintList<tTypeList<A, C, B>>();
  PrintList<tTypeList<A, C, B, C>>();

  typedef tTypeList<A, C, B, C, D> tList;
  PrintList<tList>();

  std::cout << "At index 0: " << Name<tList::tAt<0>::tResult>() << " found at " << tList::tIndexOf<A>::cVALUE << std::endl;
  std::cout << "At index 1: " << Name<tList::tAt<1>::tResult>() << " found at " << tList::tIndexOf<C>::cVALUE << std::endl;
  std::cout << "At index 2: " << Name<tList::tAt<2>::tResult>() << " found at " << tList::tIndexOf<B>::cVALUE << std::endl;
  std::cout << "At index 3: " << Name<tList::tAt<3>::tResult>() << " found at " << tList::tIndexOf<C>::cVALUE << std::endl;
  std::cout << "At index 4: " << Name<tList::tAt<4>::tResult>() << " found at " << tList::tIndexOf<D>::cVALUE << std::endl;
//  std::cout << "at index 5: " << Name<tList::tAt<5>::tResult>() << std::endl;
  if (tList::tIndexOf<E>::cVALUE == type_list::cNOT_IN_LIST)
  {
    std::cout << "Could not find E. That's OK." << std::endl;
  }
  else
  {
    std::cout << "Found E at " << tList::tIndexOf<E>::cVALUE << ". That's strange." << std::endl;
  }
//  std::cout << "At index 0 in empty list: " << Name<type_list::tAt<tTypeList<>, 0>::tResult>() << std::endl;
  std::cout << "Index of A in empty list: " << type_list::tFind<tTypeList<>, A>::cINDEX << std::endl;

  std::cout << "Testing tAppend E" << std::endl;

  typedef tList::tAppend<E>::tResult tList2;
  PrintList<tList2>();

  std::cout << "<!>  + A     = ";
  PrintList<type_list::tAppend<tTypeList<>, A>::tResult>();
  std::cout << "<!>  + <AB!> = ";
  PrintList<type_list::tAppendList<tTypeList<>, tTypeList<A, B>>::tResult>();
  std::cout << "<A!> + B     = ";
  PrintList<tTypeList<A>::tAppend<B>::tResult>();
  std::cout << "<A!> + <BC!> = ";
  PrintList<tTypeList<A>::tAppendList<tTypeList<B, C>>::tResult>();

  std::cout << "Testing tRemove C" << std::endl;

  typedef tList2::tRemove<C>::tResult tList3;
  PrintList<tList3>();

  std::cout << "Testing tRemove B" << std::endl;

  typedef tList3::tRemove<B>::tResult tList4;
  PrintList<tList4>();

  std::cout << "Testing tRemove D" << std::endl;

  typedef tList4::tRemove<D>::tResult tList5;
  PrintList<tList5>();

  std::cout << "Testing tRemoveAll C on tList2 (should be <ACBCDE!>)" << std::endl;

  PrintList<tList2::tRemoveAll<C>::tResult>();

  std::cout << "Testing tUnique" << std::endl;

  typedef tTypeList<A, B, B, A, C, B, A, A> tList6;
  typedef tList6::tUnique::tResult tList7;
  PrintList<tList6>();
  PrintList<tList7>();

  std::cout << "Testing tReplace B -> D on tList6 (should be <ABBACBAA!>)" << std::endl;

  PrintList<tList6::tReplace<B, D>::tResult>();

  std::cout << "Testing tReplaceAll B -> D on tList6 (should be <ABBACBAA!>)" << std::endl;

  PrintList<tList6::tReplaceAll<B, D>::tResult>();

  std::cout << "Testing tMostDerived" << std::endl;

  typedef tTypeList<A, B, C, D, E, Aa, Ab, Ac, Ba, Bb, Aba, Baa> tList8;
  PrintList<tList8>();
  std::cout << "A -> " << Name<tList8::tMostDerived<A>::tResult>() << std::endl;

  std::cout << "Testing tDerivedToFront" << std::endl;

  typedef tList8::tDerivedToFront::tResult tList9;
  PrintList<tList9>();

  return EXIT_SUCCESS;
}
