/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:25:38 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/07 15:07:52 by ehautefa         ###   ########.fr       */
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

}