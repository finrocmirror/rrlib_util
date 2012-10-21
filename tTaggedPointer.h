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
/*!\file    rrlib/util/tTaggedPointer.h
 *
 * \author  Max Reichardt
 *
 * \date    2012-10-09
 *
 * \brief   Contains tTaggedPointer
 *
 * \b tTaggedPointer
 *
 * Tagged pointer class.
 * This class is used to store a pointer together with an integer in a value of integral type.
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tTaggedPointer_h__
#define __rrlib__util__tTaggedPointer_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/util/tagged_pointer/tTaggedPointerImplementation.h"

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
//! Tagged pointer class
/*!
 * This class is used to store a pointer together with a 'tag' (integer) in a value of integral type (tStorage).
 *
 * \tparam Pointer type (without *)
 * \tparam ALIGNED_POINTERS Are the T pointers used with this class 8-byte aligned? (Typically the case for any object T created with 'new')
 * \tparam TAG_BIT_WIDTH Bit width of tag. 19 bits is supported on all platforms (values 0-524287) for aligned pointers
 *                       and 16 bits (values 0-65535) for non-aligned pointers.
 *                       A value of <= 3 (values 0-7) requires only a 32 bit integer for aligned pointers on 32 bit platforms.
 *                       Maximum bit width on 32 bit platforms is 32.
 *
 * Assertions make sure that only valid pointers and stamps are used.
 */
template <typename T, bool ALIGNED_POINTERS, uint TAG_BIT_WIDTH>
class tTaggedPointer
{
  typedef tagged_pointer::tTaggedPointerImplementation<TAG_BIT_WIDTH, ALIGNED_POINTERS> tImplementation;

  static_assert(TAG_BIT_WIDTH >= 1 && ((sizeof(void*) == 4 && TAG_BIT_WIDTH <= 32) || (TAG_BIT_WIDTH <= 16 || (ALIGNED_POINTERS && TAG_BIT_WIDTH <= 19))), "Invalid TAG_BIT_WIDTH");

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  /*! Integral type that pointer and tag are stored in */
  typedef typename tImplementation::tStorage tStorage;

  /*!
   * Bit mask for tag.
   * The bits in this constant may be used in tag.
   */
  enum { cSTAMP_MASK = (1 << TAG_BIT_WIDTH) - 1 };

  tTaggedPointer() {}
  tTaggedPointer(tStorage raw_tagged_pointer)
  {
    implementation.SetRaw(raw_tagged_pointer);
  }
  tTaggedPointer(T* pointer, uint stamp)
  {
    Set(pointer, stamp);
  }

  /*!
   * \return Pointer stored in this object
   */
  T* GetPointer() const
  {
    return static_cast<T*>(implementation.GetPointer());
  }

  /*!
   * \return Stamp stored in this object
   */
  uint GetStamp() const
  {
    return implementation.GetStamp();
  }

  /*!
   * \param pointer New pointer
   * \param stamp New stamp
   */
  void Set(T* pointer, uint stamp)
  {
    assert((stamp & cSTAMP_MASK) == stamp && "Stamp is out of bounds");
    assert(((!ALIGNED_POINTERS) || ((((size_t)pointer) & 0x7) == 0)) && "Pointer is not aligned");
    implementation.Set(pointer, stamp);
  }

  /*!
   * \param pointer New pointer
   */
  void SetPointer(T* pointer)
  {
    assert(((!ALIGNED_POINTERS) || ((((size_t)pointer) & 0x7) == 0)) && "Pointer is not aligned");
    implementation.SetPointer(pointer);
  }

  /*!
   * \param stamp New stamp
   */
  void SetStamp(uint stamp)
  {
    assert((stamp & cSTAMP_MASK) == stamp && "Stamp is out of bounds");
    implementation.SetStamp(stamp);
  }

  // operators

  operator tStorage() const
  {
    return implementation.GetStorage();
  }
  operator tStorage&()
  {
    return implementation.GetStorageReference();
  }

  T& operator*() const
  {
    assert(GetPointer() && "Dereferencing null pointer is not allowed");
    return *GetPointer();
  }

  T* operator->() const
  {
    assert(GetPointer() && "Dereferencing null pointer is not allowed");
    return GetPointer();
  }

  tTaggedPointer& operator=(tStorage raw_tagged_pointer)
  {
    implementation.SetRaw(raw_tagged_pointer);
    return *this;
  }

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  /*! implementation */
  tImplementation implementation;
};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
