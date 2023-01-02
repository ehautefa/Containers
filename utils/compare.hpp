/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehautefa <ehautefa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:49:23 by ehautefa          #+#    #+#             */
/*   Updated: 2022/01/26 15:55:58 by ehautefa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARE_HPP
#define COMPARE_HPP

#include <iostream>

namespace ft
{
	/*******************/
	/*** LEXICO COMP ***/
	/*******************/

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		try
		{
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1)
					return false;
				else if (*first1 < *first2)
					return true;
				++first1;
				++first2;
			}
		}
		catch (const std::exception &e)
		{
			throw e;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		try
		{
			while (first1 != last1)
			{
				if (first2 == last2 || comp(*first2, *first1))
					return false;
				else if (comp(*first1, *first2))
					return true;
				++first1;
				++first2;
			}
		}
		catch (const std::exception &e)
		{
			throw e;
		}
		return (first2 != last2);
	}

	/*******************/
	/*****  EQUAL  *****/
	/*******************/

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		try
		{
			while (first1 != last1)
			{
				if (!(*first1 == *first2))
					return false;
				++first1;
				++first2;
			}
		}
		catch (const std::exception &e)
		{
			throw e;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		try
		{
			while (first1 != last1)
			{
				if (!pred(*first1, *first2))
					return false;
				++first1;
				++first2;
			}
		}
		catch (const std::exception &e)
		{
			throw e;
		}
		return true;
	}
}

#endif