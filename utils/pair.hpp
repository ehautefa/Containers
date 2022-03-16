/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:54:41 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/16 17:59:31 by ehautefa         ###   ########.fr       */
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

		pair( void ) : first(), second() {};
		template<class U, class V>
		pair (const pair < U, V > & pr) : first(pr.first), second(pr.second) {};
		pair (const T1 & a, const T2 & b) : first(a), second (b) {};
		~pair( void ) {};

		template <class U, class V>
		pair<T1, T2>	&operator=(const pair<U, V> & pr) {
			first = static_cast<T1>(pr.first);
			second = static_cast<T2>(pr.second);
			return (*this);
		}
	};
	
	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 x, T2 y) { return ( pair<T1,T2>(x,y) ); }

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return (lhs.first == rhs.first && lhs.second == rhs.second); }
	template <class T1, class T2>
  	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (!(lhs == rhs)); }
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second)); }
	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (!(rhs < lhs)); }
	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (rhs < lhs); }
	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (!(lhs < rhs)); }
}

#endif