/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:52:00 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/09 15:57:21 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>

#if STL
	#include <map>
	#include <stack>
	#include <vector>
	#include <iterator>
	namespace ft = std;
#else
	#include "../vector/vector.hpp"
#endif

void	test_operator() 
{
	ft::vector<int> myvector (10);   // 10 zero-initialized elements
	ft::vector<int>::size_type sz = myvector.size();	
	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector[i]=i;	
	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
	  int temp;
	  temp = myvector[sz-1-i];
	  myvector[sz-1-i]=myvector[i];
	  myvector[i]=temp;
	}	
	std::cout << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
	  std::cout << ' ' << myvector[i];
	std::cout << '\n';
	try
  	{
		  std::cout << myvector[1] << std::endl;
		  std::cout << myvector[0] << std::endl;
  	}
  	catch(const std::exception& e)
  	{
		  std::cout << e.what() << '\n';
  	}
}

void	test_constructor_vector()
{
		ft::vector<int> first;                                // empty vector of ints
		ft::vector<int> second (4,100);
		for (size_t i = 0; i < second.size() ; i++)
			std::cout << second[i] << " ";
		std::cout << std::endl;               // four ints with value 100
		ft::vector<int> third (second.begin(),second.end());  // iterating through second
		ft::vector<int> fourth (second);                       // a copy of third
		for (size_t i = 0; i < fourth.size(); i++)
			std::cout << fourth[i] << " ";
		std::cout << std::endl;
		int myints[] = {16,2,77,29};
		ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		std::cout << "The contents of fifth are:";
		for (size_t i = 0; i < fifth.size(); i++)
			std::cout << fourth[i] << " ";
		std::cout << std::endl;
}

void	test_rel_op_swap()
{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (2,200);  // two ints with a value of 200

		for (size_t i = 0; i < foo.size(); i++)
			std::cout << "foo : " << foo[i] << " ";
		std::cout << std::endl;

		for (size_t i = 0; i < bar.size(); i++)
			std::cout << "bar : " << bar[i] << " ";
		std::cout << std::endl;

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

		ft::swap(foo,bar);

		for (size_t i = 0; i < foo.size(); i++)
			std::cout << "foo : " << foo[i] << " ";
		std::cout << std::endl;

		for (size_t i = 0; i < bar.size(); i++)
			std::cout << "bar : " << bar[i] << " ";
		std::cout << std::endl;
		
		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void	test_resize()
{
	ft::vector<int> test;

	for (int i=1;i<10;i++)
		test.push_back(i);

	std::cout << "ORIGIN:" << std::endl;
	for (size_t i=0;i<test.size();i++)
		std::cout << ' ' << test[i];
	std::cout << '\n';
	test.resize(5);
	
	std::cout << "RESIZE(5):" << std::endl;
	for (size_t i=0;i<test.size();i++)
		std::cout << ' ' << test[i];
	std::cout << '\n';
	test.resize(8,100);
	
	for (size_t i=0;i<test.size();i++)
		std::cout << ' ' << test[i];
	std::cout << '\n';
	test.resize(12);

	std::cout << "test contains:";
	for (size_t i=0;i<test.size();i++)
		std::cout << ' ' << test[i];
	std::cout << '\n';
}

void	test_reserve() {
	ft::vector<int> foo;

	try
	{
		foo.reserve(10);
		std::cout << foo.capacity() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void	test_push_back()
{
	ft::vector<int>::size_type sz;
	
	ft::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
		sz = foo.capacity();
		std::cout << "capacity changed: " << sz << '\n';
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
		sz = bar.capacity();
		std::cout << "capacity changed: " << sz << '\n';
		}
	}
}

void test_vector() {
    ft::vector<int> myVector(3);

    for (std::size_t i=0; i<myVector.size(); i++)
        myVector[i] = i;

    myVector.reserve(6);
    myVector.reserve(47);
}

void	debug(ft::vector<int> & v)
{
	std::cout << "CAP: " << v.capacity() << " SIZE: " << v.size() << std::endl;
	for(size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

void test_resize2() {
    ft::vector<int> v(6, 3);
    debug(v);
    v.reserve(10);
    debug(v);
    v.resize(7);
    debug(v);
    v.resize(12);
    debug(v);
    v.resize(3);
    debug(v);
	v.resize(16);
    debug(v);
	v.resize(28);
    debug(v);
}

void	test_pop_back() {
	ft::vector<int> myvector;
	int sum (0);
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	while (!myvector.empty())
	{
		sum+=myvector.back();
		myvector.pop_back();
	}

	std::cout << "The elements of myvector add up to " << sum << '\n';
}

void	test_at() {
	ft::vector<int> myvector (10, 3);

	std::cout << "AT" << std::endl;
	try
	{
		myvector.at(5);
		myvector.at(0);
		myvector.at(189);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
}

void	test_front() {
	ft::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);

	// now front equals 78, and back 16

	myvector.front() -= myvector.back();

	std::cout << "myvector.front() is now " << myvector.front() << '\n';

}

void	test_assign() {
	ft::vector<int>	test(5, 3);

	test.assign(4, 100);
	debug(test);
	test.assign(18, 890);
	debug(test);
	test.assign(1, 890);
	debug(test);

	std::vector<int> test_std(10, 42);
	test.assign(test_std.begin(), test_std.end());
	debug(test);
}

int main()
{
	test_operator();
	test_constructor_vector();
	test_rel_op_swap();
	test_resize();
	test_resize2();
	test_push_back();
	test_reserve();
	test_vector();
	test_at();
	test_front();
	test_assign();
	return 0;
}