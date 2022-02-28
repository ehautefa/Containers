/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/28 13:51:12 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "../utils/iterator_traits.hpp"
#include "../map/node.hpp"

namespace ft
{
	template < class Node >
	struct map_iterator
	{ 
		typedef Node        									node_type;
		typedef	Node*											node_pointer;
		typedef	typename node_type::key_type 					key_type;
		typedef	typename node_type::mapped_type 				mapped_type;
		typedef	typename node_type::key_compare 				key_compare;
		typedef	typename node_type::allocator_type				allocator_type;
		typedef typename std::size_t							size_type;
		
		typedef typename std::ptrdiff_t							difference_type;
		typedef	typename node_type::value_type 					value_type;
		typedef typename node_type::value_type*					pointer;
		typedef typename node_type::value_type&					reference;
		typedef bidirectional_iterator_tag			 			iterator_category;
		
		
		private:
			node_pointer	_ptr;
		
		public:

		node_pointer		getPointer(void) const { return(_ptr); }
		
		/**** CONSTRUCTOR ****/
		map_iterator( void ) : _ptr() {}
		map_iterator( node_pointer ptr ) : _ptr(ptr) {}
		template <class Iter>
  		map_iterator ( const map_iterator<Iter>& src ) : _ptr(src.getPointer(), _parent(src.getParent())) {}
		map_iterator	&operator=( map_iterator const & rhs ) {_ptr = rhs._ptr; return *this; }
		~map_iterator( void ) {}

		/**** OPERATOR ****/
		reference		operator*() 	const {return (_ptr->_value);}
		pointer			operator->() 	const {return &(operator*());}

		map_iterator	&operator++() {
			if (!_ptr)
				return *this;
			else if (_ptr->_right) {
				_ptr = _ptr->_right;
				while (_ptr->_left)
					_ptr = _ptr->_left;
				return (*this);
			}
			else if (_ptr->_parent) {
				while (_ptr->_parent->_parent && _ptr->_parent->_right == _ptr)
					_ptr = _ptr->_parent;
				_ptr = _ptr->_parent;
				return (*this);
			}
			return (*this);
		}
		
		map_iterator	operator++( int ) { map_iterator tmp(*this); operator++(); return tmp;}

		map_iterator	&operator--() {
			if (!_ptr)
				return *this;
			if (_ptr->_left) {
				_ptr = _ptr->_left;
				while (_ptr->_right)
					_ptr = _ptr->_right;
				return (*this);
			}
			else if (_ptr->_parent) {
				while (_ptr->_parent->_parent && _ptr->_parent->_left == _ptr)
					_ptr = _ptr->_parent;
				_ptr = _ptr->_parent;
				return (*this);
			}
			return (*this);
		}
		
		map_iterator	operator--( int ) { map_iterator tmp(*this); operator--(); return tmp;}
	};

	template <class Iterator1, class Iterator2 > bool 	operator==(const map_iterator<Iterator1>& lhs, const map_iterator<Iterator2>& rhs) {return (lhs.getPointer() == rhs.getPointer());}
	template <class Iterator1, class Iterator2 > bool 	operator!=(const map_iterator<Iterator1>& lhs, const map_iterator<Iterator2>& rhs) {return (!( lhs == rhs ));}
}

#endif