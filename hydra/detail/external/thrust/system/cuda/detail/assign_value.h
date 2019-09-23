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

#if HYDRA_THRUST_DEVICE_COMPILER == HYDRA_THRUST_DEVICE_COMPILER_NVCC
#include <hydra/detail/external/thrust/detail/config.h>
#include <hydra/detail/external/thrust/system/cuda/config.h>
#include <hydra/detail/external/thrust/system/cuda/detail/execution_policy.h>
#include <hydra/detail/external/thrust/detail/raw_pointer_cast.h>
#include <hydra/detail/external/thrust/system/cuda/detail/copy.h>

HYDRA_EXTERNAL_NAMESPACE_BEGIN

HYDRA_THRUST_BEGIN_NS
namespace cuda_cub {


template<typename DerivedPolicy, typename Pointer1, typename Pointer2>
inline __hydra_host__ __hydra_device__
  void assign_value(HYDRA_EXTERNAL_NS::thrust::cuda::execution_policy<DerivedPolicy> &exec, Pointer1 dst, Pointer2 src)
{
  // XXX war nvbugs/881631
  struct war_nvbugs_881631
  {
    __hydra_host__ inline static void host_path(HYDRA_EXTERNAL_NS::thrust::cuda::execution_policy<DerivedPolicy> &exec, Pointer1 dst, Pointer2 src)
    {
      cuda_cub::copy(exec, src, src + 1, dst);
    }

    __device__ inline static void device_path(HYDRA_EXTERNAL_NS::thrust::cuda::execution_policy<DerivedPolicy> &, Pointer1 dst, Pointer2 src)
    {
      *HYDRA_EXTERNAL_NS::thrust::raw_pointer_cast(dst) = *HYDRA_EXTERNAL_NS::thrust::raw_pointer_cast(src);
    }
  };

#ifndef __CUDA_ARCH__
  war_nvbugs_881631::host_path(exec,dst,src);
#else
  war_nvbugs_881631::device_path(exec,dst,src);
#endif // __CUDA_ARCH__
} // end assign_value()


template<typename System1, typename System2, typename Pointer1, typename Pointer2>
inline __hydra_host__ __hydra_device__
  void assign_value(cross_system<System1,System2> &systems, Pointer1 dst, Pointer2 src)
{
  // XXX war nvbugs/881631
  struct war_nvbugs_881631
  {
    __hydra_host__ inline static void host_path(cross_system<System1,System2> &systems, Pointer1 dst, Pointer2 src)
    {
      // rotate the systems so that they are ordered the same as (src, dst)
      // for the call to HYDRA_EXTERNAL_NS::thrust::copy
      cross_system<System2,System1> rotated_systems = systems.rotate();
      cuda_cub::copy(rotated_systems, src, src + 1, dst);
    }

    __device__ inline static void device_path(cross_system<System1,System2> &, Pointer1 dst, Pointer2 src)
    {
      // XXX forward the true cuda::execution_policy inside systems here
      //     instead of materializing a tag
      HYDRA_EXTERNAL_NS::thrust::cuda::tag cuda_tag;
      HYDRA_EXTERNAL_NS::thrust::cuda_cub::assign_value(cuda_tag, dst, src);
    }
  };

#if __CUDA_ARCH__
  war_nvbugs_881631::device_path(systems,dst,src);
#else
  war_nvbugs_881631::host_path(systems,dst,src);
#endif
} // end assign_value()



  
} // end cuda_cub
HYDRA_THRUST_END_NS

HYDRA_EXTERNAL_NAMESPACE_END

#endif
