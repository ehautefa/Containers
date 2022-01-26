/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:10:33 by ehautefa          #+#    #+#             */
/*   Updated: 2022/01/26 16:59:11 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cctype>       // std::tolower

#if STL
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "compare.hpp"
	#include "enable_if.hpp"
	#include "is_integral.hpp"
	#include "pair.hpp"
#endif

// a case-insensitive comparison function:
bool mycomp (char c1, char c2)
{ 
	return std::tolower(c1)<std::tolower(c2); 
}

struct trivial
{
	int val;
};

bool mypredicate (int i, int j) {
  return (i==j);
}

int main()
{
	std::cout << "is_integral<trivial> == " << std::boolalpha
		<< ft::is_integral<trivial>::value << std::endl;
	std::cout << "is_integral<int> == " << std::boolalpha
		<< ft::is_integral<int>::value << std::endl;
	std::cout << "is_integral<float> == " << std::boolalpha
		<< ft::is_integral<float>::value << std::endl;

  	char foo[]="Apple";
  	char bar[]="apartment";

  	std::cout << std::boolalpha;

  	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

  	std::cout << "Using default comparison (operator<): ";
  	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
  	std::cout << '\n';

  	std::cout << "Using mycomp as comparison object: ";
  	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
  	std::cout << '\n';

	int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
	std::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

	// using default comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3]=81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	ft::pair <std::string,double> product1;                     // default constructor
	ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	ft::pair <std::string,double> product3 (product2);          // copy constructor

	product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

	product2.first = "shoes";                  // the type of first is string
	product2.second = 39.90;                   // the type of second is double

	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
	return (0);
}