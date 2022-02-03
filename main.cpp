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

void test_constructor() {
	ft::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

  	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
	std::cout << ' ' << *it;
 	std::cout << '\n';

}

void	test_reverse_iterator() {
	ft::vector<int> myvector (5);  // 5 default-constructed ints

  int i=0;

  ft::vector<int>::reverse_iterator rit = myvector.rbegin();
  for (; rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void	ft_test_iterator() {
	test_constructor();
}

int	main() {
	ft_test_iterator();
}
