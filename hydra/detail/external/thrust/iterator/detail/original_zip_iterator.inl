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

#include <hydra/detail/external/thrust/iterator/zip_iterator.h>
#include <hydra/detail/external/thrust/detail/tuple_transform.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{


template<typename IteratorTuple>
__hydra_host__ __hydra_device__
  zip_iterator<IteratorTuple>
    ::zip_iterator()
{
} // end zip_iterator::zip_iterator()


template<typename IteratorTuple>
__hydra_host__ __hydra_device__
  zip_iterator<IteratorTuple>
    ::zip_iterator(IteratorTuple iterator_tuple)
      :m_iterator_tuple(iterator_tuple)
{
} // end zip_iterator::zip_iterator()


template<typename IteratorTuple>
  template<typename OtherIteratorTuple>
  __hydra_host__ __hydra_device__
    zip_iterator<IteratorTuple>
      ::zip_iterator(const zip_iterator<OtherIteratorTuple> &other,
                     typename HYDRA_EXTERNAL_NS::thrust::detail::enable_if_convertible<
                       OtherIteratorTuple,
                       IteratorTuple
                     >::type *)
        :m_iterator_tuple(other.get_iterator_tuple())
{
} // end zip_iterator::zip_iterator()


template<typename IteratorTuple>
__hydra_host__ __hydra_device__
const IteratorTuple &zip_iterator<IteratorTuple>
  ::get_iterator_tuple() const
{
  return m_iterator_tuple;
} // end zip_iterator::get_iterator_tuple()


template<typename IteratorTuple>
  typename zip_iterator<IteratorTuple>::super_t::reference
  __hydra_host__ __hydra_device__
    zip_iterator<IteratorTuple>
      ::dereference() const
{
  using namespace detail::tuple_impl_specific;

  return HYDRA_EXTERNAL_NS::thrust::detail::tuple_host_device_transform<
    detail::dereference_iterator::template apply
  >(get_iterator_tuple(), detail::dereference_iterator());
} // end zip_iterator::dereference()


__thrust_exec_check_disable__
template<typename IteratorTuple>
  template<typename OtherIteratorTuple>
  __hydra_host__ __hydra_device__
    bool zip_iterator<IteratorTuple>
      ::equal(const zip_iterator<OtherIteratorTuple> &other) const
{
  return get<0>(get_iterator_tuple()) == get<0>(other.get_iterator_tuple());
} // end zip_iterator::equal()


template<typename IteratorTuple>
__hydra_host__ __hydra_device__
  void zip_iterator<IteratorTuple>
    ::advance(typename super_t::difference_type n)
{
  using namespace detail::tuple_impl_specific;
  tuple_for_each(m_iterator_tuple,
                 detail::advance_iterator<typename super_t::difference_type>(n));
} // end zip_iterator::advance()


template<typename IteratorTuple>
__hydra_host__ __hydra_device__
  void zip_iterator<IteratorTuple>
    ::increment()
{
  using namespace detail::tuple_impl_specific;
  tuple_for_each(m_iterator_tuple, detail::increment_iterator());
} // end zip_iterator::increment()


template<typename IteratorTuple>
__hydra_host__ __hydra_device__
  void zip_iterator<IteratorTuple>
    ::decrement()
{
  using namespace detail::tuple_impl_specific;
  tuple_for_each(m_iterator_tuple, detail::decrement_iterator());
} // end zip_iterator::decrement()


__thrust_exec_check_disable__
template<typename IteratorTuple>
  template <typename OtherIteratorTuple>
  __hydra_host__ __hydra_device__
    typename zip_iterator<IteratorTuple>::super_t::difference_type
      zip_iterator<IteratorTuple>
        ::distance_to(const zip_iterator<OtherIteratorTuple> &other) const
{
  return get<0>(other.get_iterator_tuple()) - get<0>(get_iterator_tuple());
} // end zip_iterator::distance_to()


template<typename IteratorTuple>
__hydra_host__ __hydra_device__
  zip_iterator<IteratorTuple> make_zip_iterator(IteratorTuple t)
{
  return zip_iterator<IteratorTuple>(t);
} // end make_zip_iterator()


} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust


HYDRA_EXTERNAL_NAMESPACE_END

