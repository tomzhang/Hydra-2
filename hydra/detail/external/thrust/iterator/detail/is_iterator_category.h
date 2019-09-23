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
#include <hydra/detail/external/thrust/iterator/iterator_categories.h>
#include <hydra/detail/external/thrust/detail/type_traits.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{

namespace detail
{

template <typename T>
  struct is_host_iterator_category
    : HYDRA_EXTERNAL_NS::thrust::detail::or_<
        HYDRA_EXTERNAL_NS::thrust::detail::is_convertible<T, HYDRA_EXTERNAL_NS::thrust::input_host_iterator_tag>,
        HYDRA_EXTERNAL_NS::thrust::detail::is_convertible<T, HYDRA_EXTERNAL_NS::thrust::output_host_iterator_tag>
      >
{
}; // end is_host_iterator_category

template <typename T>
  struct is_device_iterator_category
    : HYDRA_EXTERNAL_NS::thrust::detail::or_<
        HYDRA_EXTERNAL_NS::thrust::detail::is_convertible<T, HYDRA_EXTERNAL_NS::thrust::input_device_iterator_tag>,
        HYDRA_EXTERNAL_NS::thrust::detail::is_convertible<T, HYDRA_EXTERNAL_NS::thrust::output_device_iterator_tag>
      >
{
}; // end is_device_iterator_category


template <typename T>
  struct is_iterator_category
    : HYDRA_EXTERNAL_NS::thrust::detail::or_<
        is_host_iterator_category<T>,
        is_device_iterator_category<T>
      >
{
}; // end is_iterator_category

} // end detail

} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust


HYDRA_EXTERNAL_NAMESPACE_END

