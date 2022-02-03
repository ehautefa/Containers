/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/03 17:15:14 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft
{
	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
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
                      							typename iterator_traits<iterator>::reference>
	{
		typedef typename iterator_traits<iterator>::value_type       	value_type;
		typedef typename iterator_traits<iterator>::difference_type		difference_type;
		typedef typename iterator_traits<iterator>::pointer			  	pointer;
		typedef typename iterator_traits<iterator>::reference			reference;
		typedef typename iterator_traits<iterator>::category  			iterator_category;
		
		private:
			pointer	_ptr;
		
		public:
		reverse_iterator(pointer ptr) : _ptr(ptr) {}
		reverse_iterator( const reverse_iterator & src ) : _ptr(src._ptr) {}
		reverse_iterator	&operator=(const reverse_iterator & rhs) {this->_ptr = rhs._ptr;return (*this);}
		~reverse_iterator( void ) {}

		bool 	operator==(const reverse_iterator & rhs) const { return (_ptr == rhs._ptr);}
		bool 	operator!=(const reverse_iterator & rhs) const {return (_ptr != rhs._ptr);}

		reference	operator*() {return (*_ptr);}
		reference	operator->() {return (*_ptr);}

		value_type	operator=( value_type  t ) {*_ptr = t; return (*_ptr);}

		reverse_iterator	&operator++() {--_ptr;return *this;}
		reverse_iterator	operator++( value_type ) { reverse_iterator tmp(*this); operator--(); return tmp;}

		reverse_iterator	&operator--() { ++_ptr; return *this;}
		reverse_iterator	operator--( value_type ) { reverse_iterator tmp(*this); operator++(); return tmp;}	
		
		reverse_iterator	&operator+( value_type	n ) { _ptr -= n; return (*this);}
		reverse_iterator	&operator-( value_type	n ) { _ptr += n; return (*this);}
		reverse_iterator	&operator-( const reverse_iterator & rhs ) { reverse_iterator	to_ret(_ptr + rhs.ptr);return (to_ret);}

		bool 	operator>(const reverse_iterator & rhs) const {return (_ptr < rhs._ptr);}
		bool 	operator<(const reverse_iterator & rhs) const {return (_ptr > rhs._ptr);}
		bool 	operator<=(const reverse_iterator & rhs) const {return (_ptr >= rhs._ptr);}
		bool 	operator>=(const reverse_iterator & rhs) const {return (_ptr <= rhs._ptr);}
		
		reverse_iterator	&operator-=( value_type n ) {return(*this + n);}
		reverse_iterator	&operator+=( value_type n ) {return(*this - n);}

		value_type	operator[]( int n ) {return (_ptr[n]);}
	};
}

#endif