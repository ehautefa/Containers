/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:29:24 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/17 16:58:06 by ehautefa         ###   ########.fr       */
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
		typedef typename allocator_type::template rebind<node<key_type, mapped_type> >::other	node_allocator_type;
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
		node_allocator_type	_node_alloc;

		node( void ) : _value(), _parent(NULL), _left(NULL), _right(NULL), _difference_heights(0) {}
		node( value_type value, node *parent, node *left, node *right ) : _value(value), _parent(parent), _left(left), _right(right) {}
		~node() {}

		node *clone(node * parent) {
			if (!parent)
				return NULL;
			node	to_insert(value_type(_value), parent, _left->clone(this), _right->clone(this));
			// node	to_insert(this->_value, parent, this->_left->clone(this), this->_right->clone(this));
			node	*pos = _node_alloc.allocate(1);

			_node_alloc.construct(pos, to_insert);
			return pos;
		}

		void	debug(int i, char c) {
			std::cout << i << " " << c << "	:";
			std::cout << "KEY: " << this->_value.first << "	VALUE: " << this->_value.second << std::endl;
			if (this->_left)
				this->_left->debug(i + 1, 'l');
			if (this->_right)
				this->_right->debug(i + 1, 'r');
		}	

		void	destruct_all_node() {
			node<key_type, mapped_type> *left = this->_left;
			node<key_type, mapped_type> *right = this->_right;

			_node_alloc.destroy(this);
			_node_alloc.deallocate(this, 1);
			if (left)
				left->destruct_all_node();
			if (right)
				right->destruct_all_node();
		}		

		
	};
	
} // namespace ft

#endif