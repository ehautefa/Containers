/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:11:18 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/01 18:48:50 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator>
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"

namespace	ft
{
	template <class Type, class Allocator = std::allocator<Type> >
	class	vector
	{
		public:
			typedef Type										value_type;
			typedef Allocator									allocator_type;
			typedef typename std::size_t						size_type;
			typedef typename std::ptrdiff_t						difference_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef	typename Allocator::pointer					pointer;
			typedef	typename Allocator::const_pointer			const_pointer;
			// typedef typename std::iterator<iterator> 		iterator;
			// typedef typename std::iterator<const_iterator> 	const_iterator;
			// typedef typename std::reverse_iterator<iterator> reverse_iterator;
			// typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;
			
		private:
			Type*			_arr;
			Allocator		_alloc;
			size_type		_size;
			size_type		_capacity;
			
		public:
			/************* ~EXCEPTION~ *************/
			class length_error : public std::exception {
				public:
			  		const char *what( void ) const throw() {
						  return ("vector::_M_fill_insert");
					  }
			};
			
			/************* ~CONSTRUCTOR~ *************/
			explicit vector (const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_capacity = 0;
				_arr = _alloc.allocate(0);
				// _alloc.construct(_arr, value_type());
				_size = 0;
			}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())  : _alloc(alloc){
				_alloc = alloc;
				_size = n;
				_capacity = 1;
				while (_capacity < _size)
					_capacity *= 2;
				_arr = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_arr[i], val);
			}
			template <class InputIterator, ft::enable_if<ft::is_integral<InputIterator>::value, bool> >
         	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
				_alloc = alloc;
				_size = last - first;
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
			allocator_type get_allocator() const {
				return (_alloc);
			}

			size_type size() const {
				return (_size);
			}

			size_type capacity() const {
				return (_capacity);
			}

			size_type max_size() const {
				return (_alloc.max_size());
			}

			bool empty() const {
				if (_size == 0)
					return true;
				else
					return false;
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
			
			reference operator[] (size_type n) {
				return (_arr[n]);
			}

			const_reference operator[] (size_type n) const {
				return (_arr[n]);
			}

			/************* ~ITERATOR~ *************/
			// iterator begin() {
			// 	return (_arr[0]);	
			// }

			// const_iterator begin() const {
			// 	return (_arr[0]);	
			// }

			/************* ~METHOD~ *************/
			void	clear() {
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_arr[i]);
				_size = 0;
			}
			
			void resize (size_type n, value_type val = value_type()) {
				if (n < _size)
				{
					for (size_t i = n; i < _size; i++)
						_alloc.destroy(&_arr[i]);
					_size = n;
				}
				else if (n > _size)
				{
					try {this->reserve(n);}
					catch (std::exception & e) { std::cout << e.what() << std::endl;}
					for (size_t i = _size; i < n; i++)
						_alloc.construct(&_arr[i], val);
					_size = n;
				}
			}

			void reserve (size_type n) {
				if (n > this->max_size())
					throw length_error();
				else if (n > _capacity)
				{
					vector	tmp = *this;
					this->clear();
					_alloc.deallocate(_arr,_capacity);
					_capacity = n;
					_arr = _alloc.allocate(_capacity);
					_size = tmp.size();
					for (size_t i = 0; i < _size; i++)
						_alloc.construct(&_arr[i], tmp[i]);
				}
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
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (!(lhs[i] == rhs[i]))
				return false;
		}
		return true;
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs));}
	// template <class T, class Alloc>
 	// bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
	// template <class T, class Alloc>
  	// bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(rhs < lhs));}
	// template <class T, class Alloc>
  	// bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs);}
	// template <class T, class Alloc>
  	// bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs)); }
}