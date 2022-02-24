/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:41:10 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/24 16:23:14 by ehautefa         ###   ########.fr       */
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
	ft::map<int,int> first;
	ft::map<int,int> second;

	first[50]=8;
	first[17]=16;
	first[72]=32;
	first[23]=48;
	first[19]=61;
	first[12]=32;
	first[14]=32;
	first[9]=32;
	first[86]=32;
	first[82]=32;
	first[94]=32;
	first[90]=32;

	first.debug();
	second=first;
	first=ft::map<int,int>();
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

	map['e']=10;
	map['a']=30;
	map['h']=50;
	// map['d']=70;

	ft::map<char,int>::iterator	it = map.begin();
	ft::map<char,int>::iterator	ite = map.end();
	
	map.debug();

	for (; it != ite; it++) {
		std::cout << it->first << std::endl;
	}
	
}

void	test_insert() {
	std::cout << "\nTEST INSERT\n";
	ft::map<char,int> mymap;

  	// first insert function version (single parameter):
  	mymap.insert ( ft::pair<char,int>('a',100) );
  	mymap.insert ( ft::pair<char,int>('z',200) );
	
  	ft::pair<ft::map<char,int>::iterator,bool> ret;
  	ret = mymap.insert ( ft::pair<char,int>('z',500) );
  	if (ret.second==false) {
  	  std::cout << "element 'z' already existed";
  	  std::cout << " with a value of " << ret.first->second << '\n';
  	}
	mymap.debug();

	// second insert function version (with hint position):
  	ft::map<char,int>::iterator it = mymap.begin();
  	mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
  	mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting
	mymap.debug();

	ft::map<char,int> anothermap;
  	anothermap.insert(mymap.begin(),mymap.find('c'));

	anothermap.debug();
}

void	test_bound() {
	std::cout << "\nTEST BOUND\n";
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.debug();
	ft::map<char,int> anothermap;
  	anothermap.insert(itlow, itup);
	anothermap.debug();	
}

void	test_swap() {

	std::cout << "\nTEST SWAP\n";
	ft::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);
	foo.debug();
	bar.debug();

	swap(foo, bar);
	foo.debug();
	bar.debug();
}

int main() {
	test_constructor();
	test_key_comp();
	test_operator();
	test_count();
	test_iterator();
	test_insert();
	test_bound();
	test_swap();
}