/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:52:39 by ehautefa          #+#    #+#             */
/*   Updated: 2022/01/25 15:57:39 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
	class iterator {
		public:
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;

			/*******************	Function	*******************/

			template <class InputIterator, class Distance>
				void advance (InputIterator& it, Distance n);
			template <class Container>
				back_insert_iterator<Container> back_inserter (Container& x);
			template<class InputIterator>
				typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last);
			template <class Container>
				front_insert_iterator<Container> front_inserter (Container& x);
			template <class Container, class Iterator>
				insert_iterator<Container> inserter (Container& x, Iterator it);

			/*******************	Operator	*******************/

			template <class RandomIterator>
				bool operator!=(const reverse_iterator<RandomIterator>& left, const reverse_iterator<RandomIterator>& right);

			template <class Type, class CharType, class Traits, class Distance>
				bool operator!=(const istream_iterator<Type, CharType, Traits, Distance>& left, const istream_iterator<Type, CharType, Traits, Distance>& right);

			template <class CharType, class Tr>
				bool operator!=(const istreambuf_iterator<CharType, Traits>& left, const istreambuf_iterator<CharType, Traits>& right);


		
	};
	
}

