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
/*!\file    rrlib/util/tFPSComputer.cpp
 *
 * \author  Bernd Helge Schaefer
 *
 * \date    2008-03-29
 *
 */
//----------------------------------------------------------------------
#include "rrlib/util/tFPSComputer.h"

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace util
{

tFPSComputer::tFPSComputer(long long int check_interval_ms, float old_value_weight):
  current_fps_check(tTime::Now()),
  last_fps_check(current_fps_check),
  time_diff_check(current_fps_check),
  last_frame_counter(0.),
  frame_counter(0.),
  fps(0.),
  old_value_weight(old_value_weight),
  check_interval_ms(check_interval_ms)
{ }

tFPSComputer::tFPSComputer(const tTime &current_time, long long int check_interval_ms, float old_value_weight):
  current_fps_check(current_time),
  last_fps_check(current_time),
  time_diff_check(current_time),
  last_frame_counter(0.),
  frame_counter(0.),
  fps(0.),
  old_value_weight(old_value_weight),
  check_interval_ms(check_interval_ms)
{ }


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
