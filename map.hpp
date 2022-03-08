/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:52:53 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/07 16:08:24 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "map/node.hpp"
#include "map/map_iterator.hpp"
#include "map/map_reverse_iterator.hpp"
#include "map/map_const_iterator.hpp"

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
			typedef typename ft::map_iterator<node_type>						const_iterator;
			typedef typename ft::map_reverse_iterator<iterator> 				reverse_iterator;
			typedef typename ft::map_reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef typename std::size_t										size_type;
			typedef typename std::ptrdiff_t										difference_type;
		
		private:
			node_type			*_root;
			node_type			*_rend;
			node_type			*_end;
			key_type			_min;
			key_type			_max;
			size_type			_size;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;
			key_compare			_comp;

			
	
		public:
		
		/****************~MEMBER FUNCTIONS~****************/
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(), _min(), _max(), _size(0), _alloc(alloc), _comp(comp) {
			this->_init_leaf();
		}
		
		map (const map& x) : _root(x._root ? x._root->clone(NULL) : NULL), _min(x._min), _max(x._max), _size(x.size()), _alloc(x.get_allocator()), _node_alloc(x._node_alloc), _comp(x.key_comp()) {
			_end = _root;
			while (_end && _end->_right)
				_end = _end->_right;
			_rend = _root;
			while (_rend && _rend->_left)
				_rend = _rend->_left;
		}
		
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
			this->_init_leaf();
		}
		
		~map() { this->clear(); }
		
		map& operator= (const map& x) {
			this->clear();
			_root = x._root ? x._root->clone(NULL) : NULL;
			_size = x.size();
			_min = x._min;
			_max = x._max;
			_alloc = x.get_allocator();
			_node_alloc = x._node_alloc;
			_comp = x.key_comp();
			_end = _root;
			while (_end && _end->_right)
				_end = _end->_right;
			_rend = _root;
			while (_rend && _rend->_left)
				_rend = _rend->_left;
			return *this;
		}
		
		allocator_type get_allocator() const { return (_alloc); }

		/****************~ELEMENT ACCESS~****************/
		mapped_type& operator[] (const key_type& k) {
			node_type	*position = _root;
			node_type	*parent = NULL;
			size_type	depth = 0;

			while ( position && position != _end && position != _rend ) {
				parent = position;						
				if (position->_value.first == k)
					return (position->_value.second);
				if (_comp(position->_value.first, k)) // position key < k
					position = position->_right;
				else
					position = position->_left;	
				depth++;					
			}
			node_type	*new_node = add_a_node(parent, depth, k);
			return (new_node->_value.second);
		}
		
	private:
		void		_init_leaf() {
			node_type	*begin = _root;
			node_type	*rbegin = _root;
			
			if (!this->empty()) {
				while (begin && begin->_left)
					begin = begin->_left;
				while (rbegin && rbegin->_right)
					rbegin = rbegin->_right;
				begin->_left = _rend;
				rbegin->_right = _end;
			}
			
			_rend = _node_alloc.allocate(1);
			_node_alloc.construct(_rend, node_type(value_type(), begin, NULL, NULL, 0, 0, 0));
			
			_end = _node_alloc.allocate(1);
			_node_alloc.construct(_end, node_type(value_type(), rbegin, NULL, NULL, 0, 0, 0));
		}
		
		node_type	*add_a_node(node_type *parent, const size_type depth, const key_type& k) {
			node_type	*new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, node_type(value_type(k, mapped_type()), parent, NULL, NULL, depth, depth, 0));
			
			_size++;
			if (_root == NULL)
				_root = new_node;
			else if (_comp(parent->_value.first, k))
				parent->_right = new_node;
			else
				parent->_left = new_node;
			if (k < _min || _size <= 1) {
				new_node->_left = _rend;
				_rend->_parent = new_node;
			}
			if (k > _max || _size <= 1) {
				new_node->_right = _end;
				_end->_parent = new_node;
			}
			_min = k < _min || parent == NULL ? k : _min;
			_max = k > _max || parent == NULL ? k : _max;
			if (new_node->_parent)
				this->equilibre(new_node->_parent);
			return new_node;
		}
	
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
			if (pos->_left && pos->_left != _rend && pos->_right && pos->_right != _end) {
				pos->_delta = pos->_left->_max_depth - pos->_right->_max_depth;
				pos->_max_depth = pos->_left->_max_depth > pos->_right->_max_depth ? pos->_left->_max_depth : pos->_right->_max_depth;
			}
			else if ((!pos->_left || pos->_left == _rend) && (pos->_right && pos->_right != _end)) {
				pos->_delta = pos->_depth - pos->_right->_max_depth;
				pos->_max_depth = pos->_right->_max_depth;
			}
			else if ((pos->_left && pos->_left != _rend) && (!pos->_right || pos->_right == _end)) {
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
			if (pos->_left && pos->_left != _rend)
				this->refresh_depth(pos->_left);
			if (pos->_right && pos->_right != _end)
				this->refresh_depth(pos->_right);
			this->set_depth(pos);
		}

		void	equilibre( node_type *pos ) {
			if (this->size() <= 1)
			 return ;
			while (pos->_parent && pos->_delta >= -1 && pos->_delta <= 1) {
				this->set_depth(pos);
				pos = pos->_parent;
			}
			this->set_depth(pos);
			if (pos->_delta < -1 || pos->_delta > 1) {
				this->refresh_depth(this->rebalance(pos));
			}
		}

	public:
		
		/****************~ITERATORS~****************/
		iterator begin() {
			node_type	*pos = _root;
			
			if (this->empty())
				return _end;
			while (pos->_left && pos->_left != _rend)
				pos = pos->_left;
			return (iterator(pos));
		}
		
		const_iterator begin() const {
			node_type	*pos = _root;
			
			if (this->empty())
				return _end;
			while (pos->_left && pos->_left != _rend)
				pos = pos->_left;
			return (iterator(pos));
		}
		
		iterator end() { return (_end); }
		
		const_iterator end() const { return (_end); }
		
		reverse_iterator rbegin() {
			node_type	*pos = _root;
			
			if (this->empty())
				return reverse_iterator(iterator(_rend));
			while (pos->_right && pos->_right != _end)
				pos = pos->_right;
			return (reverse_iterator(iterator(pos)));
		}
		
		const_reverse_iterator rbegin() const {
			node_type	*pos = _root;
			
			if (this->empty())
				return reverse_iterator(iterator(_rend));
			while (pos->_right && pos->_right != _end)
				pos = pos->_right;
			return (reverse_iterator(iterator(pos)));
		}
		
		reverse_iterator rend() { return reverse_iterator(iterator(_rend)++); }
		
		const_reverse_iterator rend() const { return reverse_iterator(iterator(_rend)++); }
		
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
				_end = NULL;
				_rend = NULL;
			}
			else { 
				if (this->_end) {
					_node_alloc.destroy(this->_end);
					_node_alloc.deallocate(this->_end, 1);
					this->_end = NULL;
				}
				if (this->_rend) {
					_node_alloc.destroy(this->_rend);
					_node_alloc.deallocate(this->_rend, 1);
					this->_rend = NULL;
				}
			}
			_size = 0;
		}
		
		pair<iterator,bool> insert (const value_type& val) {
			node_type	*position = _root;
			node_type	*parent = NULL;
			size_type	depth = 0;
				
			while ( position && position != _end && position != _rend ) {
				parent = position;						
				if (position->_value.first == val.first)
					return (ft::make_pair<iterator, bool>(iterator(position), false));
				if (_comp(position->_value.first, val.first)) // position key < k
					position = position->_right;
				else
					position = position->_left;
				depth++;						
			}
			node_type	*new_node = add_a_node(parent, depth, val.first);
			new_node->_value.second = val.second;
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
		
		private:
		
		void	destroy_node(node_type *pos) {
			node_type	*p = _root;
			
			if (pos->_value.first == _min && _size > 1) {
				while (p->_left)
					p = p->_left;
				p->_left = _rend;
				_rend->_parent = p;
				_min = p->_value.first;
			}
			if (pos->_value.first == _max && _size > 1) {
				while (p->_right) 
					p = p->_right;
				p->_right = _end;
				_end->_parent = p;
				_max = p->_value.first;
			}
			_node_alloc.destroy(pos);
			_node_alloc.deallocate(pos, 1);
		}

		void	erase_root() {
			node_type	*pos = _root;
			
			if (this->size() == 1) { // NO CHILD
				this->destroy_node(_root);
				_root = NULL;
				_end->_parent = NULL;
				_rend->_parent = NULL;
			}
			else if (_root->_left == _rend || _root->_right == _end) { // CHILD LEFT OR RIGHT ONLY
				_root = _root->_left == _rend ? _root->_right : _root->_left;
				_root->_parent = NULL;
				this->destroy_node(pos);
			}
			else { // TWO CHILD
				node_type	*min_right = pos->_right;
				while (min_right->_left) // FIN MINIMUM RIGHT SUBTREE
					min_right = min_right->_left;
				min_right->_right = pos->_right == min_right ? min_right->_right : pos->_right;
				min_right->_parent->_left = min_right->_parent->_left == min_right ? NULL : min_right->_parent->_left;
				min_right->_parent->_right = min_right->_parent->_right == min_right ? NULL : min_right->_parent->_right;
				min_right->_parent = NULL;
				min_right->_left = pos->_left;
				min_right->_left->_parent = min_right;
				min_right->_right->_parent = min_right;
				_root = min_right;
				this->destroy_node(pos); // REMOVE POS
			}
		}

		void	erase_node(node_type *to_erase) {
			node_type	*to_link;
			
			if ((!to_erase->_left || to_erase->_left == _rend) && (!to_erase->_right || to_erase->_right == _end)) { // NO CHILD
				to_link = to_erase->_parent;
				if (to_link && to_link->_right == to_erase)
					to_link->_right = NULL;
				else if (to_link)
					to_link->_left = NULL;
			}
			else if (((!to_erase->_left || to_erase->_left == _rend)) || (!to_erase->_right || to_erase->_right == _rend)) { // ONLY ONE CHILD
				to_link = !to_erase->_left || to_erase->_left == _rend ? to_erase->_right : to_erase->_left;
				to_link->_parent = to_erase->_parent;
				if (to_erase->_parent && to_erase->_parent->_right == to_erase)
					to_erase->_parent->_right = to_link;
				else if (to_erase->_parent)
					to_erase->_parent->_left = to_link;
			}
			else { // TWO CHILD
				to_link = to_erase->_right;
				while (to_link->_left) // FIN MINIMUM RIGHT SUBTREE
					to_link = to_link->_left;
				to_link->_right = to_erase->_right == to_link ? to_link->_right : to_erase->_right;
				to_link->_parent->_left = to_link->_parent->_left == to_link ? NULL : to_link->_parent->_left;
				to_link->_parent->_right = to_link->_parent->_right == to_link ? NULL : to_link->_parent->_right;
				to_link->_parent = to_erase->_parent;
				to_link->_parent->_left = to_link->_parent->_left == to_erase ? to_link : to_link->_parent->_left;
				to_link->_parent->_right = to_link->_parent->_right == to_erase ? to_link : to_link->_parent->_right;
				to_link->_left = to_erase->_left;
				if (to_link->_left)
					to_link->_left->_parent = to_link;
				if (to_link->_right)
					to_link->_right->_parent = to_link;
			}
			this->destroy_node(to_erase);
			this->refresh_depth(to_link);
			this->equilibre(to_link);			
		}

		public:
		
		size_type	erase (const key_type& k) {
			node_type	*position = _root;
				
			while ( position && position != _end && position != _rend ) {
				if ( position->_value.first == k )
				{
					if(position == _root)
						this->erase_root();
					else
						this->erase_node(position);
					_size--;
					return 1;
				}
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}
			return 0;
		}
		
		void	erase (iterator position) {
			node_type	*pos = _root;
			
			while ( pos && pos != _end && pos != _rend ) {
				if ( pos->_value.first == (*position).first)
				{
					if (position != iterator(pos))
						return ;
					else if (pos == _root)
						this->erase_root();
					else
						this->erase_node(pos);
					_size--;
					return ;
				}
				if ( _comp(pos->_value.first, (*position).first ) )				
					pos = pos->_right;
				else
					pos = pos->_left;
			}
		}
     	
		void	erase (iterator first, iterator last) {
			node_type	*pos = _root;
			iterator	tmp;
			
			while ( pos && pos != _end && pos != _rend ) {
				if ( pos->_value.first == (*first).first)
				{
					while (first != last) {
						tmp = first;
						tmp++;
						this->erase(first);
						first = tmp;
					}
					return ;
				}
				if ( _comp(pos->_value.first, (*first).first ) )				
					pos = pos->_right;
				else
					pos = pos->_left;
			}
		 }
		 
		void swap (map& x) {
			map	tmp;
			
			tmp = *this;
			*this = x;
			x = tmp;
		}

		
		/****************~LOOKUP~****************/
		size_type count (const key_type& k) const {
			node_type	*position = _root;
			
			if ( _comp(k, _min) || _comp(_max, k))
				return 0;
			while ( position && position != _end && position != _rend ) {
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
				
			if ( _comp(k, _min) || _comp(_max, k))
				return this->end();
			while ( position && position != _end && position != _rend ) {
				if ( position->_value.first == k )
					return (iterator(position));
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}				
			return this->end();
		}
		
		const_iterator find (const key_type& k) const {
			node_type	*position = _root;
				
			while ( position && position != _end && position != _rend ) {
				if ( position->_value.first == k )
					return (const_iterator(position));
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}				
			return this->end();
		}
		
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			return (make_pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k)));
		}
		
		pair<iterator,iterator> equal_range (const key_type& k) {
			return (make_pair<iterator,iterator>(lower_bound(k), upper_bound(k)));
		}
		
		iterator lower_bound (const key_type& k	) {
			node_type	*position = _root;
				
			while ( position && position != _end && position != _rend ) {
				if ( position->_value.first == k )
					return (iterator(position));
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}				
			return iterator(position);
		}
		
		const_iterator lower_bound (const key_type& k) const {
			node_type	*position = _root;
				
			while ( position && position != _end && position != _rend ) {
				if ( position->_value.first == k )
					return (iterator(position));
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}				
			return const_iterator(position);
		}
		
		iterator upper_bound (const key_type& k) {
			node_type	*position = _root;
				
			while ( position && position != _end && position != _rend ) {
				if ( position->_value.first == k )
					return (++(iterator(position)));
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}				
			return iterator(position);
		}
					
		const_iterator upper_bound (const key_type& k) const {
			node_type	*position = _root;
				
			while ( position && position != _end && position != _rend ) {
				if ( position->_value.first == k )
					return (++(iterator(position)));
				if ( _comp(position->_value.first, k) )				
					position = position->_right;
				else
					position = position->_left;
			}				
			return iterator(position);
		}
		
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

	}; // class map

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
		typename map<Key, T>::iterator	l_it = lhs.begin();		
		typename map<Key, T>::iterator	r_it = rhs.begin();
		for (; l_it != lhs.end(); l_it++) {
			if (*l_it != *r_it)
				return false;
			r_it++;
		}
		return true;
	}
	template <class Key, class T, class Compare, class Alloc> 
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return !(lhs == rhs); }
	template <class Key, class T, class Compare, class Alloc> 
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	template <class Key, class T, class Compare, class Alloc> 
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return !(rhs < lhs); }
	template <class Key, class T, class Compare, class Alloc> 
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return rhs < lhs; }
	template <class Key, class T, class Compare, class Alloc> 
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return !(lhs < rhs); }
	
	template <class Key, class T, class Compare, class Alloc> 
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
		map<Key,T,Compare,Alloc>	tmp = x;
		x = y;
		y = tmp;
	}
} // namespace ft

#endif