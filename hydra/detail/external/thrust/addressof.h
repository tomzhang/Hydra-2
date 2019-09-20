// Copyright (c) 2018 NVIDIA Corporation
// Author: Bryce Adelstein Lelbach <brycelelbach@gmail.com>
//
// Distributed under the Boost Software License v1.0 (boost.org/LICENSE_1_0.txt)

#pragma once

#include <hydra/detail/external/thrust/detail/config.h>

#if THRUST_CPP_DIALECT >= 2011
#  include <memory>
#endif
HYDRA_EXTERNAL_NAMESPACE_BEGIN
THRUST_BEGIN_NS

///////////////////////////////////////////////////////////////////////////////

/*! Obtains the actual address of the object or function arg, even in presence of overloaded operator&.
 */
template <typename T>
__hydra_host__ __hydra_device__
T* addressof(T& arg) 
{
  return reinterpret_cast<T*>(
    &const_cast<char&>(reinterpret_cast<const volatile char&>(arg))
  );
}

///////////////////////////////////////////////////////////////////////////////

THRUST_END_NS
HYDRA_EXTERNAL_NAMESPACE_END
