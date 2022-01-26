/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:11:18 by ehautefa          #+#    #+#             */
/*   Updated: 2022/01/25 14:55:32 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace	ft
{
	template <class Type, class Allocator = allocator<Type>>
	class	vector
	{
		public:
			vector( void );
			explicit vector (const allocator_type& alloc = allocator_type());	
			explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type());
        	vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type());
			vector (const vector& x);

		private:
	};
}