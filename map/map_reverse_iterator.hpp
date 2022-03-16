/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:30:25 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/16 20:39:52 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_REVERSE_ITERATOR
#define MAP_REVERSE_ITERATOR

#include "../utils/iterator_traits.hpp"

namespace ft
{

	template <typename iterator>
	struct map_reverse_iterator
	{
		typedef typename iterator_traits<iterator>::value_type       	value_type;
		typedef typename iterator_traits<iterator>::difference_type		difference_type;
		typedef typename iterator_traits<iterator>::pointer			  	pointer;
		typedef typename iterator::const_pointer						const_pointer;
		typedef typename iterator_traits<iterator>::reference			reference;
		typedef typename iterator::const_reference						const_reference;
		typedef typename iterator_traits<iterator>::iterator_category  	iterator_category;
		typedef	iterator												iterator_type;
		
		private:
			iterator_type	_ptr;
		
		public:

		/**** CONSTRUCTOR ****/
		map_reverse_iterator( void ) : _ptr() {}
		explicit map_reverse_iterator( iterator_type it ) : _ptr(--it) {}
		template <class Iter>
  		map_reverse_iterator (const map_reverse_iterator<Iter>& src) {
			  iterator_type tmp = src.base();
			  --tmp;
			  _ptr = tmp;
		}
		~map_reverse_iterator( void ) {}

		/**** BASE ****/
		iterator_type base() const { iterator_type to_ret = _ptr; return (++to_ret);}

		/**** OPERATOR ****/
		reference			operator*()			{ return (*_ptr); }
		const_reference		operator*() const 	{ return (*_ptr); }

		map_reverse_iterator	&operator++() {--_ptr;return *this;}
		map_reverse_iterator	operator++( int ) { map_reverse_iterator tmp(*this); operator++(); return tmp;}

		map_reverse_iterator	&operator--() { ++_ptr; return *this;}
		map_reverse_iterator	operator--( int ) { map_reverse_iterator tmp(*this); operator--(); return tmp;}

		pointer				operator->() 		{ return &(operator*()); }
		const_pointer		operator->() const 	{ return &(operator*()); }
	};

	template <class Iterator1, class Iterator2 > bool 	operator==(const map_reverse_iterator<Iterator1>& lhs, const map_reverse_iterator<Iterator2>& rhs) {return (lhs.base() == rhs.base());}
	template <class Iterator1, class Iterator2 > bool 	operator!=(const map_reverse_iterator<Iterator1>& lhs, const map_reverse_iterator<Iterator2>& rhs) {return (lhs.base() != rhs.base());}
}

#endif