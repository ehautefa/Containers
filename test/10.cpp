#include <iostream>
#include <string>
#include <deque>
#include <iomanip>
#include <cstdio>

#if STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "../map.hpp"
#endif

struct ft_more {
	bool	operator()(const int &first, const int &second) const {
		return (first > second);
	}
};

int		main(void)
{
	ft::map<int, std::string, ft_more> mp;

	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	ft::map<int, std::string, ft_more>::iterator it = mp.begin();
	ft::map<int, std::string, ft_more>::iterator ite = mp.end();
	for (; it != ite; it++)
		std::cout << it->first << " | " << it->second << std::endl;

	return (0);
}