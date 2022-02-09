/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:11:18 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/09 14:48:46 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator>
#include <cstdlib>
#include "vector_iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/utils.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/compare.hpp"
#include "../utils/iterator_traits.hpp"


namespace	ft
{
	template <class Type, class Allocator = std::allocator<Type> >
	class	vector
	{
		public:
			typedef Type											value_type;
			typedef Allocator										allocator_type;
			typedef typename std::size_t							size_type;
			typedef typename std::ptrdiff_t							difference_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef	typename Allocator::pointer						pointer;
			typedef	typename Allocator::const_pointer				const_pointer;
			typedef Type*								 			iterator;
			typedef const Type*										const_iterator;
			typedef typename ft::reverse_iterator<iterator> 		reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			
		private:
			Type*			_arr;
			Allocator		_alloc;
			size_type		_size;
			size_type		_capacity;
			
		public:
			
			/************* ~CONSTRUCTOR~ *************/
			explicit vector (const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_capacity = 0;
				_arr = _alloc.allocate(0);
				_size = 0;
			}

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())  : _alloc(alloc){
				_alloc = alloc;
				_size = n;
				_capacity = _size;
				_arr = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_arr[i], val);
			}

			template <class InputIterator> 
			vector (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,  const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_size = ft::distance(first, last);
				_capacity = _size;
				std::cout << _size << std::endl;
				_arr = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(&_arr[i], *first);
					first++;
				}
			}

			vector (const vector& x) {
				_alloc = x.get_allocator();
				_size = x.size();
				_capacity = x.capacity();
				_arr = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_arr[i], x[i]);
			}

			~vector() {
				this->clear();
				_alloc.deallocate(_arr, _capacity);
			}

			/************* ~GETTER~ *************/
			allocator_type get_allocator() const { return (_alloc); }

			size_type size() const { return (_size); }

			size_type capacity() const { return (_capacity); }

			size_type max_size() const { return (_alloc.max_size()); }

			bool empty() const {
				if (_size == 0)
					return true;
				else
					return false;
			}

			reference back() { return (_arr[this->size() - 1]); }
			const_reference back() const { return (_arr[this->size() - 1]); }
			reference front() { return (_arr[0]); }
			const_reference front() const { return (_arr[0]); }

			reference at (size_type n) {
				std::string error_msg = "vector::_M_range_check: __n (which is " + itoa(n) + ") >= this->size() (which is " + itoa(_size) + ")";
				if (n < 0 || n > _size - 1)
					throw std::out_of_range(error_msg);
				return (_arr[n]);
			}

			const_reference at (size_type n) const {
				std::string error_msg = "vector::_M_range_check: __n (which is " + itoa(n) + ") >= this->size() (which is " + itoa(_size) + ")";
				if (n < 0 || n > _size - 1)
					throw std::out_of_range(error_msg);
				return (_arr[n]);
			}

			/************* ~OPERATOR~ *************/
			vector& operator= (const vector& x) {
				this->clear();
				_alloc.deallocate(_arr, _capacity);
				_alloc = x.get_allocator();
				_size = x.size();
				_capacity = x.capacity();
				_arr = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_arr[i], x[i]);
				return (*this);
			}
			
			reference operator[] (size_type n) { return (_arr[n]); }
			const_reference operator[] (size_type n) const { return (_arr[n]); }

			/************* ~ITERATOR~ *************/
			iterator 				begin()	{ return (&_arr[0]); }
			const_iterator 			begin() const { return (&_arr[0]); }
			iterator 				end() 	{ return (&_arr[_size]); }
			const_iterator 			end() 	const { return (&_arr[_size]);	 }
			reverse_iterator 		rbegin()	{ return (reverse_iterator(this->end())); }
			const_reverse_iterator 	rbegin() 	const { return (const_reverse_iterator(this->end())); }
			reverse_iterator 		rend() { return (reverse_iterator(this->begin()));	}
			const_reverse_iterator	rend() const { return const_reverse_iterator(this->begin()); }

			/************* ~METHOD WITH ITERATOR~ *************/
			template <class InputIterator>
  			void assign (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
				size_type size = ft::distance(first, last);
				this->clear();
				if (size > _capacity) {
					try {this->reserve(size);}
					catch (std::exception & e) { throw e; }
				}
				for (size_type i = _size; i < size; i++) {
					_alloc.construct(&_arr[i], *first);
					++first;
				}
				_size = size;
			}
			
			void assign (size_type n, const value_type& val) {
				this->clear();
				if (n > _capacity) {
					try {this->reserve(n);}
					catch (std::exception & e) { throw e; }
				}
				for (size_type i = _size; i < n; i++)
					_alloc.construct(&_arr[i], val);
				_size = n;
			}

			iterator erase (iterator position) {
				iterator	to_ret;
				to_ret = position;
				while (position != this->end())
				{
					_alloc.destroy(position);
					if (position + 1 != this->end())
						_alloc.construct(position, *(position + 1));
					++position;
				}
				_size--;
				return (position);
			}

			iterator erase (iterator first, iterator last) {
				iterator	to_ret;
				to_ret = last;
				size_t end_size = _size - ft::distance(first, last);
				while (first != this->end())
				{
					_alloc.destroy(first);
					if (last != this->end()) {
						_alloc.construct(first, *last);
						++last;
					}
					++first;
				}
				_size = end_size;
				return (to_ret);
			}

			iterator insert (iterator position, const value_type& val) {
				iterator	to_ret;
				value_type	old_value;
				value_type	tmp	= val;
				size_t 		i	= ft::distance(this->begin(), position);

				if (_size == _capacity) {
					try { this->reserve(_capacity * 2); }
					catch (std::exception & e) { throw e;}
				}
				_size++;
				position = &_arr[i];
				to_ret = position;
				for (; i < _size; i++)
				{
					old_value = tmp;
					tmp = *position;
					_alloc.destroy(position);
					_alloc.construct(position, old_value);
					++position;
				}
				return (to_ret);
			}

    		void insert (iterator position, size_type n, const value_type& val) {
				size_t	old_size	= _size;
				size_t	cap			= _capacity;
				size_t 	i			= ft::distance(this->begin(), position);

				while (_size + n > cap)
					cap *= 2;
				while (cap != _capacity) {
					try { this->reserve(cap); }
					catch (std::exception & e) { throw e;}
				}
				_size += n;
				for (size_t j = _size - 1; j >= i + n; j--) {
					if (j < old_size)
						_alloc.destroy(&_arr[j]);
					_alloc.construct(&_arr[j], _arr[j - n]);
				}
				for (; n > 0; n--)
				{
					if (i < old_size)
						_alloc.destroy(&_arr[i]);
					_alloc.construct(&_arr[i], val);
					i++;
				}
			}

			template <class InputIterator>
  			void insert (iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
				size_t	old_size	= _size;
				size_t	cap			= _capacity;
				size_t 	i			= ft::distance(this->begin(), position);
				size_t	n			= ft::distance( first, last );

				while (_size + n > cap)
					cap *= 2;
				while (cap != _capacity) {
					try { this->reserve(cap); }
					catch (std::exception & e) { throw e;}
				}
				_size += n;
				for (size_t j = _size - 1; j >= i + n; j--) {
					if (j < old_size)
						_alloc.destroy(&_arr[j]);
					_alloc.construct(&_arr[j], _arr[j - n]);
				}
				for (; n > 0; n--)
				{
					if (i < old_size)
						_alloc.destroy(&_arr[i]);
					_alloc.construct(&_arr[i], *first);
					i++;
					first++;
				}
			}

			/************* ~METHOD~ *************/
			void	clear() {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_arr[i]);
				_size = 0;
			}
			
			void resize (size_type n, value_type val = value_type()) {
				if (n < _size)
				{
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(&_arr[i]);
					_size = n;
				}
				else if (n > _size && n > _capacity)
				{
					try {this->reserve(n > 2 * _size ? n : 2 * _size);}
					catch (std::exception & e) { throw e;}
					for (size_type i = _size; i < n; i++)
						_alloc.construct(&_arr[i], val);
					_size = n;
				}
				else if (n > _size) {
					for (size_type i = _size; i < n; i++)
						_alloc.construct(&_arr[i], val);
					_size = n;
				}
			}

			void reserve (size_type n) {
				if (n > this->max_size())
					throw std::length_error("vector::_M_fill_insert");
				else if (n > _capacity)
				{
					vector	tmp = *this;
					this->clear();
					_alloc.deallocate(_arr,_capacity);
					_capacity = n;
					_arr = _alloc.allocate(_capacity);
					_size = tmp.size();
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&_arr[i], tmp[i]);
				}
			}

			void	pop_back() {
				this->resize(_size - 1);
			}
			
			void push_back (const value_type& val) {
				if (_size == 0 && _capacity == 0)
					this->reserve(1);
				else if (_size >= _capacity)
					this->reserve(_size * 2);
				_alloc.construct(&_arr[_size], val);
				_size++;
			}

			/************* ~SWAP~ *************/
			void swap (vector& x) {
				vector	tmp = x;
				x = *this;
				*this = tmp;
			}

			void	debug()
			{
				std::cout << "CAP: " << this->capacity() << " SIZE: " << this->size() << std::endl;
				for(size_t i = 0; i < this->size(); i++)
					std::cout << (*this)[i] << " ";
				std::cout << std::endl << std::endl;
			}	
	};

	/************* ~SWAP~ *************/
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		vector<T,Alloc>	tmp = x;
		x = y;
		y = tmp;
	}

	/************* ~RELATIONAL OPERATOR~ *************/

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (size_t	i = 0; i < lhs.size(); i++)
		{
			if (!(lhs[i] == rhs[i]))
				return false;
		}
		return true;
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs));}
	template <class T, class Alloc>
 	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
	template <class T, class Alloc>
  	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(rhs < lhs));}
	template <class T, class Alloc>
  	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs);}
	template <class T, class Alloc>
  	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs)); }
}