/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/16 10:53:50 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "../utils/iterator_traits.hpp"

namespace ft
{

	template <typename iterator>
	struct reverse_iterator
	{
		typedef typename iterator_traits<iterator>::value_type       	value_type;
		typedef typename iterator_traits<iterator>::difference_type		difference_type;
		typedef typename iterator_traits<iterator>::pointer			  	pointer;
		typedef typename iterator_traits<iterator>::reference			reference;
		typedef typename iterator_traits<iterator>::category  			iterator_category;
		typedef	iterator												iterator_type;
		
		private:
			iterator_type	_ptr;
		
		public:

		/**** CONSTRUCTOR ****/
		reverse_iterator( void ) : _ptr() {}
		explicit reverse_iterator( iterator_type it ) : _ptr(it - 1) {}
		template <class Iter>
  		reverse_iterator (const reverse_iterator<Iter>& src) : _ptr(src.base() - 1) {}
		~reverse_iterator( void ) {}

		/**** BASE ****/
		iterator_type base() const {return (iterator_type(_ptr + 1));}

		/**** OPERATOR ****/
		reference			operator*() const {return (*_ptr);}
		reverse_iterator	operator+ (difference_type n) const { return (reverse_iterator(_ptr - n + 1));}

		reverse_iterator	&operator++() {--_ptr;return *this;}
		reverse_iterator	operator++( int ) { reverse_iterator tmp(*this); operator++(); return tmp;}

		reverse_iterator	&operator+=( difference_type n ) {_ptr = _ptr - n; return(*this);}
		reverse_iterator	operator-( difference_type	n ) const { return (reverse_iterator(_ptr + n + 1));}

		reverse_iterator	&operator--() { ++_ptr; return *this;}
		reverse_iterator	operator--( int ) { reverse_iterator tmp(*this); operator--(); return tmp;}

		reverse_iterator	&operator-=( value_type n ) { _ptr = _ptr + n; return(*this);}

		pointer		operator->() const {return &(operator*());}
		reference	operator[] ( difference_type n ) const {return (base()[-n-1]);}
	};

	template <class Iterator1, class Iterator2 > bool 	operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() == rhs.base());}
	template <class Iterator1, class Iterator2 > bool 	operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() != rhs.base());}
	template <class Iterator1, class Iterator2 > bool 	operator> (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() <  rhs.base());}
	template <class Iterator1, class Iterator2 > bool 	operator< (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() >  rhs.base());}
	template <class Iterator1, class Iterator2 > bool 	operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() >= rhs.base());}
	template <class Iterator1, class Iterator2 > bool 	operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() <= rhs.base());}
	
	template <class Iterator> reverse_iterator<Iterator>	operator+(typename Iterator::difference_type	n, const reverse_iterator<Iterator>& rhs) { return (rhs + n); }

	template <class Iterator> reverse_iterator<Iterator> operator+( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return(reverse_iterator<Iterator>( rev_it.base() - n ));}
	template <class Iterator> typename reverse_iterator<Iterator>::difference_type operator- ( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return( rhs.base() - lhs.base());}
	template <class Iterator1, class Iterator2 > typename reverse_iterator<Iterator1>::difference_type operator- ( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return( rhs.base() - lhs.base());}
}

#endif