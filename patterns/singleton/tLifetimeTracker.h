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
/*!\file    tLifetimeTracker.h
 *
 * \author  Tobias Foehst
 *
 * \date    2012-01-23
 *
 * \brief Contains tLifetimeTracker
 *
 * \b tLifetimeTracker
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__patterns__singleton__tLifetimeTracker_h__
#define __rrlib__util__patterns__singleton__tLifetimeTracker_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <list>
#include <memory>
#include <algorithm>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/patterns/singleton.h"

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
namespace singleton
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------
class tLifetimeTracker;
typedef tSingletonHolder<std::list<tLifetimeTracker *>> tLifetimeTrackerList;

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//!
/*!
 *
 */
class tLifetimeTracker
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  tLifetimeTracker(unsigned int longevity, void (*destroy_instance)())
    : longevity(longevity),
      destroy_instance(destroy_instance)
  {}

  ~tLifetimeTracker()
  {
    this->destroy_instance();
  }

  static void DestroyNextInstance()
  {
    assert(!tLifetimeTrackerList::Instance().empty());
    delete tLifetimeTrackerList::Instance().front();
    tLifetimeTrackerList::Instance().pop_front();
  }

  static bool SmallerFirst(const tLifetimeTracker *a, const tLifetimeTracker *b)
  {
    return a->longevity < b->longevity;
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  unsigned int longevity;
  void (*destroy_instance)();

};

inline void SetLongevity(unsigned int longevity, void (*destroy_instance)())
{
  static std::mutex mutex;
  std::unique_lock<std::mutex> lock(mutex);

  std::auto_ptr<tLifetimeTracker> p(new tLifetimeTracker(longevity, destroy_instance));

  auto &tracker_list = tLifetimeTrackerList::Instance();
  auto position = std::upper_bound(tracker_list.begin(), tracker_list.end(), p.get(), tLifetimeTracker::SmallerFirst);
  tracker_list.insert(position, p.get());

  p.release();

  std::atexit(&tLifetimeTracker::DestroyNextInstance);
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}

#endif
