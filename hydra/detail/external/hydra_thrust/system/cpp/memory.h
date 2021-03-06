/*
 *  Copyright 2008-2018 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*! \file hydra_thrust/system/cpp/memory.h
 *  \brief Managing memory associated with Thrust's standard C++ system.
 */

#pragma once

#include <hydra/detail/external/hydra_thrust/detail/config.h>
#include <hydra/detail/external/hydra_thrust/system/cpp/memory_resource.h>
#include <hydra/detail/external/hydra_thrust/memory.h>
#include <hydra/detail/external/hydra_thrust/detail/type_traits.h>
#include <hydra/detail/external/hydra_thrust/mr/allocator.h>
#include <ostream>

namespace hydra_thrust
{
namespace system
{
namespace cpp
{
/*! Allocates an area of memory available to Thrust's <tt>cpp</tt> system.
 *  \param n Number of bytes to allocate.
 *  \return A <tt>cpp::pointer<void></tt> pointing to the beginning of the newly
 *          allocated memory. A null <tt>cpp::pointer<void></tt> is returned if
 *          an error occurs.
 *  \note The <tt>cpp::pointer<void></tt> returned by this function must be
 *        deallocated with \p cpp::free.
 *  \see cpp::free
 *  \see std::malloc
 */
inline pointer<void> malloc(std::size_t n);

/*! Allocates a typed area of memory available to Thrust's <tt>cpp</tt> system.
 *  \param n Number of elements to allocate.
 *  \return A <tt>cpp::pointer<T></tt> pointing to the beginning of the newly
 *          allocated elements. A null <tt>cpp::pointer<T></tt> is returned if
 *          an error occurs.
 *  \note The <tt>cpp::pointer<T></tt> returned by this function must be
 *        deallocated with \p cpp::free.
 *  \see cpp::free
 *  \see std::malloc
 */
template<typename T>
inline pointer<T> malloc(std::size_t n);

/*! Deallocates an area of memory previously allocated by <tt>cpp::malloc</tt>.
 *  \param ptr A <tt>cpp::pointer<void></tt> pointing to the beginning of an area
 *         of memory previously allocated with <tt>cpp::malloc</tt>.
 *  \see cpp::malloc
 *  \see std::free
 */
inline void free(pointer<void> ptr);

// XXX upon c++11
// template<typename T>
// using allocator = hydra_thrust::mr::stateless_resource_allocator<T, memory_resource>;

/*! \p cpp::allocator is the default allocator used by the \p cpp system's containers such as
 *  <tt>cpp::vector</tt> if no user-specified allocator is provided. \p cpp::allocator allocates
 *  (deallocates) storage with \p cpp::malloc (\p cpp::free).
 */
template<typename T>
  struct allocator
    : hydra_thrust::mr::stateless_resource_allocator<
        T,
        memory_resource
    >
{
private:
    typedef hydra_thrust::mr::stateless_resource_allocator<
        T,
        memory_resource
    > base;

public:
  /*! The \p rebind metafunction provides the type of an \p allocator
   *  instantiated with another type.
   *
   *  \tparam U The other type to use for instantiation.
   */
  template<typename U>
    struct rebind
  {
    /*! The typedef \p other gives the type of the rebound \p allocator.
     */
    typedef allocator<U> other;
  };

  /*! No-argument constructor has no effect.
   */
  __host__ __device__
  inline allocator() {}

  /*! Copy constructor has no effect.
   */
  __host__ __device__
  inline allocator(const allocator & other) : base(other) {}

  /*! Constructor from other \p allocator has no effect.
   */
  template<typename U>
  __host__ __device__
  inline allocator(const allocator<U> & other) : base(other) {}

  /*! Destructor has no effect.
   */
  __host__ __device__
  inline ~allocator() {}
}; // end allocator

} // end cpp

/*! \}
 */

} // end system

/*! \namespace hydra_thrust::cpp
 *  \brief \p hydra_thrust::cpp is a top-level alias for hydra_thrust::system::cpp.
 */
namespace cpp
{

using hydra_thrust::system::cpp::malloc;
using hydra_thrust::system::cpp::free;
using hydra_thrust::system::cpp::allocator;

} // end cpp

} // end hydra_thrust

#include <hydra/detail/external/hydra_thrust/system/cpp/detail/memory.inl>

