/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/01/27 15:23:35 by ehautefa         ###   ########.fr       */
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

		iterator(pointer ptr) : _ptr(ptr) {}
		iterator( const iterator & src ) : _ptr(src._ptr) {}
		~iterator( void ) {}

		private:
			pointer	_ptr;
	};

			// /*******************	Function	*******************/

			// template <class InputIterator, class Distance>
			// 	void advance (InputIterator& it, Distance n);
			// template <class Container>
			// 	back_insert_iterator<Container> back_inserter (Container& x);
			// template<class InputIterator>
			// 	typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last);
			// template <class Container>
			// 	front_insert_iterator<Container> front_inserter (Container& x);
			// template <class Container, class Iterator>
			// 	insert_iterator<Container> inserter (Container& x, Iterator it);

			// /*******************	Operator	*******************/

			// template <class RandomIterator>
			// 	bool operator!=(const reverse_iterator<RandomIterator>& left, const reverse_iterator<RandomIterator>& right);

			// template <class Type, class CharType, class Traits, class Distance>
			// 	bool operator!=(const istream_iterator<Type, CharType, Traits, Distance>& left, const istream_iterator<Type, CharType, Traits, Distance>& right);

			// template <class CharType, class Tr>
			// 	bool operator!=(const istreambuf_iterator<CharType, Traits>& left, const istreambuf_iterator<CharType, Traits>& right);
	
}

#endif