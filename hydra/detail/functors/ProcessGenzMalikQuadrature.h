/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2016 - 2018 Antonio Augusto Alves Junior
 *
 *   This file is part of Hydra Data Analysis Framework.
 *
 *   Hydra is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hydra is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hydra.  If not, see <http://www.gnu.org/licenses/>.
 *
 *---------------------------------------------------------------------------*/

/*
 * ProcessGenzMalikQuadrature.h
 *
 *  Created on: 17/03/2017
 *      Author: Antonio Augusto Alves Junior
 */

#ifndef PROCESSGENZMALIKQUADRATURE_H_
#define PROCESSGENZMALIKQUADRATURE_H_

#include <hydra/detail/Config.h>
#include <hydra/Types.h>
#include <hydra/Containers.h>
#include <hydra/detail/utility/Utility_Tuple.h>
#include <hydra/detail/utility/Generic.h>
#include <hydra/detail/GenzMalikBox.h>
#include <hydra/GenzMalikQuadrature.h>
#include <hydra/detail/TypeTraits.h>
#include <hydra/detail/utility/Arithmetic_Tuple.h>
#include <hydra/detail/Argument.h>
#include <hydra/detail/external/thrust/functional.h>
#include <hydra/detail/external/thrust/transform_reduce.h>
#include <hydra/detail/external/thrust/reduce.h>
#include <hydra/detail/external/thrust/transform.h>
#include <hydra/detail/external/thrust/functional.h>
#include <hydra/detail/external/thrust/copy.h>
#include <hydra/detail/external/thrust/execution_policy.h>





namespace hydra {


namespace detail {


template<  size_t N, typename FUNCTOR>
struct ProcessGenzMalikUnaryCall
{

	typedef typename hydra::detail::tuple_type<N  ,double>::type abscissa_type;
	typedef typename hydra::detail::tuple_type<N+2,double>::type result_type;

	ProcessGenzMalikUnaryCall()=delete;

	ProcessGenzMalikUnaryCall(const double (&lowerLimit)[N], const double (&upperLimit)[N],
			FUNCTOR const& functor):
				fFunctor(functor){

		for(size_t i=0; i<N; i++)
		{
			fA[i] = (upperLimit[i] - lowerLimit[i])/2.0;
			fB[i] = (upperLimit[i] + lowerLimit[i])/2.0;

		}
	}

	__hydra_host__ __hydra_device__
	ProcessGenzMalikUnaryCall(ProcessGenzMalikUnaryCall< N, FUNCTOR> const& other ):
	fFunctor(other.GetFunctor())
	{
		for(size_t i=0; i<N; i++)
		{
			this->fA[i]=other.fA[i];
			this->fB[i]=other.fB[i];
		}
	}

	__hydra_host__ __hydra_device__
	ProcessGenzMalikUnaryCall< N, FUNCTOR>&
	operator=(ProcessGenzMalikUnaryCall< N, FUNCTOR> const& other )
	{
		if( this== &other) return *this;

		fFunctor=other.GetFunctor();

		for(size_t i=0; i<N; i++)
		{
			this->fA[i]=other.fA[i];
			this->fB[i]=other.fB[i];
		}

		return *this;
	}

	template<typename T>
	__hydra_host__ __hydra_device__
	inline result_type operator()(T&& rule_abscissa)
	{

        auto rule5_weight            = HYDRA_EXTERNAL_NS::thrust::get<0>(rule_abscissa);
        auto rule7_weight            = HYDRA_EXTERNAL_NS::thrust::get<1>(rule_abscissa);
		auto four_difference_weight  = HYDRA_EXTERNAL_NS::thrust::get<2>(rule_abscissa);

		abscissa_type args{};
		get_transformed_abscissa( rule_abscissa, args  );

		int four_diff_index = get_dim(args);

		double _temp[N+2]{0};
		double fval  = fFunctor(args);

		_temp[0]      = fval*HYDRA_EXTERNAL_NS::thrust::get<1>(rule_abscissa);//w7;
		_temp[1]      = fval*HYDRA_EXTERNAL_NS::thrust::get<0>(rule_abscissa);//w5;
		_temp[four_diff_index]  = fval*HYDRA_EXTERNAL_NS::thrust::get<3>(rule_abscissa);//w_four_diff;


		return hydra::detail::arrayToTuple<GReal_t, N+2>(&_temp[0]);;
	}


	__hydra_host__ __hydra_device__
	inline FUNCTOR GetFunctor() const {
		return fFunctor;
	}

	__hydra_host__ __hydra_device__
	inline void SetFunctor(FUNCTOR functor) {
		fFunctor = functor;
	}


	template<typename Abscissa, typename TransAbscissa , size_t I>
	__hydra_host__ __hydra_device__
	inline typename std::enable_if< (I== HYDRA_EXTERNAL_NS::thrust::tuple_size<TransAbscissa>::value), void  >::type
	get_transformed_abscissa( Abscissa const& ,  TransAbscissa& ){}

	template<typename Abscissa, typename TransAbscissa , size_t I=0>
	__hydra_host__ __hydra_device__
	inline typename std::enable_if< (I < HYDRA_EXTERNAL_NS::thrust::tuple_size<TransAbscissa>::value), void  >::type
	get_transformed_abscissa(  Abscissa const& abscissa, TransAbscissa& transformed_abscissa  )
	{

		HYDRA_EXTERNAL_NS::thrust::get<I>(transformed_abscissa)  =
				fA[I]*HYDRA_EXTERNAL_NS::thrust::get<2>( abscissa )*HYDRA_EXTERNAL_NS::thrust::get<I+3>( abscissa )+ fB[I];

		get_transformed_abscissa<Abscissa,TransAbscissa,I+1>(original_abscissa, transformed_abscissa );
	}


	template<typename T, int I>
	typename std::enable_if< (I==HYDRA_EXTERNAL_NS::thrust::tuple_size<T>::value),void >::type
	get_dim_helper( T const&, int& ){ }

	template<typename T, int I=0>
	typename std::enable_if< (I< HYDRA_EXTERNAL_NS::thrust::tuple_size<T>::value),void >::type
	get_dim_helper( T const& X, int& result ){

		result += HYDRA_EXTERNAL_NS::thrust::get<I>(X) ? I : 0;
		get_dim_helper<T, I+1>(X, result );

	}

	template<typename T,  size_t I=0>
	int get_dim( T const& X){

		int result = 0;
		get_dim_helper(X , result );

		return result< HYDRA_EXTERNAL_NS::thrust::tuple_size<T>::value ? result : -1;
	}


	__hydra_host__ __hydra_device__ inline
	GBool_t set_four_difference_central(GReal_t value,  GReal_t * const __restrict__ fdarray)
	{


		for(size_t i=0; i<N; i++)
			fdarray[i]=value;
return 1;
	}

	__hydra_host__ __hydra_device__ inline
	GBool_t set_four_difference_unilateral(GChar_t index, GReal_t value, GReal_t* const __restrict__  fdarray)
	{

		for(size_t i=0; i<N; i++)
		fdarray[i]= ((size_t)index==i)?value:0.0;

		return 1;
	}

	__hydra_host__ __hydra_device__ inline
	GBool_t set_four_difference_multilateral( GReal_t * const __restrict__ fdarray)
		{

			for(size_t i=0; i<N; i++)
			fdarray[i]= 0.0;
			return 1;
		}

	FUNCTOR fFunctor;
	GReal_t fA[N];
	GReal_t fB[N];

};

//-----------------------------------------------------
//
//
//-----------------------------------------------------

template< size_t N>
struct ProcessGenzMalikBinaryCall:
		public HYDRA_EXTERNAL_NS::thrust::binary_function< typename hydra::detail::tuple_type<N+2, GReal_t>::type ,
		                                typename hydra::detail::tuple_type<N+2, GReal_t>::type,
		                                typename hydra::detail::tuple_type<N+2, GReal_t>::type      >
{

	__hydra_host__ __hydra_device__
	inline typename hydra::detail::tuple_type<N+2, GReal_t>::type
	operator()(typename hydra::detail::tuple_type<N+2, GReal_t>::type box1,
			typename hydra::detail::tuple_type<N+2, GReal_t>::type box2)
	{

		return hydra::detail::addTuples(box1, box2 );

	}

};


template<  size_t N, typename FUNCTOR, typename  BACKEND>
struct ProcessGenzMalikBox;

template <size_t N, typename FUNCTOR, typename RuleIterator , hydra::detail::Backend  BACKEND>
struct ProcessGenzMalikBox<N, FUNCTOR,hydra::detail::BackendPolicy<BACKEND> >
{

	typedef hydra::detail::BackendPolicy<BACKEND> system_type;

	ProcessGenzMalikBox()=delete;

	ProcessGenzMalikBox(FUNCTOR const& functor, RuleIterator begin, RuleIterator end):
			fFunctor(functor),
			fRuleBegin(begin),
			fRuleEnd(end)
		{}

	__hydra_host__ __hydra_device__
	ProcessGenzMalikBox(ProcessGenzMalikBox< N, FUNCTOR, RuleIterator,BoxIterator > const& other ):
	fFunctor(other.fFunctor),
	fRuleBegin(other.fRuleBegin),
	fRuleEnd(other.fRuleEnd)
	{}

	__hydra_host__ __hydra_device__ inline
	ProcessGenzMalikBox< N, FUNCTOR, RuleIterator,BoxIterator >&
	operator=(ProcessGenzMalikBox< N, FUNCTOR, RuleIterator,BoxIterator > const& other )
	{
		if( this== &other) return *this;

		fFunctor=other.fFunctor;
	    fRuleBegin=other.fRuleBegin;
		fRuleEnd=other.fRuleEnd;

		return *this;
	}

	__hydra_host__ __hydra_device__
	inline void operator()(GenzMalikBox<N>& hyperbox)
	{
		typedef typename hydra::detail::tuple_type<N+2, GReal_t>::type tuple_t;
		using HYDRA_EXTERNAL_NS::thrust::transform_reduce;

		auto box_result =
				transform_reduce(system_type, fRuleBegin, fRuleEnd,
				ProcessGenzMalikUnaryCall<N, FUNCTOR>(hyperbox.GetLowerLimit(), hyperbox.GetUpperLimit(), fFunctor),
				tuple_t() ,
				ProcessGenzMalikBinaryCall<N>());

		fBoxBegin[index]=box_result;

	}

	FUNCTOR fFunctor;
	RuleIterator fRuleBegin;
	RuleIterator fRuleEnd;


};



}  // namespace detail


} // namespace hydra

#endif /* PROCESSGENZMALIKQUADRATURE_H_ */
