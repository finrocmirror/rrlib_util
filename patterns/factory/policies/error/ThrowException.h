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
/*!\file    ThrowException.h
 *
 * \author  Tobias Foehst
 *
 * \date    2011-01-07
 *
 * \brief Contains ThrowException
 *
 * \b ThrowException
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__patterns__factory__policies__error__ThrowException_h__
#define __rrlib__util__patterns__factory__policies__error__ThrowException_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <stdexcept>
#include <string>

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
namespace factory
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
template <typename TAbstractProduct, typename TIdentifier>
struct ThrowException
{
  class tFactoryException : public std::runtime_error
  {
    TIdentifier id;
  public:
    tFactoryException(const TIdentifier &id) : std::runtime_error("Unknown object type passed to factory!"), id(id) {}
    ~tFactoryException() throw() {};
    const TIdentifier &GetID() const
    {
      return this->id;
    }
  };

  static TAbstractProduct *OnUnknownType(const TIdentifier &id)
  {
    throw tFactoryException(id);
  }
};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}

#endif
