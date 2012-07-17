//
// You received this file as part of MCA2
// Modular Controller Architecture Version 2
//
//Copyright (C) Robotics Research Lab (RRLab) University of Kaiserslautern
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-
//----------------------------------------------------------------------
/*!\file    tTransformTime.h
 *
 * \author  Bernd Helge Schaefer
 * \date    06.06.2006
 *
 * \brief   Contains class tTransformTime
 *
 */
//----------------------------------------------------------------------
// this is a -*- C++ -*- file
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
} //namespace util
} // namespace rrlib


#endif
