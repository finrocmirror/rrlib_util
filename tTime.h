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
/*!\file    tTime.h
 *
 */
//----------------------------------------------------------------------
#ifndef _util_tTime_h_
#define _util_tTime_h_

#include <sys/time.h>
#include <iostream>

namespace rrlib
{
namespace util
{
class tTime
{
public:
  tTime(): tv_sec(0), tv_usec(0)
  {}

  tTime(timeval time): tv_sec(time.tv_sec), tv_usec(time.tv_usec)
  {}

  //! constructor that gets a time in seconds plus microseconds
  tTime(long sec, long usec)
  {
    tv_sec = sec;
    tv_usec = usec;
    NormalizeTime();
  }


  inline void SetTvSec(long new_tv_sec)
  {
    this->tv_sec = new_tv_sec;
  }
  inline void SetTvUSec(long new_tv_usec)
  {
    this->tv_usec = new_tv_usec;
  }
  inline long TvSec()const
  {
    return this->tv_sec;
  }
  inline long TvUSec()const
  {
    return this->tv_usec;
  }
  inline tTime FromUSec(long usec)
  {
    if (usec < 0)
      *this = tTime(usec / 1000000 - 1, (usec % 1000000) + 1000000);
    else
      *this = tTime(usec / 1000000, usec % 1000000);
    return *this;
  }
  //! This static function returns a tTime that contains the current System-time
  static inline tTime Now()
  {
    timeval ntime;
    gettimeofday(&ntime, 0);
    return tTime(ntime);
  }

  /*! Returns tTime in seconds rounded down to an long integer.*/
  inline long long ToSec()const
  {
    return this->tv_sec;
  }

  /*! Returns tTime in milli seconds rounded down to an long integer.*/
  inline long long ToMSec()const
  {
    return (long long)tv_usec / 1000 + (long long)tv_sec*1000;
  }

  /*! Returns tTime in microseconds */
  inline long long ToUSec()const
  {
    return (long long)tv_usec + (long long)tv_sec*1000000;
  }

  /*! Substracts the second time from the first */
  inline tTime operator-(const tTime& b)const
  {
    tTime a = *this;
    return a -= b;
  }

  /*! Substracts a second time */
  inline tTime operator-=(const tTime& b)
  {
    tv_usec -= b.tv_usec;
    tv_sec -= b.tv_sec;
    NormalizeTime();
    return *this;
  }

private:
  long tv_sec;
  long tv_usec;

  /*! Makes sure that tv_usec lies in the interval [0; 1000000] by:
      - converting multiples of 1000000 usec into multiples of sec
      - transforming tv_sec and tv_usec so that the usec part is positive
  */
  inline void NormalizeTime()
  {
    // test modulo
    tv_sec = tv_sec + tv_usec / 1000000;
    tv_usec = tv_usec % 1000000;

    // ensure that usec part is positive
    if (tv_usec < 0)
    {
      tv_sec --;
      tv_usec += 1000000;
    }
  }

};

std::ostream& operator<<(std::ostream& str, const tTime& time);
}
}

#endif
