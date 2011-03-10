//
// You received this file as part of MCA2
// Modular Controller Architecture Version 2
//
//Copyright (C) AG Robotersysteme TU Kaiserslautern
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
/*!\file    tUnitDefinitions.h
 *
 * \author  Bernd Helge Schaefer
 * \date    14.01.2008
 *
 */
//----------------------------------------------------------------------
#ifndef _rrlib_util_tUnitDefinitions_h_
#define _rrlib_util_tUnitDefinitions_h_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include "rrlib/util/tUnitInfoUtils.h"

//! STL includes
#include <memory>

namespace rrlib
{
namespace util
{


enum tDistanceUnit
{
  eDISTANCE_UNIT_MM,
  eDISTANCE_UNIT_CM,
  eDISTANCE_UNIT_DM,
  eDISTANCE_UNIT_M,
  eDISTANCE_UNIT_DIMENSION
};

enum tAngleUnit
{
  eANGLE_UNIT_DEGREE,
  eANGLE_UNIT_TENTH_DEGREE,
  eANGLE_UNIT_HUNDRETH_DEGREE,
  eANGLE_UNIT_THOUSANTH_DEGREE,
  eANGLE_UNIT_RADIAN,
  eANGLE_UNIT_DIMENSION
};

class tUnitDefinitions
{
public:
  static std::shared_ptr<tUnitInfoUtils> distance_utils;
  static std::shared_ptr<tUnitInfoUtils> angle_utils;

  static const tUnitInfo cDistanceUnitInfo [eDISTANCE_UNIT_DIMENSION];
  static const tUnitInfo cAngleUnitInfo [eANGLE_UNIT_DIMENSION];
};

}
}
#endif
