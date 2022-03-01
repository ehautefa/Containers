/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/28 14:26:19 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_REVERSE_ITERATOR_HPP
#define MAP_REVERSE_ITERATOR_HPP

#include "../utils/iterator_traits.hpp"
#include "../map/node.hpp"

namespace ft
{
	template < typename iterator >
	struct map_reverse_iterator
	{
		typedef	iterator										iterator_type;
		typedef typename iterator_type::value_type       		value_type;
		typedef typename iterator_type::difference_type			difference_type;
		typedef typename iterator_type::pointer			  		pointer;
		typedef typename iterator_type::reference				reference;
		typedef bidirectional_iterator_tag			 			iterator_category;
				
		private:
			iterator_type	_ptr;
		
		public:

		pointer		getPointer(void) const { return(_ptr); }
		
		/**** CONSTRUCTOR ****/
		map_reverse_iterator( void ) {}
		explicit map_reverse_iterator( iterator_type it ) : _ptr(it--) {}
		template <class Iter>
  		map_reverse_iterator (const map_reverse_iterator<Iter>& src) : _ptr(src._ptr) {}
		~map_reverse_iterator( void ) {}

		/**** BASE ****/
		iterator_type base() const { iterator_type to_ret = _ptr; return (++to_ret);}

		/**** OPERATOR ****/
		reference			operator*()		const { return (*_ptr);}
		pointer				operator->()	const { return &(operator*());}

		map_reverse_iterator	&operator++() {_ptr--; return *this;}
		map_reverse_iterator	operator++( int ) { map_reverse_iterator tmp(*this); operator++(); return tmp;}

		map_reverse_iterator	&operator--() { _ptr++; return *this;}
		map_reverse_iterator	operator--( int ) { map_reverse_iterator tmp(*this); operator--(); return tmp;}


	}; // struct reverse iterator

	template <class Iterator1, class Iterator2 > bool 	operator==(const map_reverse_iterator<Iterator1>& lhs, const map_reverse_iterator<Iterator2>& rhs) {return (lhs.base() == rhs.base());}
	template <class Iterator1, class Iterator2 > bool 	operator!=(const map_reverse_iterator<Iterator1>& lhs, const map_reverse_iterator<Iterator2>& rhs) {return (lhs.base() != rhs.base());}
} // namespace ft

#endif