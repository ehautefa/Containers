/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:52:53 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/24 16:39:39 by ehautefa         ###   ########.fr       */
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
			node_type			*_root;
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
			_node_alloc.construct(new_node, node_type(value_type(k, mapped_type()), parent, NULL, NULL, depth, depth, 0));
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
		
	private:
	
		node_type	*right_rotation ( node_type * b ) {
			node_type	*a = b->_left;
			node_type	*v = a->_right;
			
			if (v)
				v->_parent = b;
			b->_left = v;
			if (b->_parent && b->_parent->_left == b)
				b->_parent->_left = a;
			else if (b->_parent)
				b->_parent->_right = a;
			else
				_root = a; 
			a->_parent = b->_parent;
			a->_right = b;
			b->_parent = a;
			return (a);
		}

		node_type	*left_rotation ( node_type * a ) {
			node_type	*b = a->_right;
			node_type	*v = b->_left;
			
			if (v)
				v->_parent = a;
			a->_right = v;
			if (a->_parent && a->_parent->_left == a)
				a->_parent->_left = b;
			else if (a->_parent)
				a->_parent->_right = b;
			else
				_root = b;
			b->_parent = a->_parent;
			b->_left = a;
			a->_parent = b;
			return (b);
		}

		node_type	*lr_rotation ( node_type * a ) { 
			if (a->_right)
				right_rotation(a->_right); // right rotation on the right subtree
			return (left_rotation(a));
		}

		node_type	*rl_rotation ( node_type * a ) { 
			if (a->_left)
				left_rotation(a->_left); // right rotation on the right subtree
			return (right_rotation(a));
		}


		node_type	*rebalance( node_type * pos) {
			if (pos->_delta < 0) {
				if (pos->_right->_delta > 0)
					return (this->lr_rotation(pos));
				else
					return (this->left_rotation (pos));
			}
			else {
				if (pos->_left->_delta < 0)
					return (this->rl_rotation(pos));
				else
					return (this->right_rotation (pos));
			}
		}

		void	set_depth(node_type *pos) {
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

		void	refresh_depth(node_type * pos) {
			pos->_depth = pos->_parent ? pos->_parent->_depth + 1 : 0;
			if (pos->_left)
				this->refresh_depth(pos->_left);
			if (pos->_right)
				this->refresh_depth(pos->_right);
			this->set_depth(pos);
		}

		void	equilibre( node_type *pos ) {
			while (pos->_parent && pos->_delta >= -1 && pos->_delta <= 1) {
				pos = pos->_parent;
				this->set_depth(pos);
			}
			if (pos->_delta < -1 || pos->_delta > 1) {
				this->refresh_depth(this->rebalance(pos));
			}
		}

	public:
		
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
		
		iterator end() {
			node_type	*pos = _root;
			node_type	*parent;
			
			while (pos) {
				parent = pos;
				pos = pos->_right;
			}
			return (iterator(parent));
		}
		
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
			_node_alloc.construct(new_node, node_type(val, parent, NULL, NULL, 0, 0, 0));
			_size++;
			if (_root == NULL)
				_root = new_node;
			else if (_comp(parent->_value.first, val.first))
				parent->_right = new_node;
			else
				parent->_left = new_node;
			return (ft::make_pair<iterator, bool>(iterator(new_node), true));
			
		}
		
		iterator insert (iterator position, const value_type& val) {
			(void)position;
			return (this->insert(val).first);
		}
		
		template <class InputIterator>
		void insert (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
			while (first != last) {
				insert(*first);
				first++;
			}
		}
		
		// void erase (iterator position);
		// size_type erase (const key_type& k);
     	// void erase (iterator first, iterator last);
		 
		void swap (map& x) {
			map	tmp;
			
			tmp = *this;
			*this = x;
			x = tmp;
		}

		
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
		
		iterator find (const key_type& k) {
			node_type	*position = _root;
				
			while ( position ) {
				if ( position->_value.first == k )
					return (iterator(position));
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}				
			return this->end();
		}
		
		// const_iterator find (const key_type& k) const {
		// 	node_type	*position = _root;
				
		// 	while ( position ) {
		// 		if ( position->_value.first == k )
		// 			return (const_iterator(position));
		// 		if ( _comp(position->_value.first, k) )				
		// 			position = position->_right;
		// 		else
		// 			position = position->_left;
		// 	}				
		// 	return this->end();
		// }
		
		// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		// pair<iterator,iterator> equal_range (const key_type& k);
		
		iterator lower_bound (const key_type& k) {
			node_type	*position = _root;
				
			while ( position ) {
				if ( position->_value.first == k )
					return (iterator(position));
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}				
			return iterator(position);
		}
		
		// const_iterator lower_bound (const key_type& k) const;
		
		iterator upper_bound (const key_type& k) {
		node_type	*position = _root;
				
			while ( position ) {
				if ( position->_value.first == k )
					return (++(iterator(position)));
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}				
			return iterator(position);
		}
					
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

	template <class Key, class T, class Compare, class Alloc> 
	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		map<Key, T, Compare, Alloc>::iterator	l_it = lhs.begin();		
		map<Key, T, Compare, Alloc>::iterator	r_it = rhs.begin();
		while (; l_it != l_ite; l_it++) {
			if (*l_it != *r_it)
				return false;
			r_it++;
		}
		return true;
	}
	
	template <class Key, class T, class Compare, class Alloc> 
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}
	template <class Key, class T, class Compare, class Alloc> 
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class Key, class T, class Compare, class Alloc> 
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(rhs < lhs);
	}
	template <class Key, class T, class Compare, class Alloc> 
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return rhs < lhs;
	}
	template <class Key, class T, class Compare, class Alloc> 
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}
	
	template <class Key, class T, class Compare, class Alloc> 
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
		map<Key,T,Compare,Alloc>	tmp = x;
		x = y;
		y = tmp;
	}
}

#endif