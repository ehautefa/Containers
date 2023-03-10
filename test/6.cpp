/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:41:10 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/10 20:41:53 by ehautefa         ###   ########.fr       */
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
	#include "../map.hpp"
#endif

template <class Key, class T>
void	debug(ft::map<Key, T> &map) {
	std::cout << "SIZE: " << map.size() << std::endl;
	
	typename ft::map<Key, T>::iterator	it = map.begin();
	for (; it != map.end(); ++it) {
		std::cout << "KEY: " << it->first << "	VALUE: " << it->second << std::endl;
	}
}

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

	debug<int, int>(first);
	second=first;
	first=ft::map<int,int>();
	debug<int, int>(second);

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
	debug<char, int>(mymap);
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
	debug<char, int>(first);

	first.clear();
	ft::map<char,int> third (first);
	debug<char, int>(third);

	ft::map<char,int,classcomp> fourth;                 // class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt);
}

void	test_iterator() {
	ft::map<char, int> map;

	map['e']=10;
	map['a']=30;
	map['h']=50;
	map['d']=70;

	ft::map<char,int>::iterator	it = map.begin();
	ft::map<char,int>::iterator	ite = map.end();
	
	debug<char, int>(map);

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
	debug<char, int>(mymap);

	// second insert function version (with hint position):
  	ft::map<char,int>::iterator it = mymap.begin();
  	mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
  	mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting
	debug<char, int>(mymap);

	ft::map<char,int> anothermap;
  	anothermap.insert(mymap.begin(),mymap.find('c'));
	debug<char, int>(anothermap);
}

void	test_bound() {
	std::cout << "\nTEST BOUND\n";
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['e']=80;
	mymap['f']=100;

	itlow=mymap.lower_bound ('d');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	// print content:
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

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
	debug<char, int>(foo);
	debug<char, int>(bar);

	swap(foo, bar);
	debug<char, int>(foo);
	debug<char, int>(bar);
}

void	test_reverse_iterator() {
	std::cout << "\nTEST REVERSE ITERATOR\n";
	ft::map<char, int> test;

	test['t'] = 456;
	test['1'] = 2147483647;
	test[')'] = -8;
	test['7'] = 789;
	test['$'] = 45;

	// test.debug();
	ft::map<char, int>::reverse_iterator	rit;
	rit = test.rbegin();
	for (; rit != test.rend(); rit++)
		std::cout << "F " << rit->first << "	S " << rit->second << std::endl;
}

void	test_erase() {
	ft::map<int, int> map;
	ft::map<int, int>::iterator it;
	
	map[-898] = 0;
	map[78] = 1;
	map[6] = 2;
	map[54] = 3;
	map[5] = 4;
	map[123] = 5;
	map[7] = 6;
	map[-6] = 7;
	map[-89] = 8;
	map[7896] = 9;

	debug(map);
	it = map.find(78);
	map.erase(it);
	debug(map);
	it = map.find(6);
	map.erase(it);
	debug(map);
	it = map.find(-6);
	map.erase(it);
	debug(map);
	it = map.find(54);
	map.erase(it);
	debug(map);
	map.erase(map.begin(), map.end());
	debug(map);
}

void	test_const_iterator() {
	ft::map<int, int> map;
	
	map[1] = 32;
	map[-28] = 112;
	map[99] = 21474836;
	map[5] = 47;

	ft::map<int, int>::const_iterator it = map.begin();
	ft::map<int, int>::const_iterator ite = map.end();
	for (; it != ite; it++) {
		std::cout << it->first << " ";
	}
}

void	test_erase_root() {
	std::cout << "\nTEST ERASE\n";
	ft::map<char,int> mymap;

	// insert some values:
	mymap['a']=10;

	mymap.erase('a');
	debug(mymap);
	
	mymap['b']=20;
	mymap['c']=30;

	mymap.erase('b');
	
	mymap['b']=20;
	mymap.erase('c');
	debug(mymap);
	mymap.erase('b');
	debug(mymap);
	
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;


	std::cout << "\nMY MAP\n";
	debug(mymap);
	mymap.erase ('b');   
	std::cout << "\nERASE 'b' ITERATOR\n";
	debug(mymap);
	std::cout << "\nERASE 'c' KEY\n";
	mymap.erase ('c');
	debug(mymap);
	mymap.erase(mymap.begin(), mymap.end());
	debug(mymap);
}

void	test_value_comp() {
	ft::map<char,int> mymap;

	mymap['x']=1001;
	mymap['y']=2002;
	mymap['z']=3003;

	std::cout << "mymap contains:\n";

	ft::pair<char,int> highest = *mymap.rbegin();          // last element

	ft::map<char,int>::iterator it = mymap.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mymap.value_comp()(*it++, highest) );
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
	test_reverse_iterator();
	test_erase_root();
	test_erase();
	test_value_comp();
}