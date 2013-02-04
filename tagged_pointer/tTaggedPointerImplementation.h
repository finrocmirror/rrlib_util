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
/*!\file    rrlib/util/tagged_pointer/tTaggedPointerImplementation.h
 *
 * \author  Max Reichardt
 *
 * \date    2012-10-09
 *
 * \brief   Contains tTaggedPointerImplementation
 *
 * \b tTaggedPointerImplementation
 *
 * Tagged pointer implementations for different platforms
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__util__tagged_pointer__tTaggedPointerImplementation_h__
#define __rrlib__util__tagged_pointer__tTaggedPointerImplementation_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <cassert>

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
namespace tagged_pointer
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//! Tagged pointer implementations for different platforms
/*!
 * Tagged pointer implementations for different platforms
 * Template is specialized for different platforms later
 */
template <uint TAG_BIT_WIDTH, bool ALIGNED_POINTERS>
class tTaggedPointerImplementation : public tTaggedPointerImplementation < TAG_BIT_WIDTH + 1, ALIGNED_POINTERS >
{
public:
  typedef typename tTaggedPointerImplementation < TAG_BIT_WIDTH + 1, ALIGNED_POINTERS >::tImplementation tImplementation;
};

template <typename TStorage>
class tTaggedPointerImplementationBase
{
public:

  typedef TStorage tStorage;

  tTaggedPointerImplementationBase() : storage(0) {}

  tStorage GetStorage() const
  {
    return storage;
  }

  tStorage& GetStorageReference()
  {
    return storage;
  }

  void SetRaw(tStorage raw)
  {
    storage = raw;
  }

protected:

  /*! Current stamp and pointer are stored in this value */
  tStorage storage;
};

#if __x86_64__

const uint64_t POINTER16_MASK = 0x0000FFFFFFFFFFFFLL;
const uint64_t STAMP16_MASK =   0xFFFF000000000000LL;
const uint64_t POINTER19_MASK = 0x00001FFFFFFFFFFFLL;
const uint64_t STAMP19_MASK =   0xFFFFE00000000000LL;

/*!
 * All pointers with up to 16 bits in stamp, use unused 16 bits in pointers on current x64-64 architectures.
 * If one day, such architectures use these upper 16 bits, we need to do something else - possibly...:
 * - use 128 bit atomics
 * - compile with --mx32
 * - store an index instead of a pointer
 */
template <bool ALIGNED_POINTERS>
class tTaggedPointerImplementation<16, ALIGNED_POINTERS> : public tTaggedPointerImplementationBase<uint64_t>
{
public:

  typedef tTaggedPointerImplementation tImplementation;

  void* GetPointer() const
  {
    return reinterpret_cast<void*>(storage & POINTER16_MASK);
  }

  uint GetStamp() const
  {
    return static_cast<int>(storage >> 48);
  }

  void Set(void* pointer, uint stamp)
  {
    uint64_t pointer_int = reinterpret_cast<uint64_t>(pointer);
    assert((pointer_int & POINTER16_MASK) == pointer_int && "x86-64 pointers are using the high 16 bits now. Implementation needs to be changed (see comment to this class).");
    uint64_t stamp64 = stamp;
    storage = (stamp64 << 48) | pointer_int;
  }

  void SetPointer(void* pointer)
  {
    uint64_t pointer_int = reinterpret_cast<uint64_t>(pointer);
    assert((pointer_int & POINTER16_MASK) == pointer_int && "x86-64 pointers are using the high 16 bits now. Implementation needs to be changed (see comment to this class).");
    uint64_t old_stamp = storage & STAMP16_MASK;
    storage = old_stamp | pointer_int;
  }

  void SetStamp(uint stamp)
  {
    uint64_t old_pointer = storage & POINTER16_MASK;
    uint64_t stamp64 = stamp;
    storage = (stamp64 << 48) | old_pointer;
  }
};

template <>
class tTaggedPointerImplementation<19, true> : public tTaggedPointerImplementationBase<uint64_t>
{
public:

  typedef tTaggedPointerImplementation tImplementation;

  void* GetPointer() const
  {
    return reinterpret_cast<void*>((storage & POINTER19_MASK) << 3);
  }

  uint GetStamp() const
  {
    return static_cast<uint>(storage >> 45);
  }

  void Set(void* pointer, uint stamp)
  {
    uint64_t pointer_int = reinterpret_cast<uint64_t>(pointer);
    assert((pointer_int & POINTER16_MASK) == pointer_int && "x86-64 pointers are using the high 16 bits now. Implementation needs to be changed (see comment to this class).");
    uint64_t stamp64 = stamp;
    storage = (stamp64 << 45) | (pointer_int >> 3);
  }

  void SetPointer(void* pointer)
  {
    uint64_t pointer_int = reinterpret_cast<uint64_t>(pointer);
    assert((pointer_int & POINTER16_MASK) == pointer_int && "x86-64 pointers are using the high 16 bits now. Implementation needs to be changed (see comment to this class).");
    uint64_t old_stamp = storage & STAMP19_MASK;
    storage = old_stamp | (pointer_int >> 3);
  }

  void SetStamp(uint stamp)
  {
    uint64_t old_pointer = storage & POINTER19_MASK;
    uint64_t stamp64 = stamp;
    storage = (stamp64 << 45) | old_pointer;
  }
};


#else

const uint32_t POINTER3_MASK =  0xFFFFFFF8;
const uint32_t STAMP3_MASK =    0x00000007;

static_assert(sizeof(void*) == 4, "Architecture not supported yet. However, it should not be too much effort to do so.");

template <>
class tTaggedPointerImplementation<3, true> : public tTaggedPointerImplementationBase<uint>
{
public:

  typedef tTaggedPointerImplementation tImplementation;

  void* GetPointer() const
  {
    return reinterpret_cast<void*>(storage & POINTER3_MASK);
  }

  uint GetStamp() const
  {
    return static_cast<uint>(storage & STAMP3_MASK);
  }

  void Set(void* pointer, uint stamp)
  {
    uint pointer_int = reinterpret_cast<uint>(pointer);
    storage = pointer_int | stamp;
  }

  void SetPointer(void* pointer)
  {
    Set(pointer, GetStamp());
  }

  void SetStamp(uint stamp)
  {
    uint old_pointer = storage & POINTER3_MASK;
    storage = old_pointer | stamp;
  }
};

template <bool ALIGNED_POINTERS>
class tTaggedPointerImplementation<32, ALIGNED_POINTERS>
{
public:
  typedef uint64_t tStorage;
  typedef tTaggedPointerImplementation tImplementation;

  tTaggedPointerImplementation() : storage(0) {}

  void* GetPointer() const
  {
    return reinterpret_cast<void*>(ints[0]);
  }

  uint GetStamp() const
  {
    return static_cast<uint>(ints[1]);
  }

  tStorage GetStorage() const
  {
    return storage;
  }

  tStorage& GetStorageReference()
  {
    return storage;
  }

  void Set(void* pointer, uint stamp)
  {
    SetPointer(pointer);
    SetStamp(stamp);
  }

  void SetPointer(void* pointer)
  {
    ints[0] = reinterpret_cast<uint>(pointer);
  }

  void SetRaw(tStorage raw)
  {
    storage = raw;
  }

  void SetStamp(uint stamp)
  {
    ints[1] = stamp;
  }

private:

  /*! Current stamp and pointer are stored in this value */
  union
  {
    tStorage storage;
    uint ints[2]; // int[0] pointer - int[1] stamp
  };
};


#endif

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}


#endif
