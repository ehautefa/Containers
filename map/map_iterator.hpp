/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/16 10:41:51 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "../utils/iterator_traits.hpp"
#include "../map/node.hpp"

namespace ft
{
	template < class Node >
	struct map_iterator
	{ 
		typedef Node        									node_type;
		typedef	Node*											node_pointer;
		typedef typename std::ptrdiff_t							difference_type;
		typedef	typename node_type::value_type 					value_type;
		typedef typename node_type::pointer						pointer;
		typedef typename node_type::reference					reference;
		typedef bidirectional_iterator_tag			 			iterator_category;
		
		private:
			node_pointer	_ptr;
		
		public:

		node_pointer		getPointer(void) const { return(_ptr); }
		
		/**** CONSTRUCTOR ****/
		map_iterator( void ) : _ptr() {}
		map_iterator( node_pointer ptr ) : _ptr(ptr) {}
		template <class Iter>
  		map_iterator ( const map_iterator<Iter>& src ) : _ptr(src.getPointer()) {}
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