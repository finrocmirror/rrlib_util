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
/*!\file    rrlib/util/tAutoRegister.h
 *
 * \author  Jens Wettach
 *
 * \date    2010-01-01
 *
 * \brief   Contains tAutoRegister, tRegister
 *
 * \b tAutoRegister, tRegister
 *
 */
//----------------------------------------------------------------------
#ifndef _rrlib_util_tAutoRegister_h_
#define _rrlib_util_tAutoRegister_h_

#include <cstdio>
#include <typeinfo>

namespace rrlib
{
namespace util
{
template<typename T, typename U> U* CreateSingleton()
{
  static T t;
  //fprintf(stderr, "CreateSingleton() called for <%s>\n", typeid(T).name());
  return dynamic_cast<U*>(&t);
}

template<typename T>
class tAutoRegister
{
public:
  tAutoRegister()
  {
    //fprintf(stderr, "tAutoRegister called\n");
    // reference it (to avoid disappearance due to gcc optimization)
    (void)registrar;
  }
private:
  class tRegister
  {
  public:
    tRegister()
    {
      //fprintf(stderr, "Registering <%s>\n", typeid(T).name());
      T::Register();//CreateSingleton<T,T>());
    }
  };

  static tRegister registrar;
};

template<typename T> typename tAutoRegister<T>::tRegister
tAutoRegister<T>::registrar;

template <class Base, class Registree>
class tRegister : public Base, public tAutoRegister<Registree>
{
public:
  tRegister() {};
};
};
};


#endif
