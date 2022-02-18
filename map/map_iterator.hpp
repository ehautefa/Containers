/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/18 15:07:17 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "../utils/iterator_traits.hpp"

namespace ft
{
	
	template <typename iterator>
	struct bidirectional_iterator
	{
		typedef typename iterator_traits<iterator>::value_type       	value_type;
		typedef typename iterator_traits<iterator>::difference_type		difference_type;
		typedef typename iterator_traits<iterator>::pointer			  	pointer;
		typedef typename iterator_traits<iterator>::reference			reference;
		typedef bidirectional_iterator_tag 					  			iterator_category;
		typedef	iterator												iterator_type;
		
		private:
			pointer	_ptr;
		
		public:

		pointer		getPointer(void) const { return(_ptr); }
		
		/**** CONSTRUCTOR ****/
		bidirectional_iterator( void ) {}
		template <class Iter>
  		bidirectional_iterator ( const bidirectional_iterator<Iter>& src ) : _ptr(src.getPointer()) {}
		bidirectional_iterator	&operator=( bidirectional_iterator const & rhs ) {_ptr = rhs._ptr; }
		~bidirectional_iterator( void ) {}

		/**** OPERATOR ****/
		reference			operator*() 	const {return (*_ptr);}
		pointer				operator->() 	const {return &(operator*());}

		bidirectional_iterator	&operator++() { ++_ptr; return *this;}
		bidirectional_iterator	operator++( int ) { bidirectional_iterator tmp(*this); operator--(); return tmp;}

		bidirectional_iterator	&operator--() {--_ptr;return *this;}
		bidirectional_iterator	operator--( int ) { bidirectional_iterator tmp(*this); operator++(); return tmp;}
	};

	template <class Iterator1, class Iterator2 > bool 	operator==(const bidirectional_iterator<Iterator1>& lhs, const bidirectional_iterator<Iterator2>& rhs) {return (lhs.getPointer() == rhs.getPointer());}
	template <class Iterator1, class Iterator2 > bool 	operator!=(const bidirectional_iterator<Iterator1>& lhs, const bidirectional_iterator<Iterator2>& rhs) {return (!( lhs == rhs ));}
}

#endif