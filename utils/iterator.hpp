/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/02 16:38:03 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;

		struct input_iterator_tag {};
		struct output_iterator_tag {};
		struct forward_iterator_tag {};
		struct bidirectional_iterator_tag {};
		struct random_access_iterator_tag {};

		iterator(pointer ptr) : _ptr(ptr) {}
		iterator( const iterator & src ) : _ptr(src._ptr) {}
		~iterator( void ) {}
		
		/*******************	METHOD	*******************/

		template <class InputIterator>
		void advance (InputIterator & it, Distance n) {
			it += n;
		}
		// template <class Container>
		// 	back_insert_iterator<Container> back_inserter (Container& x);
		// template<class InputIterator>
		// 	typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last);
		// template <class Container>
		// 	front_insert_iterator<Container> front_inserter (Container& x);
		// template <class Container, class Iterator>
		// 	insert_iterator<Container> inserter (Container& x, Iterator it);
		private:
			pointer	_ptr;
	};

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
			typedef ptrdiff_t	difference_type;
			typedef T			value_type;
			typedef T*			pointer;
			typedef T&			reference;
			// typedef iterator_category;

	};

	template <class T>
	class iterator_traits<const T*> {
		public:
			typedef ptrdiff_t	difference_type;
			typedef T			value_type;
			typedef const T*	pointer;
			typedef const T&	reference;

	};

			

			// /*******************	Operator	*******************/

			// template <class RandomIterator>
			// 	bool operator!=(const reverse_iterator<RandomIterator>& left, const reverse_iterator<RandomIterator>& right);

			// template <class Type, class CharType, class Traits, class Distance>
			// 	bool operator!=(const istream_iterator<Type, CharType, Traits, Distance>& left, const istream_iterator<Type, CharType, Traits, Distance>& right);

			// template <class CharType, class Tr>
			// 	bool operator!=(const istreambuf_iterator<CharType, Traits>& left, const istreambuf_iterator<CharType, Traits>& right);
	
}

#endif