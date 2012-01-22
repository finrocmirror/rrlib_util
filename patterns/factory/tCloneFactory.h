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
/*!\file    tCloneFactory.h
 *
 * \author  Tobias Foehst
 *
 * \date    2011-01-07
 *
 * \brief Contains tCloneFactory
 *
 * \b tCloneFactory
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__patterns__factory__tCloneFactory_h__
#define __rrlib__util__patterns__factory__tCloneFactory_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <map>
#include <typeinfo>

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
         typename TProductCreator = tFunctor<TAbstractProduct *, const TAbstractProduct &>,
         template <typename TAbstractProduct, typename TIdentifier> class TUnknownKeyPolicy = factory::ThrowException
         >
class tCloneFactory
{

  class tTypeInfoWrapper
  {
    const std::type_info &type;
  public:
    tTypeInfoWrapper(const TAbstractProduct &type) : type(typeid(type)) {}
    tTypeInfoWrapper(const TAbstractProduct *type) : type(typeid(*type)) {}
    const bool operator < (const tTypeInfoWrapper &other) const
    {
      return other.type.before(this->type);
    }
  };

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  const bool Register(const tTypeInfoWrapper &id, const TProductCreator &creator)
  {
    return this->id_to_creator_map.insert(std::make_pair(id, creator)).second;
  }

  template <typename TProduct>
  const bool Register(const tTypeInfoWrapper &id)
  {
    return this->Register(id, &factory::DefaultCopyCloner<TProduct>);
  }

  const bool Unregister(const tTypeInfoWrapper &id)
  {
    return this->id_to_creator_map.erase(id) == 1;
  }

  TAbstractProduct *Create(const TAbstractProduct *model) const
  {
    return this->Create(*model);
  }

  TAbstractProduct *Create(const TAbstractProduct &model) const
  {
    tTypeInfoWrapper id(model);
    typename std::map<tTypeInfoWrapper, TProductCreator>::const_iterator it = this->id_to_creator_map.find(id);
    if (it != this->id_to_creator_map.end())
    {
      return (it->second)(model);
    }
    return TUnknownKeyPolicy<TAbstractProduct, tTypeInfoWrapper>::OnUnknownType(id);
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  std::map<tTypeInfoWrapper, TProductCreator> id_to_creator_map;

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}

#endif
