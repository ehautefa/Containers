/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:10:33 by ehautefa          #+#    #+#             */
/*   Updated: 2022/01/26 15:55:27 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compare.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include <iostream>
#include <vector>
#include <cctype>       // std::tolower

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

	return (0);
}