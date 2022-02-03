/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/03 16:23:47 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	
	template <class Iterator>
	class iterator_traits {
		public:
			typedef typename Iterator::difference_type 	difference_type;
			typedef typename Iterator::value_type 		value_type;
			typedef typename Iterator::pointer 			pointer;
			typedef typename Iterator::reference 		reference;
			typedef typename Iterator::iterator_category iterator_category;

	};

	template <class T>
	class iterator_traits<T*> {
		public:
			typedef random_access_iterator_tag	category; 
			typedef ptrdiff_t					difference_type;
			typedef T							value_type;
			typedef T*							pointer;
			typedef T&							reference;

	};

	template <class T>
	class iterator_traits<const T*> {
		public:
			typedef random_access_iterator_tag	category; 
			typedef ptrdiff_t					difference_type;
			typedef T							value_type;
			typedef const T*					pointer;
			typedef const T&					reference;

	};

	template <typename iterator>
	struct reverse_iterator : public iterator 	<typename iterator_traits<iterator>::iterator_category,
                      							typename iterator_traits<iterator>::value_type,
                      							typename iterator_traits<iterator>::difference_type,
                      							typename iterator_traits<iterator>::pointer,
                      							typename iterator_traits<iterator>::reference> {

		typedef typename iterator_traits<iterator>::value_type       	value_type;
		typedef typename iterator_traits<iterator>::difference_type		difference_type;
		typedef typename iterator_traits<iterator>::pointer			  	pointer;
		typedef typename iterator_traits<iterator>::reference			reference;
		typedef typename iterator_traits<iterator>::iterator_category  	iterator_category;
		
		private:
			pointer	_ptr;
		
		public:
		iterator(pointer ptr) : _ptr(ptr) {}
		iterator( const iterator & src ) : _ptr(src._ptr) {}
		iterator	&operator=(const iterator & rhs) {this->_ptr = this._ptr;return (*this);}
		~iterator( void ) {}

		bool 	operator==(const iterator & rhs) const { return (_ptr == rhs._ptr);}
		bool 	operator!=(const iterator & rhs) const {return (_ptr != rhs._ptr);}

		value_type	&operator*() {return (*_ptr);}
		value_type	&operator->() {return (*_ptr);}

		value_type	operator=( value_type  t ) {*_ptr = t; return (*_ptr);}

		iterator	&operator++() {--_ptr;return *this;}
		iterator	operator++( value_type ) { iterator tmp(*this); operator--(); return tmp;}

		iterator	&operator--() { ++_ptr; return *this;}
		iterator	operator--( value_type ) { iterator tmp(*this); operator++(); return tmp;}	
		
		iterator	&operator+( value_type	n ) { _ptr -= n; return (*this);}
		iterator	&operator-( value_type	n ) { _ptr += n; return (*this);}
		iterator	&operator-( const iterator & rhs ) { iterator	to_ret(_ptr + rhs.ptr);return (to_ret);}

		bool 	operator>(const iterator & rhs) const {return (_ptr < rhs._ptr);}
		bool 	operator<(const iterator & rhs) const {return (_ptr > rhs._ptr);}
		bool 	operator<=(const iterator & rhs) const {return (_ptr >= rhs._ptr);}
		bool 	operator>=(const iterator & rhs) const {return (_ptr <= rhs._ptr);}
		
		iterator	&operator-=( value_type n ) {return(a + n);}
		iterator	&operator+=( value_type n ) {return(a - n);}

		value_type	operator[]( int n ) {return (_ptr[n]);}
	};
}

#endif