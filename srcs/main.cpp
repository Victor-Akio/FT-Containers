/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 01:17:38 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/09 02:36:36 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"
#include <iostream>

int main () {
  ft::vector<int> myvector;
  for (int i = 0; i < 10; i++) myvector.push_back(i);

  typedef ft::vector<int>::iterator iter_type;
                                                         // ? 9 8 7 6 5 4 3 2 1 0 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());         
//   std::cout << "myvector:";
//   while (from != until)
//     std::cout << ' ' << *from++;
//   std::cout << '\n';
//                                                          //
  ft::reverse_iterator<iter_type> rev_until (from);     // ^
                                                         //         <------
  ft::reverse_iterator<iter_type> rev_from (until);     //                     ^

  std::cout << "myvector:";
  while (rev_from != rev_until)
    std::cout << ' ' << *rev_from++;
  std::cout << '\n';

  return 0;
}