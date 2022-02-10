/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:52:53 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/10 14:01:32 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

namespace	ft {
	template < class Key, class T, class Compare = less<Key>, class Alloc = allocator<pair<const Key,T> > >
	class map
	{
		public:
			typedef	Key												key_type;
			typedef	T												mapped_type;
			typedef	pair<const key_type,mapped_type>				value_type;
			typedef	Compare											key_compare;
			typedef													value_compare;
			typedef													allocator_type;
			typedef	typename allocator_type::reference				reference;
			typedef	typename allocator_type::const_reference		const_reference;
			typedef	typename allocator_type::pointer				pointer;
			typedef	typename allocator_type::const_pointer			const_pointer;
			// typedef Type*								 			iterator;
			// typedef const Type*										const_iterator;
			// typedef typename ft::reverse_iterator<iterator> 		reverse_iterator;
			// typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename std::size_t							size_type;
			typedef typename std::ptrdiff_t							difference_type;
		
		
		// explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		// template <class InputIterator>
  		// map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
		// map (const map& x);
		// ~map();
		// iterator begin();
		// const_iterator begin() const;
		// void clear();
		// size_type count (const key_type& k) const;
		// bool empty() const;
		// iterator end();
		// const_iterator end() const;
		
		// pair<const_iterator,const_iterator> 
		// equal_range (const key_type& k) const;
		// pair<iterator,iterator>
		// equal_range (const key_type& k);

		// void erase (iterator position);
		// size_type erase (const key_type& k);
     	// void erase (iterator first, iterator last);
		
	};
}

#endif