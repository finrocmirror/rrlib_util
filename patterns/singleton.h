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
/*!\file    singleton.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-10-26
 *
 * \brief Contains singleton
 *
 * \b singleton
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__patterns__singleton_h__
#define __rrlib__util__patterns__singleton_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

// default policies
#include "rrlib/util/patterns/singleton/policies/creation/CreateUsingNew.h"
#include "rrlib/util/patterns/singleton/policies/lifetime/DefaultLifetime.h"

#include "rrlib/util/patterns/singleton/tSingletonHolder.h"

// creation policies
#include "rrlib/util/patterns/singleton/policies/creation/CreateStatic.h"
#include "rrlib/util/patterns/singleton/policies/creation/CreateUsingMalloc.h"

// lifetime policies
#include "rrlib/util/patterns/singleton/policies/lifetime/PhoenixSingleton.h"
#include "rrlib/util/patterns/singleton/policies/lifetime/NoDestruction.h"
#include "rrlib/util/patterns/singleton/policies/lifetime/Longevity.h"

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace util
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Function declaration
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
