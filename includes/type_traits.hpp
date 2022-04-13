/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 02:39:20 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/12 19:47:45 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

/*-----[ Type_Traits ]-----*/
//	This header defines a series of classes to obtain type information on compile-time.
//	In this case, I am implementing just the type-generator - enable_if and the Primary Type Category - is_integral
//	https://www.cplusplus.com/reference/type_traits/
namespace ft {
	/*-----[ Enable_if Structs ]-----*/
	//	Trait class that identifies whether T is an integral type.
	//	-> "T" is a type of the integral constant and "v" is a value of the integral constant.
	//	obs: enum is not integral_type
	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		operator T() { return (v); }
	};
	//	Check if "T" is an Integral Type, as listed below \/
	template<class T> struct is_integral: public integral_constant<bool, false> {};
	template<> struct is_integral<bool>: public integral_constant<bool, true> {};
	template<> struct is_integral<char>: public integral_constant<bool, true> {};
	template<> struct is_integral<wchar_t>: public integral_constant<bool, true> {};
	template<> struct is_integral<signed char>: public integral_constant<bool, true> {};
	template<> struct is_integral<short int>: public integral_constant<bool, true> {};
	template<> struct is_integral<int>: public integral_constant<bool, true> {};
	template<> struct is_integral<long int>: public integral_constant<bool, true> {};
	template<> struct is_integral<long long int>: public integral_constant<bool, true> {};
	template<> struct is_integral<unsigned char>: public integral_constant<bool, true> {};
	template<> struct is_integral<unsigned short int>: public integral_constant<bool, true> {};
	template<> struct is_integral<unsigned int>: public integral_constant<bool, true> {};
	template<> struct is_integral<unsigned long int>: public integral_constant<bool, true> {};
	template<> struct is_integral<unsigned long long int>: public integral_constant<bool, true> {};

	/*-----[ Enable_if Structs ]-----*/
	//	The type T is enabled as member type enable_if::type if B is true. Otherwise, it is not defined.
	//	For conditionally removing functions from the candidate set based on type traits,
	//	allowing separate function overloads or specializations based on those different type traits.
	//	-> "B" is a condition to be used as parameter to enable.
	//	https://en.cppreference.com/w/cpp/language/sfinae
	template< bool B, class T = void >
	struct	enable_if {};
	//	The type will be defined IF the parameter is equal the "T" type.
	template<class T>
	struct	enable_if<true, T> { typedef T type; };
}

#endif
