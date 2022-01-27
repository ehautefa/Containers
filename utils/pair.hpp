/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:54:41 by ehautefa          #+#    #+#             */
/*   Updated: 2022/01/27 12:32:19 by ehautefa         ###   ########.fr       */
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
		~pair( void ) {};

		pair	&operator=(const pair & pr) {
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};
	
	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 x, T2 y) {
		return ( pair<T1,T2>(x,y) );
	}
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs.first == lhs.first && lhs.second == rhs.second);
	}
	template <class T1, class T2>
  	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		  return (!(lhs == rhs));
	}
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second));
	}
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (!(rhs < lhs));
	}
	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (rhs < lhs);
	}
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (!(lhs < rhs));
	}
}

#endif