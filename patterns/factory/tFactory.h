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
/*!\file    tFactory.h
 *
 * \author  Tobias Foehst
 *
 * \date    2011-01-07
 *
 * \brief Contains tFactory
 *
 * \b tFactory
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__patterns__factory__tFactory_h__
#define __rrlib__util__patterns__factory__tFactory_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <map>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/patterns/command.h"

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
template <
typename TAbstractProduct,
typename TIdentifier,
typename TProductCreator = tFunctor<TAbstractProduct *>,
template <typename TAbstractProduct, typename TIdentifier> class TUnknownKeyPolicy = factory::ThrowException
>
class tFactory
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  const bool Register(const TIdentifier &id, const TProductCreator &creator)
  {
    return this->id_to_creator_map.insert(std::make_pair(id, creator)).second;
  }

  template <typename TProduct>
  const bool Register(const TIdentifier &id)
  {
    return this->Register(id, &factory::DefaultNewCreator<TProduct>);
  }

  const bool Unregister(const TIdentifier &id)
  {
    return this->id_to_creator_map.erase(id) == 1;
  }

  TAbstractProduct *Create(const TIdentifier &id) const
  {
    typename std::map<TIdentifier, TProductCreator>::const_iterator it = this->id_to_creator_map.find(id);
    if (it != this->id_to_creator_map.end())
    {
      return (it->second)();
    }
    return TUnknownKeyPolicy<TAbstractProduct, TIdentifier>::OnUnknownType(id);
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  std::map<TIdentifier, TProductCreator> id_to_creator_map;

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
