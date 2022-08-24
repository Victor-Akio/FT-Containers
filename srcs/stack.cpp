/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:20:09 by vminomiy          #+#    #+#             */
/*   Updated: 2022/08/24 01:51:03 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"

#if STD == 1
	#include <stack>
	namespace ft = std;
#else
	#include "stack.hpp"
#endif

template<typename T>
static void		printer(ft::stack<T> stk) {
	std::cout << "The stack top element is: " << stk.top() << ".\n";
	std::cout << "The Current Size of the stack is: " << stk.size() << "." << std::endl;
}

void	stack_tests(void) {
	std::cout << "[-------------------- Member Functions tests --------------------]" << std::endl;
	std::cout << "[ Constructors and Destructor ]" << std::endl;
	std::cout << "Default construction of stk (just a NULL container, than populate)." << std::endl;
	ft::stack<int>	stk;
	std::cout << "[ Push ]" << std::endl;
	std::cout << "Let's insert several numbers to our stack." << std::endl;
	for (size_t i = 0; i < 10; i++)
		stk.push(i);
	std::cout << "[ Top and Size ]" << std::endl;
	std::cout << "Keep in mind that we can consult the 'Top' element of the stack and it's size." << std::endl;
	printer(stk);
	std::cout << "[ Copy Constructor ]" << std::endl;
	std::cout << "We might initialize one Stack with the contents of another." << std::endl;
	ft::stack<int>	stker(stk);
	printer(stker);
	std::cout << "[ Pop ]" << std::endl;
	std::cout << "Let's pop some elements and print the Top and it's size." << std::endl;
	for (size_t i = (stk.size() - 1); i > 0; i--) {
		stk.pop();
		printer(stk);
		std::cout << "****************************" << std::endl;
	}
	std::cout << "[ Empty ]" << std::endl;
	std::cout << "With just one element, the container should not be EMPTY: ";
	std::cout << (stk.empty() ? "Empty." : "Not Empty.") << std::endl;
	std::cout << "Poping the last one, it will be EMPTY: ";
	stk.pop();
	std::cout << (stk.empty() ? "Empty." : "Not Empty.") << std::endl;
	std::cout << std::endl;
	std::cout << "[ Non-Member Functions ]" << std::endl;
	std::cout << "Generate 2 diferent containers." << std::endl;
	ft::stack<int>	stkb;
	for (size_t i = 0; i < 10; i++)
		stkb.push(i);
	ft::stack<int>	comp;
	for (size_t i = 10; i > 0; i--)
		comp.push(i);
	std::cout << "Stack Base:" << std::endl;
	printer(stkb);
	std::cout << "Stack Comp:" << std::endl;
	printer(comp);
	std::cout << "[ stkb &  comp ] -" << "LET'S TEST'EM!" << std::endl;
	std::cout << "[ stkb == comp ] -" << ((stkb==comp) ? "Equals!\n" : "Different!\n");
	std::cout << "[ stkb != comp ] -" << ((stkb!=comp) ? "Not the same\n" : "WRONG, the same!\n");
	std::cout << "[ stkb <  comp ] -" << ((stkb<comp) ? "stkb is Smaller!\n" : "comp is Smaller!\n");
	std::cout << "[ stkb >  comp ] -" << ((stkb>comp) ? "stkb is Greater!\n" : "comp is Greater!\n");
	std::cout << "[ stkb <= comp ] -" << ((stkb<=comp) ? "stkb is Smaller or equal!\n" : "comp is Smaller or equal!\n");
	std::cout << "[ stkb >= comp ] -" << ((stkb>=comp) ? "stkb is Greater or equal!\n" : "comp is Greater or equal!\n");
	std::cout << "[ stkb == stker ] -" << ((stkb==stker) ? "Equals!\n" : "Different!\n");
	std::cout << std::endl;
	std::cout << "[---------------------------------------------------------------------------------------------------------------]" << std::endl;
}