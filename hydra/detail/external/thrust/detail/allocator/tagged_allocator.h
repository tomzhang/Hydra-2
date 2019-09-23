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

#pragma once

#include <hydra/detail/external/thrust/detail/config.h>
#include <hydra/detail/external/thrust/detail/type_traits/pointer_traits.h>
#include <hydra/detail/external/thrust/iterator/iterator_traits.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{
namespace detail
{

template<typename T, typename Tag, typename Pointer> class tagged_allocator;

template<typename Tag, typename Pointer>
  class tagged_allocator<void, Tag, Pointer>
{
  public:
    typedef void                                                                                 value_type;
    typedef typename HYDRA_EXTERNAL_NS::thrust::detail::pointer_traits<Pointer>::template rebind<void>::other       pointer;
    typedef typename HYDRA_EXTERNAL_NS::thrust::detail::pointer_traits<Pointer>::template rebind<const void>::other const_pointer;
    typedef std::size_t                                                                          size_type;
    typedef typename HYDRA_EXTERNAL_NS::thrust::detail::pointer_traits<Pointer>::difference_type                    difference_type;
    typedef Tag                                                                                  system_type;

    template<typename U>
      struct rebind
    {
      typedef tagged_allocator<U,Tag,Pointer> other;
    }; // end rebind
};

template<typename T, typename Tag, typename Pointer>
  class tagged_allocator
{
  public:
    typedef T                                                                                 value_type;
    typedef typename HYDRA_EXTERNAL_NS::thrust::detail::pointer_traits<Pointer>::template rebind<T>::other       pointer;
    typedef typename HYDRA_EXTERNAL_NS::thrust::detail::pointer_traits<Pointer>::template rebind<const T>::other const_pointer;
    typedef typename HYDRA_EXTERNAL_NS::thrust::iterator_reference<pointer>::type                                reference;
    typedef typename HYDRA_EXTERNAL_NS::thrust::iterator_reference<const_pointer>::type                          const_reference;
    typedef std::size_t                                                                       size_type;
    typedef typename HYDRA_EXTERNAL_NS::thrust::detail::pointer_traits<pointer>::difference_type                 difference_type;
    typedef Tag                                                                               system_type;

    template<typename U>
      struct rebind
    {
      typedef tagged_allocator<U,Tag,Pointer> other;
    }; // end rebind

    __hydra_host__ __hydra_device__
    inline tagged_allocator();

    __hydra_host__ __hydra_device__
    inline tagged_allocator(const tagged_allocator &);

    template<typename U, typename OtherPointer>
    __hydra_host__ __hydra_device__
    inline tagged_allocator(const tagged_allocator<U, Tag, OtherPointer> &);

    __hydra_host__ __hydra_device__
    inline ~tagged_allocator();

    __hydra_host__ __hydra_device__
    pointer address(reference x) const;

    __hydra_host__ __hydra_device__
    const_pointer address(const_reference x) const;

    size_type max_size() const;
};

template<typename T1, typename Pointer1, typename T2, typename Pointer2, typename Tag>
__hydra_host__ __hydra_device__
bool operator==(const tagged_allocator<T1,Pointer1,Tag> &, const tagged_allocator<T2,Pointer2,Tag> &);

template<typename T1, typename Pointer1, typename T2, typename Pointer2, typename Tag>
__hydra_host__ __hydra_device__
bool operator!=(const tagged_allocator<T1,Pointer1,Tag> &, const tagged_allocator<T2,Pointer2,Tag> &);

} // end detail
} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
HYDRA_EXTERNAL_NAMESPACE_END
#include <hydra/detail/external/thrust/detail/allocator/tagged_allocator.inl>

