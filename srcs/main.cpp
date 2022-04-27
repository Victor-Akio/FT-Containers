/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:17:38 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/25 22:29:50 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"
#include <iostream>
#include <cstdlib>

void	invArg(void) {
	std::cout << "Please, use the following syntax: \"./containers <flag>\"" << std::endl;
	std::cout << "Container tests: " << std::endl;
	std::cout
			<< "-V -> refers to Vector tests;\n"
			<< "-M -> refers to Map tetsts;\n"
			<< "-S -> refers to Stack tests;\n"
			<< "-B -> refers to Bonus tests;\n";
}

int		switchCase(int i) {
	switch (i) {
		case 0:
		{
			std::cout << "[ Vector Successful Test Case ]" << std::endl;
			vector_tests();
			std::cout << "[ Vector Exceptions Test Case ]" << std::endl;
			vector_exceptions();
			break ;
		}
		case 1:
		{
			std::cout << "[ Map Successful Test Case ]" << std::endl;
			map_tests();
			std::cout << "[ Map Exceptions Test Case ]" << std::endl;
			map_exceptions();
			break ;
		}
		case 2:
		{
			break ;
		}
		case 3:
		{
			break ;
		}
		default:
		{
			std::cout << "Error - Invalid argument." << std::endl;
			invArg();
			return (1);
		}
	}
	return (0);
}

int		argParser(char *arg) {
	int i = 0;
	int	x = 4;
	std::string	list[x] = {"-V", "-M", "-S", "-B"};
	
	while (i < x && list[i] != arg) i++;
	if (i > x) {
		std::cout << "Error - Invalid argument." << std::endl;
		invArg();
		return (1);
	}
	switchCase(i);
	return (0);
}

int		main(int ac, char **av) {
	srand( (unsigned)time(NULL) );

	if (ac != 2) {
		std::cout << "Error - Wrong number of arguments." << std::endl;
		invArg();
		return (1);
	} else
		argParser(av[1]);
	return (0);
}
