/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 02:26:28 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/13 23:30:31 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

/*-----[ STL - Algorithm ]-----*/
//	Algorithm defines a collection of functions especially designed to be used on ranges of elements.
//	In the template, It is being implemented the Non-modifying sequence operations - Equal and Lexicographical_compare operations.
//	Those will be used as support to comparison operations to the containers being implemented.
//	https://www.cplusplus.com/reference/algorithm/
namespace ft {
	/*-----[ Equal Elements comparison ]-----*/
	//	-> (first1, last1) are the input iterator to the first and last position of the source sequence.
	//	-> (first2, last2) are the input iterator to the first and last position of the compared sequence.
	//	Compares the elements of each ranges and return true if they are the same.
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return (false);
			++first1; ++first2;
		}
		return (true);
	}
	//	Same as above, plus an extra "pred" binary function, this can either be a function pointer or a function object.
	//	-> The "pred" returns a value convertible to bool.
	//	For example:
	//	bool mypredicate (int i, int j) { return (i==j); }
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		while (first1 != last1) {
			if (!pred(*first1, *first2))
				return (false);
			++first1; ++first2;
		}
		return (true);
	}
	/*-----[ LexoGraphical comparison ]-----*/
	//	-> (first1, last1) are the input iterator to the first and last position of the source sequence.
	//	-> (first2, last2) are the input iterator to the first and last position of the compared sequence.
	//	Compares the elements and if the first range are lexograficaly less than the second range,
	//	it returns "true".
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
	//	Same as above, with an extra "comp" binary function, this can either be a function pointer or a function object.
	//	-> The "comp" returnes whether the first argument is considered to go before the second in the specific "strict weak ordering" it defines.
	//	For example:
	//	bool mycomp (char c1, char c2) { return std::tolower(c1)<std::tolower(c2); }
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		while (first1 != last1) {
			if (!comp(*first1, *first2))
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
}

#endif
