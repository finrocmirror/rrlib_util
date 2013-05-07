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
/*!\file    rrlib/util/tTime.cpp
 *
 * \author  Jens Wettach
 *
 * \date    2011-01-17
 *
 */
//----------------------------------------------------------------------
#include "rrlib/util/tTime.h"

#ifdef _LIB_RRLIB_SERIALIZATION_PRESENT_
#include "rrlib/serialization/tInputStream.h"
#include "rrlib/serialization/tOutputStream.h"
#endif

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace util
{

const tTime tTime::time_forever(-1, 0);
const tTime tTime::time_0ms(0, 0);
const tTime tTime::time_1us(0, 1);
const tTime tTime::time_1ms(0, 1000);
const tTime tTime::time_5ms(0, 5000);
const tTime tTime::time_10ms(0, 10000);
const tTime tTime::time_20ms(0, 20000);
const tTime tTime::time_25ms(0, 25000);
const tTime tTime::time_30ms(0, 30000);
const tTime tTime::time_40ms(0, 40000);
const tTime tTime::time_50ms(0, 50000);
const tTime tTime::time_100ms(0, 100000);
const tTime tTime::time_200ms(0, 200000);
const tTime tTime::time_250ms(0, 250000);
const tTime tTime::time_300ms(0, 300000);
const tTime tTime::time_400ms(0, 400000);
const tTime tTime::time_500ms(0, 500000);
const tTime tTime::time_1s(1, 0);
const tTime tTime::time_2s(2, 0);
const tTime tTime::time_5s(5, 0);
const tTime tTime::time_10s(10, 0);
const tTime tTime::time_30s(30, 0);
const tTime tTime::time_60s(60, 0);
const tTime tTime::time_120s(120, 0);
const tTime tTime::time_180s(180, 0);
const tTime tTime::time_240s(240, 0);
const tTime tTime::time_30000s(30000, 0);
const tTime tTime::time_1year(365 * 86400, 0);


#ifdef _LIB_RRLIB_SERIALIZATION_PRESENT_
serialization::tOutputStream &operator << (serialization::tOutputStream &stream, const tTime &t)
{
  stream.WriteLong(t.TvSec());
  stream.WriteLong(t.TvUSec());
  return stream;
}

serialization::tInputStream &operator >> (serialization::tInputStream &stream, tTime &t)
{
  t.SetTvSec(static_cast<long>(stream.ReadLong()));
  t.SetTvUSec(static_cast<long>(stream.ReadLong()));
  return stream;
}

#endif

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
