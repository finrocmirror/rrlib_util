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
/*!\file    test_singleton_pattern.cpp
 *
 * \author  Tobias Foehst
 *
 * \date    2010-10-26
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <cstdlib>
#include <string>
#include <iostream>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/patterns/singleton.h"

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


struct tLogImplementation
{
  tLogImplementation()
  {
    std::cout << "Log ctor" << std::endl;
  }
  ~tLogImplementation()
  {
    std::cout << "Log dtor" << std::endl;
  }

  void Print(const std::string &message) const
  {
    std::cout << "log: " << message << std::endl;
  }
};
typedef tSingletonHolder<tLogImplementation, singleton::PhoenixSingleton> tLog;
//typedef tSingletonHolder<tLogImplementation, singleton::NoDestruction> tLog;

struct tKeyboardImplementation
{
  tKeyboardImplementation()
  {
    std::cout << "Keyboard ctor" << std::endl;
  }
  ~tKeyboardImplementation()
  {
    std::cout << "Keyboard dtor" << std::endl;
    tLog::Instance().Print("Keyboard destroyed.");
  }

  void Type(const std::string &message) const
  {
    std::cout << "keyboard: " << message << std::endl;
  };
};
typedef rrlib::util::tSingletonHolder<tKeyboardImplementation> tKeyboard;

struct tDisplayImplementation
{
  tDisplayImplementation()
  {
    std::cout << "Display ctor" << std::endl;
  }
  ~tDisplayImplementation()
  {
    std::cout << "Display dtor" << std::endl;
    tLog::Instance().Print("Display destroyed.");
  }

  void Show(const std::string &message) const
  {
    std::cout << "display: " << message << std::endl;
  };
};
typedef rrlib::util::tSingletonHolder<tDisplayImplementation> tDisplay;

int main(int argc, char **argv)
{
  tKeyboard::Instance().Type("foo");
  tDisplay::Instance().Show("bar");

  return EXIT_SUCCESS;
}
