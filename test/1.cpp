#include <iostream>
#include <string>
#include <deque>

#if STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "../vector.hpp"
#endif

void	debug_main(ft::vector<int> & v)
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
	debug_main(myvector);
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
	debug_main(myvector);

}

void	test_erase() {
	ft::vector<int> myvector;

	for (int i=1; i<=10; i++) myvector.push_back(i);

	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	myvector.erase (myvector.begin()+5);

	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	myvector.erase (myvector.begin(),myvector.begin()+3);

	std::cout << "TEST ERASE: ";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void	test_const_it() {
	ft::vector<int>	myvec;
	for (size_t i = 0; i < 13; i++)
		myvec.push_back(i + 42);
	ft::vector<int>::const_iterator	it = myvec.begin();
	std::cout << "FIRST: " << *it << std::endl;
	for (; it != myvec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	ft::vector<int>::reverse_iterator	rit = myvec.rbegin();
	for (; rit != myvec.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl;
	ft::vector<int>::const_reverse_iterator test = myvec.rend();
	(void)test;
}

void	test_insert() {
  ft::vector<int> myvector (3,100);
  ft::vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  debug_main(myvector);

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();
  debug_main(myvector);

  ft::vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());
  debug_main(myvector);

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);
  debug_main(myvector);

}

void	ft_test_iterator() {
	test_constructor();
	test_rv_base();
	test_const_it();
	test_erase();
	test_insert();
	test_reverse_iterator();

}

int	main() {
	ft_test_iterator();
}
