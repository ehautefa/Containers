/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_const_iterator.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:57:31 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/07 17:56:30 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_CONST_ITERATOR_HPP
#define MAP_CONST_ITERATOR_HPP

#include "../utils/iterator_traits.hpp"
#include "../map/node.hpp"
#include "map_iterator.hpp"

namespace	ft {
	template < class Node >
	struct const_map_iterator
	{ 
		typedef Node        									node_type;
		typedef	const Node*										node_pointer;
		typedef typename std::ptrdiff_t							difference_type;
		typedef	typename node_type::value_type 					value_type;
		typedef typename node_type::const_pointer				const_pointer;
		typedef typename node_type::pointer						pointer;
		typedef typename node_type::const_reference				const_reference;
		typedef typename node_type::reference					reference;
		typedef bidirectional_iterator_tag			 			iterator_category;
		
		private:
			node_pointer	_ptr;
		
		public:

		node_pointer		getPointer(void) const { return(_ptr); }
		
		/**** CONSTRUCTOR ****/
		const_map_iterator( void ) : _ptr() {}
		const_map_iterator( node_pointer ptr ) : _ptr(ptr) {}
		template <class Iter>
  		const_map_iterator ( const const_map_iterator<Iter>& src ) : _ptr(src.getPointer()) {}
  		const_map_iterator ( const map_iterator<node_type>& src ) : _ptr(src.getPointer()) {}
		const_map_iterator	&operator=( const_map_iterator const & rhs ) {_ptr = rhs._ptr; return *this; }
		~const_map_iterator( void ) {}

		/**** OPERATOR ****/
		reference		operator*() 	const {return (_ptr->getValue());}
		pointer			operator->() 	const {return (&_ptr->getValue());}

		const_map_iterator	&operator++() {
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
		
		const_map_iterator	operator++( int ) { const_map_iterator tmp(*this); operator++(); return tmp;}

		const_map_iterator	&operator--() {
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
		
		const_map_iterator	operator--( int ) { const_map_iterator tmp(*this); operator--(); return tmp;}
	};

	template <class Iterator1, class Iterator2 > bool 	operator==(const const_map_iterator<Iterator1>& lhs, const const_map_iterator<Iterator2>& rhs) {return (lhs.getPointer() == rhs.getPointer());}
	template <class Iterator1, class Iterator2 > bool 	operator!=(const const_map_iterator<Iterator1>& lhs, const const_map_iterator<Iterator2>& rhs) {return (!( lhs == rhs ));}
} // namespace ft

#endif