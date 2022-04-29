/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:11:54 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/29 02:34:26 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"
#include "map.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

template<typename Key, typename T>
void	printer(ft::map<Key, T> mapped, std::string target) {
	std::cout << target << ": [ ";
	for (typename ft::map<Key, T>::iterator it = mapped.begin(); it != mapped.end(); ++it)
		std::cout << it->first << "-" << it->second << "  ";
	std::cout << "]" << std::endl;
}

template<typename Key, typename T>
void	rprinter(ft::map<Key, T> mapped, std::string target) {
	std::cout << target << ": [ ";
	for (typename ft::map<Key, T>::reverse_iterator it = mapped.rbegin(); it != mapped.rend(); ++it)
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
	m4['b']=20;
	m4['a']=10;
	m4['d']=42;
	m4['c']=30;
	// printer(m4, "m4");
	// bool(*fn_pt)(char,char) = fncomp;
	// std::map<char,int,bool(*)(char,char)> m5(fn_pt);
	// printer(m5, "m5");
	std::cout << "Operator = overload of m6 receiving m1" << std::endl;
	ft::map<char, int>	m6 = m1;
	printer(m6, "m6");
	std::cout << "Destructor being called, there should not be any memory leak." << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	element_access(void) {
	std::cout << "[-------------------- Element Access tests --------------------]" << std::endl;
	std::cout << "[ at ]" << std::endl;
	std::cout << "[ Operator [] overload ]" << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	interators(void) {
	std::cout << "[-------------------- Iterators tests --------------------]" << std::endl;
	std::cout << "[ Begin and End or reverse ]" << std::endl;
	std::cout << "First of all, there shoud be a mapped list m1" << std::endl;
	ft::map<char, int>	m1;
	m1['a']=10;
	m1['b']=20;
	m1['c']=30;
	m1['d']=42;
	std::cout << "Using a iterator to access begin() and end(), than printing everything" << std::endl;
	printer(m1, "m1");
	std::cout << "There also, might be accessed though reverse iterator." << std::endl;
	rprinter(m1, "rm1");
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	capacity(void) {
	std::cout << "[-------------------- Capacity tests --------------------]" << std::endl;
	std::cout << "[ Empty ]" << std::endl;
	std::cout << "As always, there mus be an Empty map container m1" << std::endl;
	ft::map<char, int>	m1;
	std::cout << "If we execute \"empty\" function, there shoudl return [true]: ";
	std::cout << (m1.empty() ? "True" : "False") << std::endl;
	m1['a']=10;
	m1['b']=20;
	m1['c']=30;
	m1['d']=42;
	std::cout << "After insertin data, the return should bem [false]: ";
	std::cout << (m1.empty() ? "True" : "False") << std::endl;
	std::cout << "[ size and Max_size ]" << std::endl;
	printer(m1, "m1");
	std::cout << "After generating m1, his size is suposed to be 4: Size = " << m1.size() << std::endl;
	std::cout << "Although, the max_size possible for this container is: " << m1.max_size() << std::endl;
	std::cout << "This occurs, because it is related to the ammount of RAM available." << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	modifier(void) {
	std::cout << "[-------------------- Modifier tests --------------------]" << std::endl;
	std::cout << "[ Clear ]" << std::endl;
	ft::map<char, int>	m1;
	std::cout << "Create a m1, populate as before and then CLEAR!" << std::endl;
	m1['a']=10;
	m1['b']=20;
	m1['c']=30;
	m1['d']=42;
	printer(m1, "m1");
	m1.clear();
	printer(m1, "m1");
	std::cout << "[ Insert ]" << std::endl;
	std::cout << "Now that m1 is empty, lets insert some data." << std::endl;
	m1.insert(ft::pair<char, int>('a', 10));
	m1.insert(ft::pair<char, int>('b', 20));
	printer(m1, "m1");
	std::cout << "It might as well add a key with a hint." << std::endl;
	ft::map<char, int>::iterator	it = m1.begin();
	m1.insert(it, ft::pair<char, int>('c', 30));	// kind of optimization of insert
	printer(m1, "m1");
	std::cout << "This time, we shall insert all range of data of m1 to m2" << std::endl;
	ft::map<char, int>	m2;
	m2.insert(m1.begin(), m2.end());
	printer(m2, "m2");
	std::cout << "[ Erase ]" << std::endl;
	std::cout << "Instead of clearing everythign, you might want to erase a range of data of m2" << std::endl;
	m2.erase(m2.find('b'), m2.end());
	printer(m2, "m2");
	std::cout << "Let's erase data in a determined position of m2" << std::endl;
	m2.erase(m2.begin());
	printer(m2, "m2");
	std::cout << "Lastly, it might erase a data, based in the key 'b'." << std::endl;
	m1.erase('b');
	printer(m1, "m1");
	m2.erase('b');
	printer(m2, "m2");
	std::cout << "[ Swap ]" << std::endl;
	std::cout << "Let's exchange the contents of m1 and m2" << std::endl;
	m1.swap(m2);
	printer(m1, "m1");
	printer(m2, "m2");
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	lookup(void) {
	std::cout << "[-------------------- Lookup tests --------------------]" << std::endl;
	std::cout << "[ Count ]" << std::endl;
	
	std::cout << "[ Find ]" << std::endl;
	std::cout << "[ Equal Range ]" << std::endl;
	std::cout << "[ Upper and Lower bound]" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	observer(void) {
	std::cout << "[-------------------- Observer tests --------------------]" << std::endl;
	std::cout << "[ Key Compare and Value Compare ]" << std::endl;
	std::cout << "For this test, there should have one map container with some data m1" << std::endl;
	ft::map<char, int>	m1;
	m1['a']=10;
	m1['b']=20;
	m1['c']=30;
	m1['d']=42;
	printer(m1, "m1");
	std::cout << "When comparing the Values, it will use a element to set as base of comparison" << std::endl;
	ft::map<char,int>::key_compare	vcomp = m1.key_comp();
	char highest = m1.rbegin()->first;
	ft::map<char,int>::iterator it = m1.begin();
	std::cout << "m1:\n";
	while ( vcomp((*it).first, highest) ) {
		std::cout << "[" << it->first << "-" << it->second << " ] " << std::endl;
		it++;
	}
	std::cout << "When comparing the key, there will be set as base, a ft::pair" << std::endl;
	ft::pair<char, int>	high = *m1.rbegin();
	ft::map<char,int>::iterator iter = m1.begin();
	std::cout << "m1:\n";
	while ( m1.value_comp()(*iter, high) ) {
		std::cout << "[" << iter->first << "-" << iter->second << " ] " << std::endl;
		iter++;
	}
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
	observer();
	non_member();
	return ;
}

void	map_exceptions(void) {
	return ;
}