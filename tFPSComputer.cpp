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
/*!\file    tFPSComputer.cpp
 *
 * \author  Bernd Helge Schaefer
 * \date    2008-03-29
 *
 * \brief   Contains class tFPSComputer
 *
 */
//----------------------------------------------------------------------
// this is a -*- C++ -*- file
//----------------------------------------------------------------------

#include "rrlib/util/tFPSComputer.h"

using namespace rrlib::util;

tFPSComputer::tFPSComputer(long long int check_interval_ms):
    current_fps_check(tTime::Now()),
    last_fps_check(current_fps_check),
    time_diff_check(current_fps_check),
    last_frame_counter(0.),
    frame_counter(0.),
    fps(0.),
    old_value_weight(0.75),
    check_interval_ms(check_interval_ms)
{ }

tFPSComputer::tFPSComputer(const tTime &current_time, long long int check_interval_ms):
    current_fps_check(current_time),
    last_fps_check(current_time),
    time_diff_check(current_time),
    last_frame_counter(0.),
    frame_counter(0.),
    fps(0.),
    old_value_weight(0.75),
    check_interval_ms(check_interval_ms)
{ }
