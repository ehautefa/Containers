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
	#include "../vector.hpp"
#endif

template<class T>
void debug(ft::vector<T>& v) {
	std::cout << "\n_arr: ";
	for (size_t i=0; i<v.size(); i++)
		std::cout << v[i] << (i != v.size() - 1 ? ", " : "");
	std::cout << "\n_size: " << v.size() << std::endl;
	std::cout << std::endl;
}

void	test_maz_insert() {
	std::cout << "HERE\n";
	ft::vector<int> myvector (3,100);
	ft::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::vector<int> anothervector (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_push_back() {
	int sz = 20;
	ft::vector<int> v;

	v.reserve(6);

	std::cout << "Initial size: " << v.size() << ", capacity: " << v.capacity() << '\n';
	std::cout << "Size:  Capacity:\n" << std::left;
	while (sz-- > 0) {
		v.push_back(sz);
		std::cout << std::setw( 7) << v.size() << std::setw(11) << v.capacity() << '\n';
	}
	std::cout << "\nFinal size: " << v.size() << ", capacity: " << v.capacity() << '\n';

	std::cout << "Vector: " << std::endl;
	for (std::size_t i=0; i<v.size(); i++)
		std::cout << v[i] << ", ";
	std::cout << std::endl;
}

void test_reserve() {
	try {
		ft::vector<int> foo;
		debug(foo);
		for (int i=0; i<5; i++) {
			foo.reserve(i*3);
			std::cout << foo.capacity() << std::endl;
		}
		foo.reserve(foo.max_size() + 1);
	} catch (const std::exception& e) {
		std::cout << "HERE " << e.what() << std::endl;
	}

	try {
		ft::vector<int> foo(3);
		debug(foo);
		for (int i=0; i<5; i++) {
			foo.reserve(i*3);
			std::cout << foo.capacity() << std::endl;
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void test_resize() {
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
	try {
		v.resize(v.max_size() + 1);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void test_pop_back() {
	ft::vector<int> v(5, 3);
	debug(v);
	v.pop_back();
	debug(v);
}

void test_swap() {
	ft::vector<int> v1(5, 3);
	ft::vector<int> v2(3, 5);
	debug(v1);
	debug(v2);
	v1.swap(v2);
	debug(v1);
	debug(v2);
}

void test_assign() {
	ft::vector<int> v1(5, 3);
	debug(v1);
	v1.assign(7, 2);
	debug(v1);
	v1.assign(3, 6);
	debug(v1);
	try {
		v1.assign(v1.max_size() + 1, 7);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::deque<int> v2(10, 9);
	v1.assign(v2.begin(), v2.end());
	debug(v1);
}

void test_insert() {
	ft::vector<int> v(10, 3);
	std::deque<int> d(10, 9);

	debug(v);
	v.insert(v.begin() + 2, 4);
	debug(v);
	v.insert(v.begin() + 5, 4, 5);
	debug(v);
	v.insert(v.begin() + 8, d.begin(), d.end());
	debug(v);
}

void test_iterator() {
	ft::vector<int>    myvec;
    for (size_t i = 0; i < 13; i++)
        myvec.push_back(i + 42);
    ft::vector<int>::const_iterator    it = myvec.begin();
    std::cout << "FIRST: " << *it << std::endl;
    for (; it != myvec.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    ft::vector<int>::reverse_iterator    rit = myvec.rbegin();
    for (; rit != myvec.rend(); rit++)
        std::cout << *rit << " ";
    std::cout << std::endl;
    ft::vector<int>::const_reverse_iterator test = myvec.rend();
    (void)test;
}

void test_erase() {
	ft::vector<int> v;

	for (size_t i=0; i<10; i++)
		v.push_back(i);
	debug(v);
	v.erase(v.begin() + 3, v.begin() + 7);
	debug(v);
	v.erase(v.begin() + 2);
	debug(v);
}

void test_operator() {
	ft::vector<std::string> v1(10, "salut");
	ft::vector<std::string> v2(10, "salut");

	v2[4] = "coucou";

	std::cout << (v1 == v2) << ", ";
	std::cout << (v1 != v2) << ", ";
	std::cout << (v1 < v2) << ", ";
	std::cout << (v1 > v2) << ", ";
	std::cout << (v1 <= v2) << ", ";
	std::cout << (v1 >= v2) << std::endl;

	std::cout << (v1 == v1) << ", ";
	std::cout << (v1 != v1) << ", ";
	std::cout << (v1 < v1) << ", ";
	std::cout << (v1 > v1) << ", ";
	std::cout << (v1 <= v1) << ", ";
	std::cout << (v1 >= v1) << std::endl;
}

int 	main() {

	test_push_back();
	test_reserve();
	test_resize();
	test_pop_back();
	test_swap();
	test_assign();
	test_insert();
	test_iterator();
	test_erase();
	test_operator();
	test_maz_insert();
}