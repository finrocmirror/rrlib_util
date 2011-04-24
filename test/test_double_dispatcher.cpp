//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) AG Robotersysteme TU Kaiserslautern
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
/*!\file    test_double_dispatch_pattern.cpp
 *
 * \author  Tobias Foehst
 *
 * \date    2011-03-26
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
#include "rrlib/util/tDoubleDispatcher.h"

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

struct Base
{
  virtual ~Base() {};
};
struct A : public Base {};
struct B : public Base {};
struct C : public Base {};
struct D : public B {};

struct tBinaryAction
{
  static void Execute(const A &a, const A &b)
  {
    std::cout << "A mit A" << std::endl;
  }
  static void Execute(const A &a, const B &b)
  {
    std::cout << "A mit B" << std::endl;
  }
  static void Execute(const A &a, const C &b)
  {
    std::cout << "A mit C" << std::endl;
  }
  static void Execute(const A &a, const D &b)
  {
    std::cout << "A mit D" << std::endl;
  }
  static void Execute(const B &a, const B &b)
  {
    std::cout << "B mit B" << std::endl;
  }
  static void Execute(const B &a, const C &b)
  {
    std::cout << "B mit C" << std::endl;
  }
  static void Execute(const B &a, const D &b)
  {
    std::cout << "B mit D" << std::endl;
  }
  static void Execute(const C &a, const C &b)
  {
    std::cout << "C mit C" << std::endl;
  }
  static void Execute(const C &a, const D &b)
  {
    std::cout << "C mit D" << std::endl;
  }
  static void Execute(const D &a, const D &b)
  {
    std::cout << "D mit D" << std::endl;
  }

//  static void Execute(const B &a, const A &b) { std::cout << "B mit A" << std::endl; }
//  static void Execute(const C &a, const A &b) { std::cout << "C mit A" << std::endl; }
//  static void Execute(const C &a, const B &b) { std::cout << "C mit B" << std::endl; }
//  static void Execute(const D &a, const A &b) { std::cout << "D mit A" << std::endl; }
//  static void Execute(const D &a, const B &b) { std::cout << "D mit B" << std::endl; }
//  static void Execute(const D &a, const C &b) { std::cout << "D mit C" << std::endl; }

  static void OnError(const Base &left, const Base &right)
  {
    std::cout << "error" << std::endl;
  }
};

void PerformAction(const Base &left, const Base &right)
{
  tDoubleDispatcher<tBinaryAction, const Base, tTypeList<const A, const B, const C, const D>>::Execute(left, right);
}

int main(int argc, char **argv)
{
  std::cout << "Testing double dispatch" << std::endl;

  PerformAction(A(), A());
  PerformAction(A(), B());
  PerformAction(A(), C());
  PerformAction(A(), D());
  PerformAction(B(), A());
  PerformAction(B(), B());
  PerformAction(B(), C());
  PerformAction(B(), D());
  PerformAction(C(), A());
  PerformAction(C(), B());
  PerformAction(C(), C());
  PerformAction(C(), D());
  PerformAction(D(), A());
  PerformAction(D(), B());
  PerformAction(D(), C());
  PerformAction(D(), D());

  return EXIT_SUCCESS;
}
