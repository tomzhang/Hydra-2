/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2016-2017 Antonio Augusto Alves Junior
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
 * ThreeBodyMassThresholdBackground.h
 *
 *  Created on: 01/08/2018
 *      Author: Antonio Augusto Alves Junior
 *
 *  Updated on: Feb 21 2020
 *      Author: Davide Brundu
 *         Log: Update call interface
 */

#ifndef THREEBODYMASSTHRESHOLDBACKGROUND_H_
#define THREEBODYMASSTHRESHOLDBACKGROUND_H_

#include <hydra/detail/Config.h>
#include <hydra/detail/BackendPolicy.h>
#include <hydra/Types.h>
#include <hydra/Function.h>
#include <hydra/Pdf.h>
#include <hydra/Integrator.h>
#include <hydra/detail/utility/CheckValue.h>
#include <hydra/Parameter.h>
#include <hydra/Tuple.h>
#include <tuple>
#include <limits>
#include <stdexcept>
#include <cassert>
#include <utility>

namespace hydra {
/**
 * \ingroup common_functions
 * \class ThreeBodyMassThresholdBackground
 *
 */
template<typename ArgType, typename Signature=double(ArgType)>
class ThreeBodyMassThresholdBackground: public BaseFunctor<ThreeBodyMassThresholdBackground<ArgType>, Signature, 4>
{
	using BaseFunctor<ThreeBodyMassThresholdBackground<ArgType>, Signature, 4>::_par;

public:

	ThreeBodyMassThresholdBackground() = delete;

	ThreeBodyMassThresholdBackground(Parameter const& threshold, Parameter const& A, Parameter const& B, Parameter const& C):
		BaseFunctor<ThreeBodyMassThresholdBackground<ArgType>, Signature, 4>({threshold, A, B, C})
		{}

	__hydra_host__ __hydra_device__
	ThreeBodyMassThresholdBackground(ThreeBodyMassThresholdBackground<ArgType> const& other ):
	BaseFunctor<ThreeBodyMassThresholdBackground<ArgType>, Signature, 4>(other)
	{}

	__hydra_host__ __hydra_device__
	ThreeBodyMassThresholdBackground<ArgType>&
	operator=(ThreeBodyMassThresholdBackground<ArgType> const& other ){
		if(this==&other) return  *this;
		BaseFunctor<ThreeBodyMassThresholdBackground<ArgType>, Signature, 4>::operator=(other);
		return  *this;
	}

	__hydra_host__ __hydra_device__
	inline double Evaluate(ArgType x)  const	{

		double arg   = (x - _par[0]);
		double ratio = (arg/_par[0]);
		double val   = arg>0 ? (1- ::exp(-arg/_par[3]))*::pow(ratio, _par[1]) + _par[2]*(ratio-1) : 0;

		return  CHECK_VALUE( (val>0 ? val : 0), "par[0]=%f, par[1]=%f, par[2]=%f, par[3]=%f ", _par[0], _par[1], _par[2], _par[3]);

	}



};



}  // namespace hydra

#endif /* THREEBODYMASSTHRESHOLDBACKGROUND_H_ */
