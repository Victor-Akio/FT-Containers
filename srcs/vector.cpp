/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:42:56 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/13 03:19:18 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"
#include "vector.hpp"

// std::cout << "[  ]" << std::endl;

template <typename T>
void	printer(ft::vector<T> vec, std::string target) {
	std::cout << target << ": [";
	for (typename ft::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << " ]" << std::endl;
}

void	vector_tests(void) {
	std::cout << "[-------------------- Member Functions tests --------------------]" << std::endl;
	{
		std::cout << "[ Constructors and Destructor ]" << std::endl;
		std::cout << "Default construction of v1 (just a NULL container)." << std::endl;
		ft::vector<int>	v1;
		printer(v1, "v1");
		std::cout << "Initialized construction of v2 (just 10 elements 42)." << std::endl;
		ft::vector<int>	v2(10, 42);
		printer(v2, "v2");
		std::cout << "Copy of a Container v2 to v3 (same as v2)" << std::endl;
		ft::vector<int>	v3(v2);
		printer(v3, "v3");
		std::cout << "Copy through iterator v3 to v4 (same as v3)" << std::endl;
		ft::vector<int>	v4(v3.begin(), v3.end());
		printer(v4, "v4");
		std::cout << "Also, it is possible to create v5 with and array" << std::endl;
		char		charray[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
		ft::vector<char>	v5(charray, charray + sizeof(charray) / sizeof(char));
		printer(v5, "v5");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Operator Overload = ]" << std::endl;
		ft::vector<int>		gadino(2, 4);
		ft::vector<int>		lenzo(4, 2);

		std::cout << "In the begining, lenzo and gadino will be, respectively." << std::endl;
		printer(lenzo, "lenzo");
		printer(gadino, "garianders");
		lenzo = gadino;
		std::cout << "after the overload, Lenzo will change:\nlenzo " << std::endl;
		printer(lenzo, "lenzo");
		std::cout << "Although, gadino will still have the same elements:\ngadino " << std::endl;
		printer(gadino, "garianders");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Assign ]" << std::endl;
		std::cout << "Here we are testing both assign functions, with copies and with a range of numbers" << std::endl;
		ft::vector<std::string>		giyeo;
		ft::vector<std::string>		adrian;

		std::cout << "After creating a NULL pointer container, we assign serveral(8) \"vivo\", to giyeo container" << std::endl;
		giyeo.assign(8, "vivo");
		printer(giyeo, "giyeo");
		std::cout << "And for the second part, we are assigning giyeo's container to adrian container" <<std::endl;
		adrian.assign(giyeo.begin(), giyeo.end());
		printer(adrian, "adrian");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Get Allocator ]" << std::endl;
		ft::vector<int>	caiola;
		std::size_t			i;

		std::cout << "Generaly, you can access the allocator throught this function." << std::endl;
		std::cout << "You can use the allocator functions, as allocate, construct, destroy or deallocate." << std::endl;
		int *ptr = caiola.get_allocator().allocate(43);
		for (i = 0; i < 43; i++)
			caiola.get_allocator().construct(&ptr[i], i);
		std::cout << "After set the counter, the container should have something like:\ncaio: ";
		for (i = 0; i < 43; i++)
			std::cout << ptr[i] << " ";
		std::cout << std::endl;
		for (i = 0; i < 43; i++)
			caiola.get_allocator().destroy(&ptr[i]);
		caiola.get_allocator().deallocate(ptr, 43);
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	std::cout << "[-------------------- Element Access tests --------------------]" << std::endl;
	{
		std::cout << "[ at ]" << std::endl;
		ft::vector<int>		lucas(43);

		std::cout << "(at) can be used to access independently, the positions througth the container." << std::endl;
		for (unsigned i = 0; i < lucas.size(); i++)
			lucas.at(i) = i;
		std::cout << "In a loop, printing every element, we should have:\n[";
		for (unsigned i = 0; i < lucas.size(); i++)
			std::cout << " " << lucas.at(i);
		std::cout << " ]" << std::endl;
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Operator Overload [] ]" << std::endl;
		ft::vector<int>		colchetes(5);

		std::cout << "Using operator[] we are setting values to the container." << std::endl;
		for (unsigned i = 0; i < colchetes.size(); i++)
			colchetes[i] = i;
		std::cout << "In a loop, printing every element with operator[], we should have:\n[";
		for (unsigned i = 0; i < colchetes.size(); i++)
			std::cout << " " << colchetes[i];
		std::cout << " ]" << std::endl;
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Front and Back Access ]" << std::endl;
		char		charray[] = {'a', 'e', 'i', 'o', 'u'};
		ft::vector<char>	vogais(charray, charray + sizeof(charray) / sizeof(char));

		std::cout << "We Create a container of \"vogais\"." << std::endl;
		printer(vogais, "vogais");
		std::cout << "The first(front) one is \"" << vogais.front() << "\"" << std::endl;
		std::cout << "The last(back) one is \"" << vogais.back() << "\"" << std::endl;
		vogais.pop_back();
		std::cout << "After a Pop out, the last(back) one will be \"" << vogais.back() << "\"" << std::endl;
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Data Access ]" << std::endl;
		int					debs[] = {1, 2, 3, 4};
		ft::vector<int>		array(debs, debs + sizeof(debs) / sizeof(int));
		int					*p = array.data();
		std::cout << "After instantiating a array container for debs, we access through its data...."

		std::cout << "Than printing every element of data, within debs:"
		std::cout << "debs = ";
		for (std::size_t i = 0; i < array.size(); ++i)
			std::cout << p[i] << ' ';
		std::cout << '\n';
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	std::cout << "[-------------------- Iterators tests --------------------]" << std::endl;
	{
		std::cout << "[ Begin and End iterators ]" << std::endl;
		//	TODO AMANHA
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}

void	vector_exceptions(void) {
	{
		return ;
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}
