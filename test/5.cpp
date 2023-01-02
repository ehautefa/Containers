/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:57:17 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/10 11:40:10 by ehautefa         ###   ########.fr       */
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
	#include "../stack.hpp"
#endif

void	debug(ft::stack<int, ft::vector<int> > &stk) {
	std::cout << "SIZE " << stk.size() << std::endl;
	if (!stk.empty())
		std::cout << "TOP " << stk.top() << std::endl;
	std::cout << "EMPTY " << stk.empty() << std::endl;
}

int		main() {
	ft::vector<int>	vec(18, 42);
	
	ft::stack<int, ft::vector<int> >		stk1(vec);
	ft::stack<int, ft::vector<int> >		stk2;
	(void)stk2;

	debug(stk1); debug(stk2);

	for (size_t i = 0; i < 7; i++)
		stk2.push(i + 14);

	stk1.pop();

	debug(stk1); debug(stk2);

	std::cout << ( stk1 == stk2 ) << std::endl;
	std::cout << ( stk1 != stk2 ) << std::endl;
	std::cout << ( stk1 <  stk2 ) << std::endl;
	std::cout << ( stk1 <= stk2 ) << std::endl;
	std::cout << ( stk1 >  stk2 ) << std::endl;
	std::cout << ( stk1 >= stk2 ) << std::endl;

	stk2 = stk1;

	std::cout << ( stk1 == stk2 ) << std::endl;
	std::cout << ( stk1 != stk2 ) << std::endl;
	std::cout << ( stk1 <  stk2 ) << std::endl;
	std::cout << ( stk1 <= stk2 ) << std::endl;
	std::cout << ( stk1 >  stk2 ) << std::endl;
	std::cout << ( stk1 >= stk2 ) << std::endl;
}