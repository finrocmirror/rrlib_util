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
/*!\file    tCallback.h
 *
 * \author  Tim Braun
 * \date    2006-04-07
 *

 *
 * \brief   Contains tBaseCallback, tCallback
 *
 * \b tCallback
 *
 *  Template for setting up callbacks from objects to other objects
 *  see tScene.cpp in library simvis3d for an usage example
 *  FIXME: add appropriate documentation here
 *
 */
//----------------------------------------------------------------------


#ifndef _rrlib_util_tCallback_h_
#define _rrlib_util_tCallback_h_

namespace rrlib
{
namespace util
{
class tBaseCallback
{
public:

  virtual ~tBaseCallback()
  {};

  // function to call member function. virtual cause derived
  // classes will use a pointer to an object and a pointer to a member function
  // to make the function call
  virtual void Call(const void *data) = 0;          // call using function
};


// derived template class
template <class T>
class tCallback : public tBaseCallback
{
private:
  void(T::*fpt)(const void *data);         // pointer to member function
  T* pt2Object;                  // pointer to object

public:

  // constructor - takes pointer to an object and pointer to a member and stores
  // them in two private variables
  tCallback(T* _pt2Object, void(T::*_fpt)(const void *))
  {
    pt2Object = _pt2Object;
    fpt = _fpt;
  };

  virtual ~tCallback()
  {};

  // override function Call
  virtual void Call(const void *data)
  {
    (pt2Object->*fpt)(data);      // dont insert spaces here - code will break :(

  }; // execute member function
};
};
};
#endif
