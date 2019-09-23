/*
 *  Copyright 2008-2013 NVIDIA Corporation
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

#include <hydra/detail/external/thrust/detail/config.h>
#include <hydra/detail/external/thrust/detail/allocator/malloc_allocator.h>
#include <hydra/detail/external/thrust/system/detail/generic/select_system.h>
#include <hydra/detail/external/thrust/system/detail/bad_alloc.h>
#include <hydra/detail/external/thrust/detail/raw_pointer_cast.h>
#include <hydra/detail/external/thrust/detail/malloc_and_free.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{
namespace detail
{


template<typename T, typename System, typename Pointer>
  typename malloc_allocator<T,System,Pointer>::pointer
    malloc_allocator<T,System,Pointer>
      ::allocate(typename malloc_allocator<T,System,Pointer>::size_type cnt)
{
  using HYDRA_EXTERNAL_NS::thrust::system::detail::generic::select_system;

  // XXX should use a hypothetical HYDRA_EXTERNAL_NS::thrust::static_pointer_cast here
  System system;

  pointer result = HYDRA_EXTERNAL_NS::thrust::malloc<T>(select_system(system), cnt);

  if(result.get() == 0)
  {
    throw HYDRA_EXTERNAL_NS::thrust::system::detail::bad_alloc("malloc_allocator::allocate: malloc failed");
  } // end if

  return result;
} // end malloc_allocator::allocate()


template<typename T, typename System, typename Pointer>
  void malloc_allocator<T,System,Pointer>
    ::deallocate(typename malloc_allocator<T,System,Pointer>::pointer p, typename malloc_allocator<T,System,Pointer>::size_type)
{
  using HYDRA_EXTERNAL_NS::thrust::system::detail::generic::select_system;

  System system;
  HYDRA_EXTERNAL_NS::thrust::free(select_system(system), p);
} // end malloc_allocator


} // end detail
} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust

HYDRA_EXTERNAL_NAMESPACE_END
