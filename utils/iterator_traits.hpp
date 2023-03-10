/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:29:13 by ehautefa          #+#    #+#             */
/*   Updated: 2022/03/16 16:47:42 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>

namespace ft
{
	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag : public input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : public forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};

	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T *, typename Reference = T &>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T *, typename Reference = T &>
	struct const_iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template <class Iterator>
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T *>
	{
	public:
		typedef random_access_iterator_tag category;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
	};

	template <class T>
	class iterator_traits<const T *>
	{
	public:
		typedef random_access_iterator_tag category;
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
	};
}

#endif