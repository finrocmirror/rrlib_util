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
/*!\file    rrlib/util/tTransformTime.h
 *
 * \author  Bernd Helge Schaefer
 *
 * \date    2006-06-06
 *
 * \brief   Contains class tTransformTime
 *
 */
//----------------------------------------------------------------------

#ifndef _tTransformTime_h_
#define _tTransformTime_h_

#include "rrlib/util/tTime.h"

namespace rrlib
{
namespace util
{

class tTransformTime
{
public:
  tTransformTime(const tTime& transformante_time_base,
                 const tTime& transformer_time_base);

  void ChangeTimeBase(const tTime& transformante_time_base,
                      const tTime& transformer_time_base);

  void Transform(tTime& transformante, const tTime& transformer);

private:
  tTime last_transformante;
  tTime last_transformer;
};

// end of namespace declaration
}
}


#endif
