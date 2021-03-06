/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2016 - 2020 Antonio Augusto Alves Junior
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
 * genz_malik.inl
 *
 *  Created on: 10/08/2018
 *      Author: Antonio Augusto Alves Junior
 */

#ifndef GENZ_MALIK_INL_
#define GENZ_MALIK_INL_


/**
 * \example plain_mc.inl
 * This example show how to use the hydra::Plain
 * numerical integration algorithm to calculate
 * the integral of a five dimensional Gaussian.
 */

#include <iostream>
#include <assert.h>
#include <time.h>
#include <string>
#include <vector>
#include <array>
#include <chrono>
#include <limits>


//command line arguments
#include <tclap/CmdLine.h>

//this lib
#include <hydra/Types.h>

#include <hydra/Function.h>
#include <hydra/FunctorArithmetic.h>
#include <hydra/Plain.h>
#include <hydra/GenzMalikQuadrature.h>
#include <hydra/Lambda.h>
#include <hydra/host/System.h>
#include <hydra/device/System.h>



int main(int argv, char** argc)
{

	size_t  boxes  = 0;

	try {

		TCLAP::CmdLine cmd("Command line arguments for plain mc", '=');

		TCLAP::ValueArg<size_t> NCallsArg("n", "number-of-hyperboxes", "Number of hyperboxes", true, 1, "size_t");
		cmd.add(NCallsArg);

		cmd.parse(argv, argc);

		// Get the value parsed by each arg.
		boxes   = NCallsArg.getValue();

	}
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	//number of dimensions (user can change it)
	constexpr size_t N = 2;

	//integration region limits
	double  min[N];
	double  max[N];

    //5D Gaussian parameters
	double mean  = 0.0;
	double sigma = 1.0;

	//set Gaussian parameters and
	//integration region limits
	for(size_t i=0; i< N; i++){
		min[i]   = -6.0;
		max[i]   =  6.0;
	}

	// create functor using C++11 lambda
	auto GAUSSIAN = [=] __hydra_dual__ (unsigned int n, double* x ){

		double g = 1.0;
		double f = 0.0;

		for(size_t i=0; i<N; i++){
			double m2 = (x[i] - mean )*(x[i] - mean );
			double s2 = sigma*sigma;
			f = exp(-m2/(2.0 * s2 ))/( sqrt(2.0*s2*PI));
			g *= f;
		}

		return g;
	};

	//wrap the lambda
    auto gaussian = hydra::wrap_lambda(GAUSSIAN);

    //device
    {
    	//----------------------------------------------------------------------
    	//Genz-Malik integrator
    	hydra::GenzMalikQuadrature<N,  hydra::device::sys_t > GM_d(min, max, boxes, 0.5);

    	auto start = std::chrono::high_resolution_clock::now();

    	auto result = GM_d.Integrate(gaussian);

    	auto end = std::chrono::high_resolution_clock::now();

    	std::chrono::duration<double, std::milli> elapsed = end - start;

    	std::cout << std::endl;
    	std::cout << "----------------- Device ----------------"<< std::endl;
    	std::cout << ">>> [Genz-Malik]: Gaussian<"<< N << ">" << std::endl;
    	std::cout << "Result: "    << result.first << " +/- " << result.second <<std::endl
				  << "Time (ms): " << elapsed.count() <<std::endl;
    	std::cout << "-----------------------------------------"<< std::endl;

    }


	return 0;


	}



#endif /* GENZ_MALIK_INL_ */
