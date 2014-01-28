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
/*!\file    rrlib/util/test/test_exceptions.cpp
 *
 * \author  Tobias Föhst
 *
 * \date    2014-01-24
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <sys/time.h>
#include <sstream>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/tTraceableException.h"

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
const size_t cINSTANCES = 100000;

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

void FunctionForLongerBacktrace()
{
  throw rrlib::util::tTraceableException<std::runtime_error>("Finally terminating with uncaught exception");
}

int main(int argc, char **argv)
{
  {
    struct timeval start;
    struct timeval stop;
    std::cout << "Throwing (and catching) " << cINSTANCES / 1000.0 << "k instances of std::runtime_error..." << std::endl;
    gettimeofday(&start, nullptr);
    for (size_t i = 0; i < cINSTANCES; ++i)
    {
      try
      {
        throw std::runtime_error("This is a normal runtime error");
      }
      catch (std::runtime_error &error)
      {}
    }
    gettimeofday(&stop, nullptr);
    double microseconds = (stop.tv_sec - start.tv_sec) * 1E6 + (stop.tv_usec - start.tv_usec);
    std::cout << "done: " << microseconds / 1E6 << " s (" << microseconds / cINSTANCES << " µs/instance)" << std::endl;
  }

  {
    struct timeval start;
    struct timeval stop;
    std::cout << "Throwing (and catching) " << cINSTANCES / 1000.0 << "k instances of tTraceableException<std::runtime_error>..." << std::endl;
    gettimeofday(&start, nullptr);
    for (size_t i = 0; i < cINSTANCES; ++i)
    {
      try
      {
        throw rrlib::util::tTraceableException<std::runtime_error>("This is a traceable runtime error");
      }
      catch (std::runtime_error &error)
      {}
    }
    gettimeofday(&stop, nullptr);
    double microseconds = (stop.tv_sec - start.tv_sec) * 1E6 + (stop.tv_usec - start.tv_usec);
    std::cout << "done: " << microseconds / 1E6 << " s (" << microseconds / cINSTANCES << " µs/instance" << std::endl;
  }

  FunctionForLongerBacktrace();

  return EXIT_SUCCESS;
}
