/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:41:10 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/18 11:33:46 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <iomanip>

#if STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "../map/map.hpp"
#endif

void	test_operator() {
	ft::map<char,int> first;
	ft::map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	first.debug();
	second=first;                // second now contains 3 ints
	first=ft::map<char,int>();  // and first is now empty
	second.debug();

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "Size of second: " << second.size() << '\n';
}

void	test_key_comp() {
	ft::map<char,int> mymap;

	ft::map<char,int>::key_compare mycomp = mymap.key_comp();

	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;

	std::cout << mycomp('a', 'b') << mycomp('c', '8') << std::endl;
	mymap.debug();
 }

void	test_constructor() {
	ft::map<int, int>	test;
	(void)test;

	test[5] = 5;
	test[5] = 4;
	test[2] = 3;
	test[7] = 4;
	test[3] = 2;
	test.debug();
}


int main() {
	test_constructor();
	test_key_comp();
	test_operator();
}