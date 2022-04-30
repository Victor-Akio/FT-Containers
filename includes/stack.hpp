/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 00:58:18 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/30 02:29:38 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.hpp"
#include "vector.hpp"

namespace ft {
	template< class T, class Container = ft::vector<T> >
	class stack {
		public:
			/*-----[ Member Types ]-----*/
			typedef Container									container_type;
			typedef	T											value_type;
			typedef typename container_type::size_type			size_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Functions ]-----*/
			explicit stack( const container_type& cont = container_type() );
			stack( const stack& other );
			~stack();
			stack& operator=( const stack& other );
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Element Access Functions ]-----*/
			reference top();
			const_reference top() const;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Capacity Functions ]-----*/
			bool empty() const;
			size_type size() const;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Modifiers Functions ]-----*/
			void push( const value_type& value );
			void pop();
			/*-----------------------------------------------------------------------------------------------------------------------------*/
		private:
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Objects Functions ]-----*/
			container_type		c;
	};
	/*-----------------------------------------------------------------------------------------------------------------------------*/
	/*-----[ Non-Member Functions ]-----*/
	template< class T, class Container >
	bool operator==( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs );
	template< class T, class Container >
	bool operator!=( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs );
	template< class T, class Container >
	bool operator<( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs );
	template< class T, class Container >
	bool operator<=( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs );
	template< class T, class Container >
	bool operator>( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs );
	template< class T, class Container >
	bool operator>=( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs );
	/*-----------------------------------------------------------------------------------------------------------------------------*/
}
