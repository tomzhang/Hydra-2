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
 * Range.h
 *
 *  Created on: 29/08/2017
 *      Author: Antonio Augusto Alves Junior
 */

#ifndef RANGE1_INL_
#define RANGE1_INL_

#include <hydra/detail/Config.h>
#include <hydra/detail/BackendPolicy.h>
#include <hydra/Distance.h>
#include <hydra/detail/external/thrust/iterator/iterator_traits.h>


namespace hydra {

template<typename Iterator>
class Range<Iterator>{

public:
	//stl-like typedefs
	typedef typename HYDRA_EXTERNAL_NS::thrust::iterator_traits<Iterator>::difference_type    difference_type;
	typedef typename HYDRA_EXTERNAL_NS::thrust::iterator_traits<Iterator>::value_type         value_type;
	typedef typename HYDRA_EXTERNAL_NS::thrust::iterator_traits<Iterator>::pointer            pointer;
	typedef typename HYDRA_EXTERNAL_NS::thrust::iterator_traits<Iterator>::reference          reference;
	typedef typename HYDRA_EXTERNAL_NS::thrust::iterator_traits<Iterator>::iterator_category  iterator_category;

	Range()=delete;

	Range(Iterator begin, Iterator end):
		fBegin( begin),
		fEnd( end )
		{}

	Range(Iterator begin,  size_t last):
			fBegin( begin),
			fEnd( begin + last )
			{}

	Range(Range<Iterator> const& other):
			fBegin( other.GetBegin()),
			fEnd( other.GetEnd() )
			{}

	Range<Iterator>&
	operator=(Range<Iterator> const& other){

		if(this==&other) return this;

		fBegin = other.GetBegin();
		fEnd = other.GetEnd();
		return this;
	}


	Iterator begin(){ return fBegin;};

	Iterator   end(){ return fEnd;};

	size_t size() { return hydra::distance(fBegin, fEnd);}

	Iterator GetBegin() const {
		return fBegin;
	}

	void SetBegin(Iterator begin) {
		fBegin = begin;
	}

	Iterator GetEnd() const {
		return fEnd;
	}

	void SetEnd(Iterator end) {
		fEnd = end;
	}

	reference  operator[](size_t i)
	{
		return fBegin[i];
	}

	const reference  operator[](size_t i) const
	{
		return fBegin[i];
	}


private:
	Iterator fBegin;
	Iterator fEnd;

};

template<typename Iterator>
Range<Iterator>
make_range(Iterator begin, Iterator end ){
	return Range<Iterator>( begin, end);
}

template<typename Iterator>
Range<HYDRA_EXTERNAL_NS::thrust::reverse_iterator<Iterator>>
make_reverse_range(Iterator begin, Iterator end ){

	typedef HYDRA_EXTERNAL_NS::thrust::reverse_iterator<Iterator> reverse_iterator_type;
	return Range<reverse_iterator_type>(  reverse_iterator_type(end), reverse_iterator_type(begin));
}

template<typename Iterable>
typename std::enable_if<hydra::detail::is_iterable<Iterable>::value,
Range<decltype(std::declval<Iterable&>().begin())>>::type
make_range(Iterable const& container){

	typedef decltype(hydra::begin(container)) iterator_type;
	return Range<iterator_type>( hydra::begin(container), hydra::end(container));
}

template<typename Iterable>
typename std::enable_if<hydra::detail::is_iterable<Iterable>::value,
Range<decltype(std::declval<Iterable&>().begin())>>::type
make_range(Iterable&& container){

	typedef decltype(hydra::begin(container)) iterator_type;
	return Range<iterator_type>( hydra::begin(container), hydra::end(container));
}



template<typename Iterable>
typename std::enable_if<hydra::detail::is_reverse_iterable<Iterable>::value,
Range<decltype(std::declval<Iterable&>().rbegin())>>::type
make_reverse_range(Iterable const& container){

	typedef decltype(hydra::rbegin(container)) iterator_type;
	return Range<iterator_type>( hydra::rbegin(container), hydra::rend(container));
}

template<typename Iterable>
typename std::enable_if<hydra::detail::is_reverse_iterable<Iterable>::value,
Range<decltype(std::declval<Iterable&>().rbegin())>>::type
make_reverse_range(Iterable&& container){

	typedef decltype(hydra::rbegin(container)) iterator_type;
	return Range<iterator_type>( hydra::rbegin(container), hydra::rend(container));
}



}  // namespace hydra



#endif /* Range_H_ */
