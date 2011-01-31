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
/*!\file    test_command_pattern.cpp
 *
 * \author  Tobias Foehst
 *
 * \date    2010-10-24
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/patterns/command.h"

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

// Functor class with return type void and parameters int and double
struct TestFunctor1
{
  void operator()(int i, double d)
  {
    std::cout << "TestFunctor1 called with i = " << i << ", d = " << d << "." << std::endl;
  }
};
// Functor class with return type void and parameter int
struct TestFunctor2
{
  bool operator()(int i)
  {
    std::cout << "TestFunctor2 called with i = " << i << "." << std::endl;
    return true;
  }
};
// Functor class with return type void and no parameters
struct TestFunctor3
{
  void operator()()
  {
    std::cout << "TestFunctor3 called." << std::endl;
  }
};

// Classic void function we can get a pointer to with parameters int and double
void TestFunction(int i, double d)
{
  std::cout << "TestFunction called with i = " << i << ", d = " << d << "." << std::endl;
}

// A function to test if automatic conversion of two int parameters to double for the function and from const char * to std::string as returny type would work
const char *TestConversions(double, double)
{
  static const char buffer[] = "Hello, world!";
  return buffer;
}

void CreateCommand(const tFunctor<const char *, double, double> &command)
{
  std::cout << command(4, 4.5) << std::endl;
}

// A class with two member functions
struct Parrot
{
  void Eat()
  {
    std::cout << "Tsk, knick, tsk..." << std::endl;
  }
  void Speak()
  {
    std::cout << "Oh Captain, my Captain!" << std::endl;
  }
};



int main(int argc, char **argv)
{
  // Test basic functor objects
  TestFunctor1 f1;
  tFunctor<void, int, double> cmd1(f1);
  TestFunctor2 f2;
  tFunctor<bool, int> cmd2(f2);
  TestFunctor3 f3;
  tFunctor<void> cmd3(f3);

  cmd1(4, 4.5);
  cmd2(4);
  cmd3();

  // pointer to function
  tFunctor<void, int, double> cmd4(&TestFunction);
  cmd4(4, 4.5);

  // pointer to function with implicit conversions
  tFunctor<std::string, int, int> cmd5(&TestConversions);
  std::cout << cmd5(4, 4.5).substr(7) << std::endl;

  CreateCommand(&TestConversions);

  // pointer to member functions for objects
  Parrot geronimo;
  tFunctor<void> cmd6(geronimo, &Parrot::Eat);
  tFunctor<void> cmd7(geronimo, &Parrot::Speak);

  cmd6();
  cmd7();

  // copy of functors
  tFunctor<void, int, double> cmd8(cmd1);
  cmd8(4, 4.5);

  // binding of first parameter
  tFunctor<void, double> cmd9 = BindFirstParameter(cmd1, 4);
  cmd9(4.5);

  // binding of second parameter (in terms of the first parameter, applied recursively)
  BindFirstParameter(cmd9, 4.5)();

  // chaining of two functors
  tFunctor<void> cmd10 = ChainFunctors(cmd6, cmd7);
  cmd10();

  // recursive chaining
  ChainFunctors(cmd6, cmd10)();

  // STL compliance
  std::vector<tFunctor<void, int, double>> commands;
  commands.push_back(cmd1);
  commands.push_back(cmd4);
  commands.push_back(cmd8);

  for (std::vector<tFunctor<void, int, double>>::iterator it = commands.begin(); it != commands.end(); ++it)
  {
    (*it)(4, 4.5);
  }

  return EXIT_SUCCESS;
}
