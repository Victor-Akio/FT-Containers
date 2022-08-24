/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:42:56 by vminomiy          #+#    #+#             */
/*   Updated: 2022/08/24 01:51:00 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"

#if STD == 1
	#include <vector>
	namespace ft = std;
#else
	#include "vector.hpp"
#endif

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
		std::cout << "After instantiating a array container for debs, we access through its data...." << std::endl;

		std::cout << "Than printing every element of data, within debs:" << std::endl;
		std::cout << "debs = ";
		for (std::size_t i = 0; i < array.size(); ++i)
			std::cout << p[i] << ' ';
		std::cout << '\n';
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	std::cout << "[-------------------- Iterators tests --------------------]" << std::endl;
	{
		std::cout << "[ Begin and End iterators ]" << std::endl;
		std::cout << "As for the begin and end iterator functions:" << std::endl;
		ft::vector<char>	let(10);
		ft::vector<char>::reverse_iterator		rit = let.rbegin();
		for (int	i = 64; rit != let.rend(); rit++) {
			*rit = ++i;
		}
		std::cout << "After reverse iterating the letter.. we will print the range with iterator" << std::endl;
		printer(let, "letter");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	std::cout << "[-------------------- Capacity tests --------------------]" << std::endl;
	{
		std::cout << "[ Empty ]" << std::endl;
		std::cout << "Just create a emp vector." << std::endl;
		ft::vector<int>		emp;

		std::string		is_empty = emp.empty() ? "empty" : "Has elements";
		std::cout << "The Emp container shall be empty. Status: " << is_empty << std::endl;
		printer(emp, "emp");
		std::cout << "Setting 42 in emp, will change things" << std::endl;
		emp.push_back(42);
		is_empty = emp.empty() ? "empty" : "Has elements";
		std::cout << "The Emp container shall have some value. Status: " << is_empty << std::endl;
		printer(emp, "emp");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Size and Max_Size ]" << std::endl;
		ft::vector<int>		gariadno(162, 174);

		std::cout << "After generating gariadno, his size is suposed to be 162: Size = " << gariadno.size() << std::endl;
		std::cout << "Although, the max_size possible for this container is: " << gariadno.max_size() << std::endl;
		std::cout << "This occurs, because it is related to the ammount of RAM available." << std::endl;
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Reserve and Capacity ]" << std::endl;
		ft::vector<int>		cap;
		ft::vector<int>		res;

		
		for (int i = 0; i < 10; i++)
			cap.push_back(i);
		printer(cap, "Capacity");
		std::cout << "The Cap Capacity is: " << cap.capacity() << std::endl;

		std::cout << "In the second case, we are reserving storage space for res as 42" << std::endl;
		res.reserve(42);
		for (int i = 0; i < 10; i++)
			res.push_back(i);
		printer(res, "Reserve");
		std::cout << "The res Capacity is: " << res.capacity() << std::endl;
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	std::cout << "[-------------------- Modifiers tests --------------------]" << std::endl;
	{
		std::cout << "[ Clear ]" << std::endl;
		std::cout << "Clear is suposed to destroy the elements within the container.. \nGenerate a Container" << std::endl;

		ft::vector<int>		lenzo;
		for (int i = 0; i < 10; i++)
			lenzo.push_back(i);
		printer(lenzo, "lenzo");
		std::cout << "Than Clear everything!" << std::endl;
		lenzo.clear();
		printer(lenzo, "lenzo");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Insert and Erase ]" << std::endl;
		ft::vector<int>				tbi(4, 42);
		ft::vector<int>				paulino;
		ft::vector<int>::iterator	it;

		std::cout << "After creating paulino container. ";
		printer(paulino, "paulino");
		std::cout << "We will insert 42 in the first place" << std::endl;
		it = paulino.begin();
		it = paulino.insert(it, 42);
		printer(paulino, "paulino");
		std::cout << "Now, let's add 10 copies of 42 in the next spaces" << std::endl;
		paulino.insert(it, 10, 42);
		printer(paulino, "paulino");
		std::cout << "For Educational purpose, we might want to erase one of the eleven 42s, 10 sounds better..." << std::endl;
		paulino.erase(paulino.begin());
		printer(paulino, "paulino");
		std::cout << "OR!! None 42 should pass! erasing all the range of elements" << std::endl;
		paulino.erase(paulino.begin(), paulino.end());
		printer(paulino, "paulino");
		std::cout << "Finaly, an empty container is not fun... we will ser tbi to paulino" << std::endl;
		it = paulino.begin();
		paulino.insert(it, tbi.begin(), tbi.end());
		printer(paulino, "paulino");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Push_Back and Pop_Back ]" << std::endl;
		std::cout << "In the begining, there was nothing!" << std::endl;
		ft::vector<int>		ecole;

		printer(ecole, "42");
		std::cout << "Lets push/count to 10 in the container!" << std::endl;
		for (int i = 1; i <= 10; ++i)
			ecole.push_back(i);
		printer(ecole, "42");
		std::cout << "Than... let's pop some elements... 5 times?" << std::endl;
		for (int i = 0; i < 5; ++i)
			ecole.pop_back();
		printer(ecole, "42");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Resize ]" << std::endl;
		std::cout << "First, let's create a container with size 10." << std::endl;
		ft::vector<int>		alice(10, 42);
		printer(alice, "Alice in Wonderlands");

		std::cout << "Shink the container to size 2." << std::endl;
		alice.resize(2);
		printer(alice, "Alice in Wonderlands");
		std::cout << "Than, Grow back, but somethign is weird? what about the zeros?!" << std::endl;
		alice.resize(10);
		printer(alice, "Alice in Wonderlands");
		std::cout << "Shink back to 2." << std::endl;
		alice.resize(2);
		printer(alice, "Alice in Wonderlands");
		std::cout << "Than, Grow back again with the same size and quality!" << std::endl;
		alice.resize(10, 42);
		printer(alice, "Alice in Wonderlands");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Swap ]" << std::endl;
		ft::vector<int>		lenzo(10, 6);
		ft::vector<int>		gustavo(5, 9);

		printer(lenzo, "lenzo");
		printer(gustavo, "gustavo");
		std::cout << "Lenzo e Gustavo were created, let's swap tham.." << std::endl;
		lenzo.swap(gustavo);
		printer(lenzo, "lenzo");
		printer(gustavo, "gustavo");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	std::cout << "[-------------------- Nom-Member Function tests --------------------]" << std::endl;
	{
		std::cout << "[ Comparison operators ]" << std::endl;
		std::cout << "Generate 2 diferent containers." << std::endl;
		ft::vector<char>	adrian(3, 'a');
		ft::vector<char>	caio(2, 'c');

		printer(adrian, "adrian");
		printer(caio, "caio");
		std::cout << "[ adrian &  caio ] " << "LET'S TEST'EM!" << std::endl;
		std::cout << "[ adrian == caio ] " << ((adrian==caio) ? "Equals!\n" : "Different!\n");
		std::cout << "[ adrian != caio ] " << ((adrian!=caio) ? "Not the same\n" : "WRONG, the same!\n");
		std::cout << "[ adrian <  caio ] " << ((adrian<caio) ? "Adrian is Smaller!\n" : "Caio is Smaller!\n");
		std::cout << "[ adrian >  caio ] " << ((adrian>caio) ? "Adrian is Greater!\n" : "Caio is Greater!\n");
		std::cout << "[ adrian <= caio ] " << ((adrian<=caio) ? "Adrian is Smaller or equal!\n" : "Caio is Smaller or equal!\n");
		std::cout << "[ adrian >= caio ] " << ((adrian>=caio) ? "Adrian is Greater or equal!\n" : "Caio is Greater or equal!\n");
		std::cout << std::endl;
		std::cout << "Now! lets try with the same as adrian, to do one more test!" << std::endl;
		ft::vector<char>	stalone(3, 'a');

		printer(adrian, "adrian");
		printer(stalone, "SIlvestrE Stalones");
		std::cout << "[ adrian == Silvester Stalone ] " << ((adrian==stalone) ? "are THE SAME!\n" : "Different!\n");
		std::cout << "[ adrian != Silvester Stalone ] " << ((adrian!=stalone) ? "are not the same\n" : "WRONG, the same person!\n");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
	{
		std::cout << "[ Swap ]" << std::endl;
		std::cout << "Now, outside the container!" << std::endl;
		ft::vector<int>		lenzo(10, 6);
		ft::vector<int>		gustavo(5, 9);

		printer(lenzo, "lenzo");
		printer(gustavo, "gustavo");
		std::cout << "Lenzo e Gustavo were created, let's swap tham.." << std::endl;
		ft::swap(lenzo, gustavo);
		printer(lenzo, "lenzo");
		printer(gustavo, "gustavo");
	}
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}
