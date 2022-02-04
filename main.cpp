#include <iostream>
#include <string>
#include <deque>

#if STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "vector/vector.hpp"
#endif

void	debug(ft::vector<int> & v)
{
	std::cout << "CAP: " << v.capacity() << " SIZE: " << v.size() << std::endl;
	for(size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

void test_constructor() {
	ft::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

  	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
	std::cout << ' ' << *it;
 	std::cout << '\n';

}

void	test_rv_base() {
	ft::vector<int>	vec;
	for (int i = 0; i < 42; i++)
		vec.push_back(i + 42);

	ft::vector<int>::reverse_iterator	rev_end(vec.begin());
	ft::vector<int>::reverse_iterator	rev_beg(vec.end());

	ft::vector<int>::iterator	it = rev_end.base();
	for (; it != rev_beg.base(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	test_reverse_iterator() {
	ft::vector<int> myvector (1, 42);
	for (size_t i = 0; i < 9; i++)
		myvector.push_back(i);

	ft::vector<int>::iterator ite = myvector.end();
	--ite;
	std::cout << *ite << std::endl;
	int i = 0;
  	ft::vector<int>::reverse_iterator rit(ite);
	std::cout << *rit << *ite << std::endl;
	ft::vector<int>::reverse_iterator rit_cpy(rit);
	ft::vector<int>::reverse_iterator rite = myvector.rend();
	debug(myvector);
  	for (; rit!= rite; ++rit)
  	  *rit = ++i;
	--rite;
	for (; rit_cpy != rite; --rite) {
		std::cout << *rite << " ";
	}
	std::cout << std::endl;
	rite = myvector.rend();
	rit = myvector.rbegin();
	std::cout << *rit << std::endl;
	rit++;
	std::cout << *rit << std::endl;
	for (; rit != rite; ++rit) {
		std::cout << *rit << " ";
	}
	std::cout << std::endl;
	debug(myvector);

  	std::cout << "myvector contains:";
  	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
  	  std::cout << ' ' << *it;
  	std::cout << '\n';
}

void	ft_test_iterator() {
	test_constructor();
	test_rv_base();
}

int	main() {
	ft_test_iterator();
	test_reverse_iterator();
}
