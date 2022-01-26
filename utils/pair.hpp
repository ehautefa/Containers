/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:54:41 by ehautefa          #+#    #+#             */
/*   Updated: 2022/01/26 16:54:44 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace	ft
{
	template <class T1, class T2>
	struct pair {
		T1	first;
		T2	second;

		pair( void ) {};
		pair (const pair<T1,T2>& pr) : first(pr.first), second(pr.second) {};
		pair (const T1 & a, const T2 & b) : first(a), second (b) {};
		
	};
	
	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 x, T2 y) {
		return ( pair<T1,T2>(x,y) );
	}
}

#endif