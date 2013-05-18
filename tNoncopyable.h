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
/*!\file    rrlib/util/tNoncopyable.h
 *
 * \author  Max Reichardt
 *
 * \date    2013-05-17
 *
 * \brief   Contains tNoncopyable
 *
 * \b tNoncopyable
 *
 * Class without copy constructor and copy assignment operator.
 * Any C++ class that is a subclass of this class is noncopyable as well.
 *
 * In "Effective C++", use of such as class is recommended.
 *
 * In C++11, the copy constructor and copy assignment operator can also
 * be explicitly deleted. However, we consider a tNoncopyable base class
 * more readable.
 *
 * boost::noncopyable is not used, as this creates a dependency to
 * boost - possibly only for this very basic functionality.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tNoncopyable_h__
#define __rrlib__util__tNoncopyable_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
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
// Class declaration
//----------------------------------------------------------------------
//! Class without copy constructor and copy assignment operator.
/*!
 * Class without copy constructor and copy assignment operator.
 * Any C++ class that is a subclass of this class is noncopyable as well.
 *
 * In "Effective C++", use of such as class is recommended.
 *
 * In C++11, the copy constructor and copy assignment operator can also
 * be explicitly deleted. However, we consider a tNoncopyable base class
 * more readable.
 *
 * boost::noncopyable is not used, as this creates a dependency to
 * boost - possibly only for this very basic functionality.
 */
class tNoncopyable
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  tNoncopyable(const tNoncopyable&) = delete; // make noncopyable
  tNoncopyable& operator=(const tNoncopyable&) = delete; // make noncopyable

//----------------------------------------------------------------------
// Protected constructor and destructor
//----------------------------------------------------------------------
protected:

  tNoncopyable() {}

  ~tNoncopyable() {}

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
