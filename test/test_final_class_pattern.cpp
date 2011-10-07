//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//----------------------------------------------------------------------
/*!\file    test_final_class_pattern.cpp
 *
 * \author  Tobias Foehst
 *
 * \date    2010-12-14
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
#include "rrlib/util/patterns/final_class.h"

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Namespace usage
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------


// this is basically the test part of this program
//#define TRY_ILLEGAL  // if defined, this file should not compile

struct A
{
  void f()
  {
    std::cout << "A" << std::endl;
  }
};

struct B : public A
{
  void f()
  {
    std::cout << "B" << std::endl;
  }
};

class FinalFromA : public A, RRLIB_FINAL_CLASS
  {};

class FinalFromB : public B, RRLIB_FINAL_CLASS
  {};

struct Final : RRLIB_FINAL_CLASS
{
  void f()
  {
    std::cout << "Final" << std::endl;
  }
};

#ifdef TRY_ILLEGAL
class IllegalFromFinalFromA : public FinalFromA
  {};

class IllegalFromFinalFromB : public FinalFromB
  {};

class IllegalFromFinal : public Final
  {};
#endif

int main(int argc, char **argv)
{
  A a;
  a.f();

  B b;
  b.f();

  FinalFromA final_from_a;
  final_from_a.f();

  FinalFromB final_from_b;
  final_from_b.f();

  FinalFromB final;
  final.f();

#ifdef TRY_ILLEGAL
  IllegalFromFinalFromA illegal_from_final_from_a;
  illegal_from_final_from_a.f();

  IllegalFromFinalFromB illegal_from_final_from_b;
  illegal_from_final_from_b.f();

  IllegalFromFinal illegal_from_final;
  illegal_from_final.f();
#endif

  return EXIT_SUCCESS;
}
