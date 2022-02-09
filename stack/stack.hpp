/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:34:53 by ehautefa          #+#    #+#             */
/*   Updated: 2022/02/09 17:30:17 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace	ft {
	template <class T, class Container = vector<T> >
	class stack {

		public:
		typedef	typename Container::value_type			value_type;
		typedef	typename Container::size_type			size_type;
		typedef	Container								container_type;

		protected:
			Container	c;

		public:

		explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}
		stack( const stack& other ) : c(other.c) {}
		~stack() {}
		stack& operator=( const stack& other ) { c = other.c; return *this; }

		bool 				empty() const					{ return( c.empty() );}
		void 				pop() 							{ c.pop_back(); }
		void 				push (const value_type& val)	{ c.push_back(val); }
		size_type 			size() const 					{ return( c.size() ); }
		value_type& 		top() 							{ return( c.back() ); }
		const value_type&	top() const 					{ return( c.back() ); }

		bool operator== (const stack & rhs) { return(this->c == rhs.c); }
  		bool operator!= (const stack & rhs) { return(this->c != rhs.c); }
  		bool operator<  (const stack & rhs) { return(this->c <  rhs.c); }	
  		bool operator<= (const stack & rhs) { return(this->c <= rhs.c); }	
  		bool operator>  (const stack & rhs) { return(this->c >  rhs.c); }
  		bool operator>= (const stack & rhs) { return(this->c >= rhs.c); }
	};		
}

#endif