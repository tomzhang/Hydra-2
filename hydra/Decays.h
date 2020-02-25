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
 * Decays.h
 *
 *  Created on: 24/02/2020
 *      Author: Antonio Augusto Alves Junior
 */

#ifndef DECAYS_H_
#define DECAYS_H_

#include <hydra/detail/Config.h>
#include <hydra/detail/BackendPolicy.h>
#include <hydra/Vector3R.h>
#include <hydra/Vector4R.h>
#include <hydra/multivector.h>
#include <hydra/Tuple.h>

namespace hydra {

/**
* \ingroup phsp
*/
template<typename Particles,  typename Backend>
class Decays;

/**
 * \ingroup phsp
 * \brief This class provides storage for N-particle states. Data is stored using SoA layout.
 * \tparam Particles list of particles in the final state
 * \tparam Backend memory space to allocate storage for the particles.
 */
template<typename ...Particles,   hydra::detail::Backend Backend>
class Decays<hydra::tuple<Particles...>, hydra::detail::BackendPolicy<Backend>>
{
	typedef hydra::detail::BackendPolicy<Backend>  system_type;
	typedef hydra_thrust::tuple<Particles...>       tuple_type;
	typedef multivector<tuple_type, system_type>  storage_type;

public :

	typedef typename storage_type::value_type                          value_type;
	typedef typename storage_type::reference_type                       reference;
	typedef typename storage_type::const_reference_type           const_reference;
	typedef typename storage_type::iterator                              iterator;
	typedef typename storage_type::const_iterator                  const_iterator;
	typedef typename storage_type::reverse_iterator              reverse_iterator;
	typedef typename storage_type::const_reverse_iterator  const_reverse_iterator;



	/**
	 * Default contstuctor
	 */
	Decays():
		fDecays()
	{}

	/**
	 * Constructor with n decays.
	 * @param n number of entries.
	 */
	Decays(size_t n):
		fDecays(n)
	{}

	/**
	 * Copy constructor.
	 * @param other
	 */
	Decays(Decays<tuple_type, system_type> const& other ):
		fDecays(other)
	{}

	/**
	 * Move constructor.
	 * @param other
	 */
	Decays(Decays<tuple_type, system_type>&& other ):
		fDecays( std::move(other) )
	{}

	/**
	 * Copy constructor trans-backend
	 * @param other
	 */
	template< hydra::detail::Backend BACKEND2>
	Decays(Decays<tuple_type, detail::BackendPolicy<BACKEND2>> const& other ):
	fDecays(other)
	{}

	/**
	 * Copy constructor iterator interface
	 * @param other
	 */
	template<typename Iterator>
	Decays( Iterator first, Iterator  last )
	{
		size_t n = hydra_thrust::distance(first, last);

		fDecays.resize(n);

		hydra_thrust::copy(first, last, this->begin());
	}

	/**
	 * Add a decay to the container, increasing
	 * its size by one element.
	 * @param p is a tuple with N final state particles.
	 */
	void AddEntry( tuple_type const& p )
	{
		fDecays.push_back( decay );
	}


	reference_type GetEntry( size_t i )
	{
		return fDecays[i];
	}

	//----------------------------------------
	//  stl compliant interface
	//----------------------------------------
	inline void pop_back() { fDecays.pop_back(); }

	inline void push_back(const value_type& particles){ fDecays.push_back( particles ); }

	void resize(size_t size){ fDecays.resize(size); }

	void clear(){ fDecays.clear(); }

	void shrink_to_fit() { fDecays.shrink_to_fit(); }

	void reserve(size_t size) { fDecays.reserve(size); }

	size_t size() const{return fDecays.size(); }

	size_t capacity() const{return fDecays.capacity();}

	bool empty() const{	return fDecays.empty(); }

	iterator erase(iterator pos) {
		return fDecays.erase(pos);
	}

	iterator erase(iterator first, iterator last){
		return fDecays.erase( first, last);
	}

	iterator insert(iterator position, const value_type &x){
		return fDecays.insert(position, x);
	}

	void insert(iterator position, size_type n, const value_type &x){
		fDecays.insert(position,n,x );
	}


	template<typename InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last){
		fDecays.insert(position, first, last );
	}

	template<typename Iterable>
	typename std::enable_if<detail::is_iterable<Iterable>::value, void>::type
	insert(iterator position, Iterable range){
		fDecays.insert( position, range);
	}

	reference front(){	return this->begin()[0];}

	const_reference front() const  {return this->cbegin()[0];}

	reference back(){return  this->begin()[this->size() - 1];}

	const_reference back() const{return  this->cbegin()[this->size() - 1]; }

	//converting access
	template<typename Functor>
	__caster_iterator<iterator, value_type, Functor>
	begin( Functor const& caster )
	{ return __begin(caster);}

	template<typename Functor>
	__caster_iterator<iterator, value_type, Functor>
	end( Functor const& caster )
	{ return __end(caster);}

	template<typename Functor>
	__caster_iterator<reverse_iterator, value_type, Functor>
	rbegin( Functor const& caster )
	{ return __rbegin(caster);}

	template<typename Functor>
	__caster_iterator<reverse_iterator, value_type, Functor>
	rend( Functor const& caster )
	{ return __rend(caster);}

	//non-constant access
	iterator begin(){ return __begin(); }

	iterator end(){ return __end(); }

	reverse_iterator rbegin(){ return __rbegin(); }

	reverse_iterator rend(){ return __rend(); }

	//constant access
	const_iterator begin() const {return __begin();}

	const_iterator end() const { return __end(); }

	const_reverse_iterator rbegin() const { return __rbegin();}

	const_reverse_iterator rend() const { return __rend();}

	const_iterator cbegin() const { return __cbegin(); }

	const_iterator cend() const { return __cend(); }

	const_reverse_iterator crbegin() const { return __crbegin(); }

	const_reverse_iterator crend() const { return  __crend();}

	inline	reference operator[](size_t n)
	{	return begin()[n] ;	}

	inline const_reference operator[](size_t n) const
	{	return cbegin()[n]; }






	/**
	 * Assignment operator.
	 * @param other
	 */
	Decays<tuple_type, system_type>&
	operator=(Decays<N,detail::BackendPolicy<BACKEND>> const& other )
	{
		if(this==&other) return *this;

		fDecays  = other.GetDecays();

		return *this;
	}

	/**
	 * Move assignment operator.
	 * @param other
	 * @return
	 */
	Decays<tuple_type, system_type>&
	operator=(Decays<tuple_type, system_type>&& other )
	{
		if(this==&other) return *this;

		this->fDecays  = other.MoveDecays();

		return *this;
	}


	/**
	 * Assignment operator.
	 * @param other
	 * @return
	 */
	template< hydra::detail::Backend BACKEND2>
	Decays<N,detail::BackendPolicy<BACKEND> >&
	operator=(Decays<N,detail::BackendPolicy<BACKEND2> > const& other )
	{
		size_t n = hydra_thrust::distance(first, last);

		fDecays.resize(n);

		hydra_thrust::copy(other.begin(),  other.end(), this->begin() );

		return *this;
	}



protected:

	const storage_type& GetDecays() const
	{
		return fDecays;
	}

	storage_type&& MoveDecays() const
	{
		return std::move(fDecays);
	}



private:

  storage_type  fDecays;

};


}  // namespace hydra



#endif /* DECAYS_H_ */
