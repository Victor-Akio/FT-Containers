/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 02:42:47 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/09 07:42:13 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP

/*-----[ Utility ]-----*/
//	This header contains utilities in unrelated domains.
//	In this case, objects that can hold two values of different types: pair, make_pair, piecewise_construct, piecewise_construct_t.
//	There is being implemented the pair and make_pair;
//	https://www.cplusplus.com/reference/utility/
namespace ft {
	/*-----[ Pair ]-----*/
	//	This class couples together a pair of values, which may be of different types (T1 and T2). 
	//	-> T1 is a type of member first, aliased as first_type.
	//	-> T2 is a type of member second, aliased as second_type.
	//	class pair, instead of just a struct.
	template <class T1, class T2>
	class pair {
		public:
			/*-----[ Member Types ]-----*/
			typedef T1		first_type;
			typedef T2		second_type;
			/*-----[ Member Variables ]-----*/
			T1 first;
			T2 second;
			/*-----[ Member Functions ]-----*/
			//	Constructs a pair object, as default constructor, copy constructor and initialization constructor.
			//	-> "pr" is another pais object;
			//	-> (a, b) refers to the first and second type, respectively.
			pair(void): first(first_type()), second(second_type()) {}
			template <class U, class V>
			pair( pair<U,V> const &pr): first(pr.first_type()), second(pr.second_type()) {}
			pair (first_type const &a, second_type const &b): first(a), second(b) {}
			pair	&operator= (pair const &pr) {
				first = pr.first;
				second = pr.second;
				return (*this);
			}
			// ~pair(void) {}				//There is no destructor in the manual
			/*-----[ Relational Operators ]-----*/
			//	There is the relational operators for comparison.
			template <class T1, class T2>
			bool operator== (const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; }

			template <class T1, class T2>
			bool operator!= (const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) { return !(lhs==rhs); }

			template <class T1, class T2>
			bool operator<  (const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

			template <class T1, class T2>
			bool operator<= (const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) { return !(rhs<lhs); }

			template <class T1, class T2>
			bool operator>  (const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) { return rhs<lhs; }

			template <class T1, class T2>
			bool operator>= (const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) { return !(lhs<rhs); }
	}

	/*-----[ Make_Pair ]-----*/
	//	Construct a pair object with the templates types.
	//	-> (x, y) are the values of the first and second, respectively.
	template < class T1,class T2 >
	pair<T1, T2>	make_pair(T1 x, T2 y) {
		return ( pair< T1, T2 >(x, y) );
	}
}

#endif
