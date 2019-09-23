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


/*! \file logical.h
 *  \brief Logical operations on ranges
 */

#pragma once

#include <hydra/detail/external/thrust/detail/config.h>
#include <hydra/detail/external/thrust/detail/execution_policy.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust
{


/*! \addtogroup reductions
 *  \{
 *  \addtogroup logical
 *  \ingroup reductions
 *  \{
 */


/*! \p all_of determines whether all elements in a range satify a predicate.
 *  Specifically, \p all_of returns \c true if <tt>pred(*i)</tt> is \c true
 *  for every iterator \c i in the range <tt>[first, last)</tt> and 
 *  \c false otherwise.
 *
 *  The algorithm's execution is parallelized as determined by \p exec.
 *
 *  \param exec The execution policy to use for parallelization.
 *  \param first The beginning of the sequence.
 *  \param last  The end of the sequence.
 *  \param pred A predicate used to test range elements.
 *  \return \c true, if all elements satisfy the predicate; \c false, otherwise.
 *
 *  \tparam DerivedPolicy The name of the derived execution policy.
 *  \tparam InputIterator is a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a>,
 *  \tparam Predicate must be a model of <a href="http://www.sgi.com/tech/stl/Predicate.html">Predicate</a>.
 *
 *  \code
 *  #include <hydra/detail/external/thrust/logical.h>
 *  #include <hydra/detail/external/thrust/functional.h>
 *  #include <hydra/detail/external/thrust/execution_policy.h>
 *  ...
 *  bool A[3] = {true, true, false};
 *
 *  HYDRA_EXTERNAL_NS::thrust::all_of(HYDRA_EXTERNAL_NS::thrust::host, A, A + 2, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns true
 *  HYDRA_EXTERNAL_NS::thrust::all_of(HYDRA_EXTERNAL_NS::thrust::host, A, A + 3, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *
 *  // empty range
 *  HYDRA_EXTERNAL_NS::thrust::all_of(HYDRA_EXTERNAL_NS::thrust::host, A, A, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *  
 *  \endcode
 *
 *  \see any_of
 *  \see none_of
 *  \see transform_reduce
 */
template<typename DerivedPolicy, typename InputIterator, typename Predicate>
__hydra_host__ __hydra_device__
bool all_of(const HYDRA_EXTERNAL_NS::thrust::detail::execution_policy_base<DerivedPolicy> &exec, InputIterator first, InputIterator last, Predicate pred);


/*! \p all_of determines whether all elements in a range satify a predicate.
 * Specifically, \p all_of returns \c true if <tt>pred(*i)</tt> is \c true
 * for every iterator \c i in the range <tt>[first, last)</tt> and 
 * \c false otherwise.
 *
 *  \param first The beginning of the sequence.
 *  \param last  The end of the sequence.
 *  \param pred A predicate used to test range elements.
 *  \return \c true, if all elements satisfy the predicate; \c false, otherwise.
 *
 *  \tparam InputIterator is a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a>,
 *  \tparam Predicate must be a model of <a href="http://www.sgi.com/tech/stl/Predicate.html">Predicate</a>.
 *
 *  \code
 *  #include <hydra/detail/external/thrust/logical.h>
 *  #include <hydra/detail/external/thrust/functional.h>
 *  ...
 *  bool A[3] = {true, true, false};
 *
 *  HYDRA_EXTERNAL_NS::thrust::all_of(A, A + 2, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns true
 *  HYDRA_EXTERNAL_NS::thrust::all_of(A, A + 3, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *
 *  // empty range
 *  HYDRA_EXTERNAL_NS::thrust::all_of(A, A, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *  
 *  \endcode
 *
 *  \see any_of
 *  \see none_of
 *  \see transform_reduce
 */
template<typename InputIterator, typename Predicate>
bool all_of(InputIterator first, InputIterator last, Predicate pred);


/*! \p any_of determines whether any element in a range satifies a predicate.
 *  Specifically, \p any_of returns \c true if <tt>pred(*i)</tt> is \c true
 *  for any iterator \c i in the range <tt>[first, last)</tt> and 
 *  \c false otherwise.
 *
 *  The algorithm's execution is parallelized as determined by \p exec.
 *
 *  \param exec The execution policy to use for parallelization.
 *  \param first The beginning of the sequence.
 *  \param last  The end of the sequence.
 *  \param pred A predicate used to test range elements.
 *  \return \c true, if any element satisfies the predicate; \c false, otherwise.
 *
 *  \tparam DerivedPolicy The name of the derived execution policy.
 *  \tparam InputIterator is a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a>,
 *  \tparam Predicate must be a model of <a href="http://www.sgi.com/tech/stl/Predicate.html">Predicate</a>.
 *
 *  \code
 *  #include <hydra/detail/external/thrust/logical.h>
 *  #include <hydra/detail/external/thrust/functional.h>
 *  #include <hydra/detail/external/thrust/execution_policy.h>
 *  ...
 *  bool A[3] = {true, true, false};
 *
 *  HYDRA_EXTERNAL_NS::thrust::any_of(HYDRA_EXTERNAL_NS::thrust::host, A, A + 2, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns true
 *  HYDRA_EXTERNAL_NS::thrust::any_of(HYDRA_EXTERNAL_NS::thrust::host, A, A + 3, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns true
 *
 *  HYDRA_EXTERNAL_NS::thrust::any_of(HYDRA_EXTERNAL_NS::thrust::host, A + 2, A + 3, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *
 *  // empty range
 *  HYDRA_EXTERNAL_NS::thrust::any_of(HYDRA_EXTERNAL_NS::thrust::host, A, A, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *  \endcode
 *
 *  \see all_of
 *  \see none_of
 *  \see transform_reduce
 */
template<typename DerivedPolicy, typename InputIterator, typename Predicate>
__hydra_host__ __hydra_device__
bool any_of(const HYDRA_EXTERNAL_NS::thrust::detail::execution_policy_base<DerivedPolicy> &exec, InputIterator first, InputIterator last, Predicate pred);
   

/*! \p any_of determines whether any element in a range satifies a predicate.
 * Specifically, \p any_of returns \c true if <tt>pred(*i)</tt> is \c true
 * for any iterator \c i in the range <tt>[first, last)</tt> and 
 * \c false otherwise.
 *
 *  \param first The beginning of the sequence.
 *  \param last  The end of the sequence.
 *  \param pred A predicate used to test range elements.
 *  \return \c true, if any element satisfies the predicate; \c false, otherwise.
 *
 *  \tparam InputIterator is a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a>,
 *  \tparam Predicate must be a model of <a href="http://www.sgi.com/tech/stl/Predicate.html">Predicate</a>.
 *
 *  \code
 *  #include <hydra/detail/external/thrust/logical.h>
 *  #include <hydra/detail/external/thrust/functional.h>
 *  ...
 *  bool A[3] = {true, true, false};
 *
 *  HYDRA_EXTERNAL_NS::thrust::any_of(A, A + 2, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns true
 *  HYDRA_EXTERNAL_NS::thrust::any_of(A, A + 3, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns true
 *
 *  HYDRA_EXTERNAL_NS::thrust::any_of(A + 2, A + 3, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *
 *  // empty range
 *  HYDRA_EXTERNAL_NS::thrust::any_of(A, A, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *  \endcode
 *
 *  \see all_of
 *  \see none_of
 *  \see transform_reduce
 */
template<typename InputIterator, typename Predicate>
bool any_of(InputIterator first, InputIterator last, Predicate pred);


/*! \p none_of determines whether no element in a range satifies a predicate.
 *  Specifically, \p none_of returns \c true if there is no iterator \c i in 
 *  the range <tt>[first, last)</tt> such that <tt>pred(*i)</tt> is \c true,
 *  and \c false otherwise.
 *
 *  The algorithm's execution is parallelized as determined by \p exec.
 *
 *  \param exec The execution policy to use for parallelization.
 *  \param first The beginning of the sequence.
 *  \param last  The end of the sequence.
 *  \param pred A predicate used to test range elements.
 *  \return \c true, if no element satisfies the predicate; \c false, otherwise.
 *
 *  \tparam DerivedPolicy The name of the derived execution policy.
 *  \tparam InputIterator is a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a>,
 *  \tparam Predicate must be a model of <a href="http://www.sgi.com/tech/stl/Predicate.html">Predicate</a>.
 *
 *  \code
 *  #include <hydra/detail/external/thrust/logical.h>
 *  #include <hydra/detail/external/thrust/functional.h>
 *  #include <hydra/detail/external/thrust/execution_policy.h>
 *  ...
 *  bool A[3] = {true, true, false};
 *
 *  HYDRA_EXTERNAL_NS::thrust::none_of(HYDRA_EXTERNAL_NS::thrust::host, A, A + 2, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *  HYDRA_EXTERNAL_NS::thrust::none_of(HYDRA_EXTERNAL_NS::thrust::host, A, A + 3, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *
 *  HYDRA_EXTERNAL_NS::thrust::none_of(HYDRA_EXTERNAL_NS::thrust::host, A + 2, A + 3, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns true
 *
 *  // empty range
 *  HYDRA_EXTERNAL_NS::thrust::none_of(HYDRA_EXTERNAL_NS::thrust::host, A, A, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns true
 *  \endcode
 *
 *  \see all_of
 *  \see any_of
 *  \see transform_reduce
 */
template<typename DerivedPolicy, typename InputIterator, typename Predicate>
__hydra_host__ __hydra_device__
bool none_of(const HYDRA_EXTERNAL_NS::thrust::detail::execution_policy_base<DerivedPolicy> &exec, InputIterator first, InputIterator last, Predicate pred);


/*! \p none_of determines whether no element in a range satifies a predicate.
 *  Specifically, \p none_of returns \c true if there is no iterator \c i in 
 *  the range <tt>[first, last)</tt> such that <tt>pred(*i)</tt> is \c true,
 *  and \c false otherwise.
 *
 *  \param first The beginning of the sequence.
 *  \param last  The end of the sequence.
 *  \param pred A predicate used to test range elements.
 *  \return \c true, if no element satisfies the predicate; \c false, otherwise.
 *
 *  \tparam InputIterator is a model of <a href="http://www.sgi.com/tech/stl/InputIterator.html">Input Iterator</a>,
 *  \tparam Predicate must be a model of <a href="http://www.sgi.com/tech/stl/Predicate.html">Predicate</a>.
 *
 *  \code
 *  #include <hydra/detail/external/thrust/logical.h>
 *  #include <hydra/detail/external/thrust/functional.h>
 *  ...
 *  bool A[3] = {true, true, false};
 *
 *  HYDRA_EXTERNAL_NS::thrust::none_of(A, A + 2, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *  HYDRA_EXTERNAL_NS::thrust::none_of(A, A + 3, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns false
 *
 *  HYDRA_EXTERNAL_NS::thrust::none_of(A + 2, A + 3, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns true
 *
 *  // empty range
 *  HYDRA_EXTERNAL_NS::thrust::none_of(A, A, HYDRA_EXTERNAL_NS::thrust::identity<bool>()); // returns true
 *  \endcode
 *
 *  \see all_of
 *  \see any_of
 *  \see transform_reduce
 */
template<typename InputIterator, typename Predicate>
bool none_of(InputIterator first, InputIterator last, Predicate pred);


/*! \} // end logical
 *  \} // end reductions
 */


} // end HYDRA_EXTERNAL_NAMESPACE_BEGIN  namespace thrust

HYDRA_EXTERNAL_NAMESPACE_END


#include <hydra/detail/external/thrust/detail/logical.inl>

