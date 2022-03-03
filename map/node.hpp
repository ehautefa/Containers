/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:29:24 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/28 11:28:04 by ehautefa         ###   ########.fr       */
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
			
		value_type 					_value;
		node						*_parent;
		node						*_left;
		node						*_right;
		size_type					_depth;
		size_type					_max_depth;
		difference_type				_delta;
		node_allocator_type			_node_alloc;

		node( void ) : _value(), _parent(NULL), _left(NULL), _right(NULL), _depth(0), _max_depth(0), _delta(0) {}
		node( value_type value, node *parent, node *left, node *right, size_type depth, size_type max_depth, difference_type delta ) : _value(value), _parent(parent), _left(left), _right(right), _depth(depth), _max_depth(max_depth), _delta(delta) {}
		~node() {}

		node *clone(node * parent) {
			node	*pos 		= _node_alloc.allocate(1);
			node	*f_left		= _left ? _left->clone(pos) : NULL;
			node	*f_right	= _right ? _right->clone(pos) : NULL;

			node	to_insert(_value, parent, f_left, f_right, _depth, _max_depth, _delta);

			_node_alloc.construct(pos, to_insert);
			return pos;
		}

		void	display() {
			std::cout << "KEY: " << this->_value.first << " 	VALUE: " << this->_value.second;
			std::cout << "	DEPTH: " << this->_depth << "	DELTA: " << this->_delta;
			std::cout << "	MAX_DEPTH: " << this->_max_depth;
			std::cout << "	PARENT: " << this->_parent << "	LEFT: " << this->_left;
			std::cout << "	RIGHT: " << this->_right << std::endl;
		}

		void	debug(int i, char c) {
			std::cout << i << " " << c << "	:";
			this->display();
			if (this->_left)
				this->_left->debug(i + 1, 'l');
			if (this->_right)
				this->_right->debug(i + 1, 'r');
		}	

		void	destruct_all_node() {
			if (_left)
				_left->destruct_all_node();
			if (_right)
				_right->destruct_all_node();
			_node_alloc.destroy(this);
			_node_alloc.deallocate(this, 1);
		}	

		node	&operator=( node const & rhs ) {
			// _value = rhs._value;
			_parent = rhs._parent;
			_left = rhs._left;
			_right = rhs._right;
			_depth = rhs._depth;
			_max_depth = rhs._max_depth;
			_delta = rhs._delta;
			_node_alloc = rhs._node_alloc;
			return (*this);
		}

		void	swap_neighboor( node *x ) {
			if (x->_parent && x->_parent->_left == x) 
				x->_parent->_left = this;
			else if (x->_parent && x->_parent->_right == x)
				x->_parent->_right = this;
			if (x->_left)
				x->_left->_parent = this;
			if (x->_right)
				x->_right->_parent = this;
		}

		void	swap( node & x ) {
			node	tmp = x;
			// ATTENTION PROBLEME QUAND TU SWAP 2 voisins proches 
			x.swap_neighboor(this);
			this->swap_neighboor( &tmp );
			x = *this;
			*this = tmp;
		}

	};

	template <class Key, class T, class Compare, class Alloc> 
	bool	operator==(node<Key, T, Compare, Alloc> const & rhs, node<Key, T, Compare, Alloc> const & lhs) {
		return (lhs._value == rhs._value);
	}
	
} // namespace ft

#endif