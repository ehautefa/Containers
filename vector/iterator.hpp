/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/08 18:04:51 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "../utils/iterator_traits.hpp"

namespace ft
{
	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	class iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	class const_iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;	
	};

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
			pointer	_ptr;
		
		public:
		/**** CONSTRUCTOR ****/
		reverse_iterator( void ) {}
		explicit reverse_iterator( iterator_type it ) : _ptr(it) {}
		reverse_iterator( const reverse_iterator & src ) : _ptr(src._ptr) {}
		~reverse_iterator( void ) {}

		/**** BASE ****/
		iterator_type base() const {return (iterator_type(_ptr + 1));}

		/**** OPERATOR ****/
		reference			operator*() const {return (*_ptr);}
		reverse_iterator	operator+ (difference_type n) const { _ptr -= n; return (*this);}

		reverse_iterator	&operator++() {--_ptr;return *this;}
		reverse_iterator	operator++( int ) { reverse_iterator tmp(*this); operator++(); return tmp;}

		reverse_iterator	&operator+=( difference_type n ) {return(*this - n);}
		reverse_iterator	&operator-( difference_type	n ) { _ptr += n; return (*this);}

		reverse_iterator	&operator--() { ++_ptr; return *this;}
		reverse_iterator	operator--( value_type ) { reverse_iterator tmp(*this); operator--(); return tmp;}

		reverse_iterator	&operator-=( value_type n ) {return(*this + n);}

		pointer		operator->() const {return (*_ptr);}
		reference	operator[] ( difference_type n ) const {return (_ptr[n]);}
	};

	template <class Iterator> bool 	operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() == rhs.base());}
	template <class Iterator> bool 	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() != rhs.base());}
	template <class Iterator> bool 	operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() <  rhs.base());}
	template <class Iterator> bool 	operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() >  rhs.base());}
	template <class Iterator> bool 	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() >= rhs.base());}
	template <class Iterator> bool 	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs.base() <= rhs.base());}
	
	template <class Iterator> reverse_iterator<Iterator> operator+( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return(reverse_iterator<Iterator>( rev_it.base() - n ));}
	template <class Iterator> typename reverse_iterator<Iterator>::difference_type operator- ( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return(reverse_iterator<Iterator>( -lhs.base() + rhs.base()));}
}

#endif