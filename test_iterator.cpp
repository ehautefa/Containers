/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:27:50 by ehautefa          #+#    #+#             */
/*   Updated: 2022/01/25 15:29:24 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include <list>
#include <iostream>

int main( )
{
   int i;

   std::list<int> L;
   for ( i = 1 ; i < 9 ; ++i )
   {
      L.push_back ( i );
   }
   std::list<int>::iterator L_Iter, LPOS = L.begin ( );

   std::cout << "The list L is: ( ";
   for ( L_Iter = L.begin( ) ; L_Iter != L.end( ); L_Iter++)
      std::cout << *L_Iter << " ";
   std::cout << ")." << std::endl;

   std::cout << "The iterator LPOS initially points to the first element: "
        << *LPOS << "." << std::endl;

   advance ( LPOS , 4 );
   std::cout << "LPOS is advanced 4 steps forward to point"
        << " to the fifth element: "
        << *LPOS << "." << std::endl;

   advance ( LPOS , -3 );
   std::cout << "LPOS is moved 3 steps back to point to the "
        << "2nd element: " << *LPOS << "." << std::endl;
}
