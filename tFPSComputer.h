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
/*!\file    tFPSComputer.h
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
#ifndef _util_tFPSComputer_h_
#define _util_tFPSComputer_h_

#include "rrlib/util/tTime.h"

namespace rrlib
{
namespace util
{
class tFPSComputer
{
public:
  tFPSComputer(long long int check_interval_ms = 1000, float old_value_weight = 0.75);

  tFPSComputer(const util::tTime &current_time, long long int check_interval_ms = 1000, float old_value_weight = 0.75);

  inline void IncrementFrameCounter()
  {
    ++this->frame_counter;
  }

  inline bool IncrementFrameCounterAndCheckFPS()
  {
    return IncrementFrameCounterAndCheckFPS(util::tTime::Now());
  }

  inline bool IncrementFrameCounterAndCheckFPS(const util::tTime &current_time)
  {
    ++this->frame_counter;
    return this->CheckFPS(current_time);
  }

  inline bool CheckFPS()
  {
    return CheckFPS(util::tTime::Now());
  }

  inline bool CheckFPS(const util::tTime &current_time)
  {
    current_fps_check = current_time;
    long long int ms_passed = (current_fps_check - last_fps_check).ToMSec();
    if (ms_passed < 0)
    {
      last_fps_check = current_time;
      return false;
    }
    else if (ms_passed > this->check_interval_ms)
    {
      double number_of_frames = this->frame_counter - this->last_frame_counter;

      fps = this->old_value_weight * fps + (1. - this->old_value_weight) * (number_of_frames * (1000. / (double) ms_passed));

      if (this->fps < 0.1)
      {
        this->fps = 0.;
      }

      this->last_frame_counter = this->frame_counter;
      this->last_fps_check = this->current_fps_check;
      return true;
    }
    return false;
  }

  inline float FPS() const
  {
    return this->fps;
  }

  inline double FrameCounter() const
  {
    return this->frame_counter;
  }

private:
  util::tTime current_fps_check;
  util::tTime last_fps_check;
  util::tTime time_diff_check;
  double last_frame_counter;
  double frame_counter;
  double time_diff;
  float fps;
  float old_value_weight;
  long long int check_interval_ms;
};

}
}
#endif
