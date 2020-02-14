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
 * StaticAssert.h
 *
 *  Created on: 09/02/2020
 *      Author: Antonio Augusto Alves Junior
 */

#ifndef STATICASSERT_H_
#define STATICASSERT_H_

#define HYDRA_STATIC_ASSERT(condition, message)\
static_assert(condition,\
"\n\n"\
"|++++++++++++++< HYDRA STATIC ASSERTION FAILED >++++++++++++++|\n"\
"| Error : " message"\n"\
"|+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++|\n"\
"\n\n" );


#endif /* STATICASSERT_H_ */
