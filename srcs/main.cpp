/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:17:38 by vminomiy          #+#    #+#             */
/*   Updated: 2022/08/24 02:21:19 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "containers.hpp"

void	invArg(void) {
	std::cout << "Please, use the following syntax: \"./containers <flag>\"" << std::endl;
	std::cout << "Container tests: " << std::endl;
	std::cout
			<< "-V -> refers to Vector tests;\n"
			<< "-M -> refers to Map tetsts;\n"
			<< "-S -> refers to Stack tests;\n";
}

int		switchCase(int i) {
	switch (i) {
		case 0:
		{
			std::cout << "[ Vector Successful Test Case ]" << std::endl;
			vector_tests();
			break ;
		}
		case 1:
		{
			std::cout << "[ Map Test Case ]" << std::endl;
			map_tests();
			break ;
		}
		case 2:
		{
			std::cout << "[ Stack Test Case ]" << std::endl;
			stack_tests();
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
	std::string	list[3] = {"-V", "-M", "-S"};
	
	while (i < 3 && list[i] != arg) i++;
	if (i > 3) {
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
