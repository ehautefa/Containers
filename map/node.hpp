/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:29:24 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/15 12:36:48 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include "../utils/enable_if.hpp"
#include "../utils/utils.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/compare.hpp"
#include "../utils/iterator_traits.hpp"
#include "../utils/pair.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	struct node
	{
		typedef	Key												key_type;
		typedef	T												mapped_type;
		typedef	pair<const key_type,mapped_type>				value_type;
		typedef	Compare											key_compare;
		typedef	Alloc											allocator_type;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef	typename allocator_type::pointer				pointer;
		typedef	typename allocator_type::const_pointer			const_pointer;
		typedef typename std::size_t							size_type;
		typedef typename std::ptrdiff_t							difference_type;
			
		value_type 		_value;
		node			*_parent;
		node			*_left;
		node			*_right;
		size_type		_difference_heights;
		size_type		_height;

		node( void ) : _value(), _parent(NULL), _left(NULL), _right(NULL), _difference_heights(0) {}
		node( value_type value, node *parent, node *left, node *right ) : _value(value), _parent(parent), _left(left), _right(right) {}
		~node() {}

		
	};
	
} // namespace ft

#endif