/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:16:47 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/14 16:17:48 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
#define AVL_HPP

namespace	ft {

	template < class Key, class T >
	struct node
	{
		ft::pair<Key, T> 		_value;
		node					*_parent;
		node					*_left;
		node					*_right;

		node( void ) : _value(), _parent(NULL), _left(NULL), _right(NULL) {}
		~node() {}
	};

	class avl
	{
		private:
			
		public:
			avl(/* args */);
			~avl();
	};
	
	
}
	

#endif