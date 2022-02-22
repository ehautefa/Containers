/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:52:53 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/22 12:51:39 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "node.hpp"
#include "map_iterator.hpp"

namespace	ft {
	
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
			typedef	Key															key_type;
			typedef	T															mapped_type;
			typedef	pair<const key_type,mapped_type>							value_type;
			typedef	node<const key_type,mapped_type>							node_type;
			typedef	Compare														key_compare;
			typedef	Alloc														allocator_type;
			typedef typename allocator_type::template rebind<node_type>::other	node_allocator_type;
			typedef	typename allocator_type::reference							reference;
			typedef	typename allocator_type::const_reference					const_reference;
			typedef	typename allocator_type::pointer							pointer;
			typedef	typename allocator_type::const_pointer						const_pointer;
			typedef	typename ft::map_iterator<node_type>						iterator;
			// typedef const Type*												const_iterator;
			// typedef typename ft::reverse_iterator<iterator> 					reverse_iterator;
			// typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename std::size_t										size_type;
			typedef typename std::ptrdiff_t										difference_type;
		
		private:
			node_type		*_root;
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
			node_type	*position = _root;
			node_type	*parent = NULL;
			size_type	depth = 0;
				
			while ( position ) {
				parent = position;						
				if (position->_value.first == k)
					return (position->_value.second);
				if (_comp(position->_value.first, k)) // position key < k
					position = position->_right;
				else
					position = position->_left;	
				depth++;					
			}
			
			// ADD A NODE
			node_type	*new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, node_type(value_type(k, mapped_type()), parent, NULL, NULL, depth));
			_size++;
			if (_root == NULL)
				_root = new_node;
			else if (_comp(parent->_value.first, k))
				parent->_right = new_node;
			else
				parent->_left = new_node;
			this->equilibre(new_node);
			return new_node->_value.second;
		}

		void	rr_rotation ( node_type * b ) {
			node_type	*a = b->_left;
			node_type	*v = a->_right;

			v->_parent = b;
			b->_left = v;
			a->_parent = b->_parent;
			a->_right = b;
			b->_parent = a;
		}

		void	left_rotation ( node_type * a ) {
			node_type	*b = a->_right;
			node_type	*v = b->_left;
			
			v->_parent = a;
			a->_left = v;
			if (a->_parent->_left == a)
				a->_parent->_left = b;
			else
				a->_parent->_right = b;
			b->_parent = a->_parent;
			b->_left = a;
			a->_parent = b;
		}

		void	rebalance( node_type * pos) {
			if (pos->_delta < 0)
				this->left_rotation (pos);
			else
				this->right_rotation (pos);
		}

		void	equilibre( node_type *pos ) {
			while (pos->_parent && pos->_delta >= -1 && pos->_delta <= 1) {
				pos = pos->_parent;
				if (pos->_left && pos->_right) {
					pos->_delta = pos->_left->_max_depth - pos->_right->_max_depth;
					pos->_max_depth = pos->_left->_max_depth > pos->_right->_max_depth ? pos->_left->_max_depth : pos->_right->_max_depth;
				}
				else if (!pos->_left && pos->_right) {
					pos->_delta = pos->_depth - pos->_right->_max_depth;
					pos->_max_depth = pos->_right->_max_depth;
				}
				else if (pos->_left && !pos->_right) {
					pos->_delta = pos->_left->_max_depth - pos->_depth;
					pos->_max_depth = pos->_left->_max_depth;
				}
				else {
					pos->_delta = 0;
					pos->_max_depth = pos->_depth;
				}
			}
			if (pos->_delta < -1 || pos->_delta > 1) {
				std::cout << "rebalance " << pos->_value.first << std::endl;
				// this->rebalance(pos);
			}
		}
		
		/****************~ITERATORS~****************/
		iterator begin() {
			node_type	*pos = _root;
			node_type	*parent;
			
			while (pos) {
				parent = pos;
				pos = pos->_left;
			}
			return (iterator(parent));
		}
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
				node_type	*pos = _root;
				pos->destruct_all_node();
				_root = NULL;
			}
			_size = 0;
		}
		
		pair<iterator,bool> insert (const value_type& val) {
			node_type	*position = _root;
			node_type	*parent = NULL;
				
			while ( position ) {
				parent = position;						
				if (position->_value.first == val.first)
					return (ft::make_pair<iterator, bool>(iterator(position), false));
				if (_comp(position->_value.first, val.first)) // position key < k
					position = position->_right;
				else
					position = position->_left;							
			}
			
			// ADD A NODE
			node_type	*new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, node_type(val, parent, NULL, NULL));
			_size++;
			if (_root == NULL)
				_root = new_node;
			else if (_comp(parent->_value.first, val.first))
				parent->_right = new_node;
			else
				parent->_left = new_node;
			return (ft::make_pair<iterator, bool>(iterator(new_node), true));
			
		}
		
		// iterator insert (iterator position, const value_type& val);
		// template <class InputIterator>
		// void insert (InputIterator first, InputIterator last);
		// void erase (iterator position);
		// size_type erase (const key_type& k);
     	// void erase (iterator first, iterator last);
		// void swap (map& x);

		
		/****************~LOOKUP~****************/
		size_type count (const key_type& k) const {
			node_type	*position = _root;
				
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
			node_type	*pos = _root;
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