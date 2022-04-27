/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:11:54 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/27 20:26:52 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"
#include "map.hpp"

template<typename Key, typename T>
void	printer(ft::map<Key, T> mapped, std::string target) {
	std::cout << target << ": "<< "[ ";
	for (typename ft::map<Key, T>::iterator it = mapped.begin(); it != mapped.end(); ++it)
		std::cout << it->first << "-" << it->second << "  ";
	std::cout << "]" << std::endl;
}
//	Those are related to the Example in CPP reference of constructor
bool	fncomp(char lhs, char rhs) { return (lhs < rhs); }
struct	classcomp {
	bool operator() (const char& lhs, const char& rhs) const { return (lhs < rhs); }
};

void	member_functions(void) {
	std::cout << "[-------------------- Member Functions tests --------------------]" << std::endl;
	std::cout << "[ Constructors and Destructor ]" << std::endl;
	std::cout << "Format: (Key - Value)." << std::endl;
	std::cout << "Default construction of m1 (just a NULL container, than populate)." << std::endl;
	ft::map<char, int>	m1;
	m1['a']=10;
	m1['b']=20;
	m1['c']=30;
	m1['d']=42;
	printer(m1, "m1");
	std::cout << "Copy construction of m2 as copy of m1." << std::endl;
	ft::map<char, int>	m2(m1);
	printer(m2, "m2");
	std::cout << "Range construction of m3 with entire m2." << std::endl;
	ft::map<char, int>	m3(m2.begin(), m2.end());
	printer(m3, "m3");
	std::cout << "Construction of m4 with Class as compare." << std::endl;
	ft::map<char, int, classcomp>	m4;
	m4['a']=10;
	m4['b']=20;
	m4['c']=30;
	m4['d']=42;
	// printer(m4, "m4");
	bool(*fn_pt)(char,char) = fncomp;
	std::map<char,int,bool(*)(char,char)> m5 (fn_pt);
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	element_access(void) {
	std::cout << "[-------------------- Element Access tests --------------------]" << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	interators(void) {
	std::cout << "[-------------------- Iterators tests --------------------]" << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	capacity(void) {
	std::cout << "[-------------------- Capacity tests --------------------]" << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	modifier(void) {
	std::cout << "[-------------------- Modifier tests --------------------]" << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	lookup(void) {
	std::cout << "[-------------------- Lookup tests --------------------]" << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	observer(void) {
	std::cout << "[-------------------- Observer tests --------------------]" << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	non_member(void) {
	std::cout << "[-------------------- Non Member Function tests --------------------]" << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	map_tests(void) {
	member_functions();
	element_access();
	interators();
	capacity();
	modifier();
	lookup();
	non_member();
	return ;
}

void	map_exceptions(void) {
	return ;
}