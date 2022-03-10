/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:25:38 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/10 10:23:53 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>

namespace	ft {
	template <class Type>
	std::string	itoa(Type n)
	{
		std::stringstream out;
		out << n;
		return(out.str());
	}

	template <typename T>
	void	swap( T & lhs, T & rhs )
	{
		T	tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}

	template<class InputIterator>
  	typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last) {
		typename iterator_traits<InputIterator>::difference_type	to_ret = 0;
		for (; first != last; first++) {
			to_ret++;
			
		}
		return (to_ret);
	  }

}