/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:52:53 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/18 15:08:08 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "node.hpp"

namespace	ft {
	
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
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
			// typedef ft::bidirectional_iterator			 			iterator;
			// typedef const Type*										const_iterator;
			// typedef typename ft::reverse_iterator<iterator> 		reverse_iterator;
			// typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename std::size_t							size_type;
			typedef typename std::ptrdiff_t							difference_type;
		
		private:
			node<key_type, mapped_type>		*_root;
			size_type			_size;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;
			key_compare			_comp;

			
	
		public:
		
		/****************~MEMBER FUNCTIONS~****************/
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(), _size(0), _alloc(alloc), _comp(comp) {}
		
		map (const map& x) : _root(x._root ? x._root->clone(NULL) : NULL), _size(x.size()), _alloc(x.get_allocator()), _node_alloc(x._node_alloc), _comp(x.key_comp()) {}
		
		template <class InputIterator>
  		map (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
			_size = 0;
			_comp = comp;
			_alloc = alloc;
			while (first != last)
			{
				*this[*first.value_type.first] = *first.value_type.second;
				first++;
				_size++;
			}
		}
		~map() { this->clear(); }
		
		map& operator= (const map& x) {
			this->clear();
			_root = x._root ? x._root->clone(NULL) : NULL;
			_size = x.size();
			_alloc = x.get_allocator();
			_node_alloc = x._node_alloc;
			_comp = x.key_comp();
			return *this;
		}
		
		allocator_type get_allocator() const { return (_alloc); }
		
		/****************~ELEMENT ACCESS~****************/
		mapped_type& operator[] (const key_type& k) {
			node<key_type, mapped_type>	*position = _root;
			node<key_type, mapped_type>	*parent = NULL;
				
			while ( position != NULL)
			{
				if (position->_value.first == k)
					return (position->_value.second);
				if (_comp(position->_value.first, k)) {// position key < k
					if (!position->_right)
						parent = position;						
					position = position->_right;
				}
				else {
					if (!position->_left)
						parent = position;
					position = position->_left;							
				}
			}
			node<key_type, mapped_type>	to_insert(value_type(k, mapped_type()), parent, NULL, NULL);
			_size++;
			if (_root == NULL) {
				_root = _node_alloc.allocate(1);
			 	_node_alloc.construct(_root, to_insert);
				 return (_root->_value.second);
			}
			else if (_comp(parent->_value.first, k)) {
				parent->_right = _node_alloc.allocate(1);
				_node_alloc.construct(parent->_right, to_insert);
				return (parent->_right->_value.second);
			}
			else {
				parent->_left = _node_alloc.allocate(1);
				_node_alloc.construct(parent->_left, to_insert);
				return (parent->_left->_value.second);
			}
		}
		
		/****************~ITERATORS~****************/
		// iterator begin() {}
		// const_iterator begin() const;
		// iterator end();
		// const_iterator end() const;
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;
		
		/****************~CAPACITY~****************/
		bool empty() const { if (_size == 0) {return (true);} return false;}
		size_type size() const { return _size; }
		size_type max_size() const { return (_alloc.max_size()); }
		
		/****************~MOFIFIERS~****************/
		void clear() {
			if (_root) {
				node<key_type, mapped_type>	*pos = _root;
				pos->destruct_all_node();
			}
			_root = NULL;
			_size = 0;
		}
		
		// pair<iterator,bool> insert (const value_type& val) {
		// 	node	*_position = _root;
			
		// 	if (this->empty()) { _root = new node(val, NULL, NULL, NULL); }
		// 	while (_position != NULL) {
		// 		if (comp(_position->_value, val)) // _position->_value < val
		// 			_position = _position->right;
		// 		else
		// 			_position = _position->left;
		// 	}
			
		// }
		// iterator insert (iterator position, const value_type& val);
		// template <class InputIterator>
		// void insert (InputIterator first, InputIterator last);
		// void erase (iterator position);
		// size_type erase (const key_type& k);
     	// void erase (iterator first, iterator last);
		// void swap (map& x);

		
		/****************~LOOKUP~****************/
		size_type count (const key_type& k) const {
			node<key_type, mapped_type>	*position = _root;
				
			while ( position ) {
				if ( position->_value.first == k )
					return 1;
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}				
			return 0;
		}
		
		// iterator find (const key_type& k);
		// const_iterator find (const key_type& k) const;
		// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		// pair<iterator,iterator> equal_range (const key_type& k);
		// iterator lower_bound (const key_type& k);
		// const_iterator lower_bound (const key_type& k) const;
		// iterator upper_bound (const key_type& k);
		// const_iterator upper_bound (const key_type& k) const;
		
		/****************~OBSERVERS~****************/
		key_compare key_comp() const { return (_comp); }
		
		// value_compare value_comp() const {
			
		// }

		void	debug() {
			std::cout << "SIZE: " << _size << std::endl;
			if (_root) {
			node<key_type, mapped_type>	*pos = _root;
			pos->debug(0, ' ');
			}
		}

	};

	template <class Key, class Compare>
	bool	operator== ( Key const & lhs, Key const & rhs) {
		std::cout << "using == surcharge\n";
		if (Compare(lhs, rhs) || Compare(rhs, lhs))
			return false;
		return true;
	}

	// template <class Key, class T, class Compare, class Alloc> bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
	// template <class Key, class T, class Compare, class Alloc> bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
	// template <class Key, class T, class Compare, class Alloc> bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
	// template <class Key, class T, class Compare, class Alloc> bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
	// template <class Key, class T, class Compare, class Alloc> bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
	// template <class Key, class T, class Compare, class Alloc> bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
	
	// template <class Key, class T, class Compare, class Alloc> void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y);
}

#endif