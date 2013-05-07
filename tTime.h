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
/*!\file    rrlib/util/tTime.h
 *
 * \author  Jens Wettach
 *
 * \date    2011-01-04
 *
 * \brief
 *
 */
//----------------------------------------------------------------------
#ifndef _util_tTime_h_
#define _util_tTime_h_

#include <sys/time.h>
#include <iostream>

namespace rrlib
{

#ifdef _LIB_RRLIB_SERIALIZATION_PRESENT_
namespace serialization
{
class tInputStream;
class tOutputStream;
}
#endif

namespace util
{
//! Repesents times (absolutes and differences)
/*! Use this class whenever you want to deal with times,
  as it provides a number of operators and functions.
 */
class  tTime
{
public:

  //! standard constructor, creates a null-time
  tTime()
  {
    tv_sec = 0;
    tv_usec = 0;
  };


  //! constructor, takes a timeval for creation
  tTime(const tTime & t)
  {
    tv_sec = t.tv_sec;
    tv_usec = t.tv_usec;
  }

  //! constructor, takes a timeval for creation
  tTime(timeval t)
  {
    tv_sec = t.tv_sec;
    tv_usec = t.tv_usec;
  }

  //! constructor that gets a time in seconds plus microseconds
  tTime(long sec, long usec)
  {
    tv_sec = sec;
    tv_usec = usec;
    NormalizeTime();
  }

  //! This static function returns a tTime that contains the current System-time
  static inline tTime Now()
  {
    timeval ntime;
    gettimeofday(&ntime, 0);
    return tTime(ntime);
  }

  /*! Returns the time of the current thread (time elapsed since start
    of thread. It exists only for internal MCA usage. You do not need
    to call it directly. */
  static inline tTime TaskTime()
  {
# if (CLOCKS_PER_SEC == 1000000)

    return tTime(0, clock());
# else

    return tTime(0, clock() * (1000000 / CLOCKS_PER_SEC));
# endif

  }

  /*! Returns a time that is calculated by tTime::Now()+tTime(0,usec)
   */
  static inline tTime FutureUSec(long usec)
  {
    tTime ntime(0, usec);
    //FromUSec(usec);
    ntime += tTime::Now();
    return ntime;
  }

  /*! Returns a time that is calculated by
    tTime::Now()+tTime.FromMSec(msec)
  */
  static inline tTime FutureMSec(long msec)
  {
    tTime ntime(0, msec * 1000);
    //FromMSec(msec);
    ntime += tTime::Now();
    return ntime;
  }

  /*! Returns a time that is calculated by tTime::Now()+tTime(sec,0)
   */
  static inline tTime FutureSec(long sec)
  {
    tTime ntime(sec, 0);
    //FromSec(sec);
    ntime += tTime::Now();
    return ntime;
  }

  /*! Sets tTime to zero. Return value is tTime itself. */
  inline tTime FromZero()
  {
    tv_usec = 0;
    tv_sec = 0;
    return *this;
  }

  /*! Sets tTime to the current  Return value is tTime itself. */
  inline tTime FromNow()
  {
    *this = Now();
    return *this;
  }

  /*! Sets tTime to the current task  Return value is tTime itself. */
  inline tTime FromTaskTime()
  {
    *this = TaskTime();
    return *this;
  }

  /*! Sets tTime to tTime(sec,0). Return value is tTime itself. */
  inline tTime FromSec(long sec)
  {
    *this = tTime(sec, 0);
    return *this;
  }

  /*! Splits msec in sec and usec and sets tTime to tTime(sec,usec). Return value is tTime itsself. */
  inline tTime FromMSec(long msec)
  {
    if (msec < 0)
      *this = tTime(msec / 1000 - 1, ((msec % 1000) + 1000) * 1000);
    else
      *this = tTime(msec / 1000, (msec % 1000) * 1000);
    return *this;
  }
  inline tTime FromUSec(long usec)
  {
    if (usec < 0)
      *this = tTime(usec / 1000000 - 1, (usec % 1000000) + 1000000);
    else
      *this = tTime(usec / 1000000, usec % 1000000);
    return *this;
  }

  /*! Compares a tTime with zero. */
  inline bool IsZero() const
  {
    return ((tv_usec == 0) && (tv_sec == 0));
  }

  /*! Returns tTime in nanoseconds */
  inline long long ToNSec()const
  {
    return ((long long)tv_usec + (long long)tv_sec * 1000000) * 1000;
  }

  /*! Returns tTime in microseconds */
  inline long long ToUSec()const
  {
    return (long long)tv_usec + (long long)tv_sec * 1000000;
  }

  /*! Returns tTime in milli seconds rounded down to an long integer.*/
  inline long long ToMSec()const
  {
    return (long long)tv_usec / 1000 + (long long)tv_sec * 1000;
  }

  /*! Returns tTime in seconds rounded down to an long integer.*/
  inline long ToSec()const
  {
    return tv_sec;
  }

  /*! Don't use this function: Returns the tv_sec value if timeval which is the basis of tTime */
  inline long TvSec()const
  {
    return tv_sec;
  }

  /*! Don't use this function: Returns the tv_usec value if timeval which is the basis of tTime */
  inline long TvUSec() const
  {
    return tv_usec;
  }

  /*! Don't use this function: Returns the tv_usec value if timeval which is the basis of tTime */
  inline long TvNSec() const
  {
    return tv_usec * 1000;
  }

  /*! Don't use this function: Sets the internal tv_sec variable of timeval */
  inline void SetTvSec(long new_tv_sec)
  {
    tv_sec = new_tv_sec;
  }

  /*! Don't use this function: Sets the internal tv_usec variable of timeval */
  inline void SetTvUSec(long new_tv_usec)
  {
    tv_usec = new_tv_usec;
  }

  /*! Use this function if you want to express the time in hours, minutes and seconds */
  inline int Hours()const
  {
    return tv_sec / 3600 % 24;
  }

  /*! Use this function if you want to express the time in hours, minutes and seconds */
  inline int Minutes()const
  {
    return (tv_sec % 3600) / 60;
  }

  /*! Use this function if you want to express the time in hours, minutes and seconds */
  inline int Seconds()const
  {
    return (tv_sec % 3600) % 60;
  }

  /*! Use this function if you want to get the subseconds in milliseconds (rounded) */
  inline int MSeconds()const
  {
    return tv_usec / 1000;
  }

  /*! Adds two times */
  inline tTime operator+(const tTime& b)const
  {
    tTime a = *this;
    return a += b;
  }

  /*! Adds a second time */
  inline tTime operator+=(const tTime& b)
  {
    tv_usec += b.tv_usec;
    tv_sec += b.tv_sec;
    //NormalizeTimePositive();
    NormalizeTime();
    return *this;
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
    //NormalizeTimeNegative();
    NormalizeTime();
    return *this;
  }

  /*! sign operator */
  inline tTime operator-()const
  {
    tTime a(-tv_sec, tv_usec);
//     a.tv_usec = tv_usec;
//     a.tv_sec = -tv_sec;
    return a;
  }

  /*! Multiplies the time by a factor. Uses operator*= (see below). */
  inline tTime operator*(double factor)const
  {
    tTime a = *this;
    return a *= factor;
  }

  /*! Multiplies by a factor. */
  inline tTime operator*=(double factor)
  {
    tv_usec = (long)(tv_usec * factor);
    tv_sec = (long)(tv_sec * factor);
    NormalizeTime();
    return *this;
  }

  /*! Compares two variables of type tTime. Returns true if they are not equal*/
  inline bool operator!=(const tTime& b)const
  {
    return (tv_usec != b.tv_usec) || (tv_sec != b.tv_sec);
  }

  /*! Compares two variables of type tTime. Returns true if they are equal*/
  inline bool operator==(const tTime& b) const
  {
    return (tv_usec == b.tv_usec) && (tv_sec == b.tv_sec);
  }

  /*! Compares two variables of type tTime. Returns true if the first one is earlier than the second one*/
  inline bool operator<(const tTime& b) const
  {
    return (tv_sec == b.tv_sec) ? (tv_usec < b.tv_usec) : (tv_sec < b.tv_sec);
  }

  /*! Compares two variables of type tTime. Returns true if the first one is later than the second one*/
  inline bool operator>(const tTime& b) const
  {
    return (tv_sec == b.tv_sec) ? (tv_usec > b.tv_usec) : (tv_sec > b.tv_sec);
  }

  /*! Compares two variables of type tTime. Returns true if the first one is erlier than or equal to the second one*/
  inline bool operator<=(const tTime& b) const
  {
    return (tv_sec == b.tv_sec) ? ((tv_usec == b.tv_usec) || (tv_usec < b.tv_usec)) : (tv_sec < b.tv_sec);
  }

  /*! Compares two variables of type tTime. Returns true if the first one is later than or equal to the second one*/
  inline bool operator>=(const tTime& b) const
  {
    return (tv_sec == b.tv_sec) ? ((tv_usec == b.tv_usec) || (tv_usec > b.tv_usec)) : (tv_sec > b.tv_sec);
  }

  /*! Casts this tTime object into timespec object (consists of tv_sec/tv_nsec, see h)*/
  operator timespec()
  {
    timespec t = {tv_sec, 1000 * tv_usec};
    return t;
  }

  /*! Returns a formatted string for strftime-like-usage instead of getting "(sec, usec)", which is not really readable when used as global timestamp (date) */
  inline std::string GetString(const std::string &format_string) const
  {
    char buffer[64];
    strftime(buffer, sizeof(buffer), format_string.c_str(), localtime(&tv_sec));
    return std::string(buffer);
  }


  // some standard time intervals to be used for timeouts etc
  static const tTime time_forever;
  static const tTime time_0ms;
  static const tTime time_1us;
  static const tTime time_1ms;
  static const tTime time_5ms;
  static const tTime time_10ms;
  static const tTime time_20ms;
  static const tTime time_25ms;
  static const tTime time_30ms;
  static const tTime time_40ms;
  static const tTime time_50ms;
  static const tTime time_100ms;
  static const tTime time_200ms;
  static const tTime time_250ms;
  static const tTime time_300ms;
  static const tTime time_400ms;
  static const tTime time_500ms;
  static const tTime time_1s;
  static const tTime time_2s;
  static const tTime time_5s;
  static const tTime time_10s;
  static const tTime time_30s;
  static const tTime time_60s;
  static const tTime time_120s;
  static const tTime time_180s;
  static const tTime time_240s;
  static const tTime time_30000s;
  static const tTime time_1year;

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

//! Overloading the << operator for ostream
/*! Outputs a time as a pair of long integer representing (seconds, microseconds).
 */
inline std::ostream &operator<<(std::ostream &ost, const tTime& time)
{
  ost << "(" << time.TvSec() << ", " << time.TvUSec() << ")";
  return ost;
}

//! Overloading the << operator for ostream
/*! Outputs a time as a pair of long integer representing (seconds, microseconds).
 */
inline std::istream &operator>>(std::istream &str, tTime &time)
{
  char temp;
  long int tv_sec, tv_usec;
  str >> temp;
  if (temp == '(')
  {
    str >> tv_sec >> temp >> tv_usec >> temp;
  }
  else
  {
    str.putback(temp);
    str >> tv_sec >> tv_usec;
  }
  time = tTime(tv_sec, tv_usec);
  return str;
}

#ifdef _LIB_RRLIB_SERIALIZATION_PRESENT_

serialization::tOutputStream &operator << (serialization::tOutputStream &stream, const tTime &t);

serialization::tInputStream &operator >> (serialization::tInputStream &stream, tTime &t);

#endif

}
}
#endif
