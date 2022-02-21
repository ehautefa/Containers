/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:41:10 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/21 18:55:26 by ehautefa         ###   ########.fr       */
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
	ft::map<char,int> econd;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	// first.debug();
	econd=first;                // second now contains 3 ints
	first=ft::map<char,int>();  // and first is now empty
	// econd.debug();

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "Size of second: " << econd.size() << '\n';
}

void	test_key_comp() {
	ft::map<char,int> mymap;

	ft::map<char,int>::key_compare mycomp = mymap.key_comp();

	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;

	std::cout << mycomp('a', 'b') << mycomp('c', '8') << std::endl;
	// mymap.debug();
 }

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

void	test_count() {
	ft::map<char,int> mymap;
	char c;

	mymap ['c']=101;
	mymap ['a']=202;
	mymap ['f']=303;

	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c)>0)
		std::cout << " is an element of mymap.\n";
		else 
		std::cout << " is not an element of mymap.\n";
	}
}

void	test_constructor() {
	ft::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;
	// first.debug();

	first.clear();
	ft::map<char,int> third (first);
	// third.debug();

	ft::map<char,int,classcomp> fourth;                 // class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt);
}

void	test_iterator() {
	ft::map<char, int> map;

	map['z']=10;
	map['e']=30;
	map['h']=50;
	map['d']=70;

	ft::map<char,int>::iterator	it = map.begin();
	std::cout << it->first << std::endl;

	map.debug();
	
}


int main() {
	test_constructor();
	test_key_comp();
	test_operator();
	test_count();
	test_iterator();
}