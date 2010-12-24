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
/*!\file    tSingletonHolder.h
 *
 * \author  Tobias Foehst
 *
 * \date    2010-10-26
 *
 * \brief Contains tSingletonHolder
 *
 * \b tSingletonHolder
 *
 */
//----------------------------------------------------------------------
#ifndef _rrlib_util_patterns_singleton_tSingletonHolder_h_
#define _rrlib_util_patterns_singleton_tSingletonHolder_h_

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <boost/noncopyable.hpp>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

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
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
template < typename T,
template <typename> class TCreationPolicy = CreateUsingNew,
template <typename> class TLifetimePolicy = DefaultLifetime >
class tSingletonHolder : public boost::noncopyable
{
  tSingletonHolder();

  static void DestroyInstance()
  {
    assert(!Destroyed());
    TCreationPolicy<T>::Destroy(Instance());
    Instance() = 0;
    Destroyed() = true;
  }

  static T *&Instance()
  {
    static T *instance = 0;
    return instance;
  }
  static bool &Destroyed()
  {
    static bool destroyed = false;
    return destroyed;
  }

public:

  static T &GetInstance()
  {
    if (!Instance())
    {
      if (Destroyed())
      {
        TLifetimePolicy<T>::OnDeadReference();
        Destroyed() = false;
      }
      Instance() = TCreationPolicy<T>::Create();
      TLifetimePolicy<T>::ScheduleDestruction(&DestroyInstance);
    }
    return *Instance();
  }

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
