/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 00:58:18 by vminomiy          #+#    #+#             */
/*   Updated: 2022/06/01 01:06:43 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.hpp"
#include "vector.hpp"
#include "algorithm.hpp"

namespace ft {
	template< class T, class Container = ft::vector<T> >
	class stack {
		public:
			/*-----[ Member Types ]-----*/
			typedef	T											value_type;
			typedef Container									container_type;
			typedef typename container_type::size_type			size_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Functions ]-----*/
			//	Default constructor. Value-initializes the container.
			explicit stack( const container_type& cont = container_type() ): c(cont) {}
			//	Copy constructor with the contents of other.c.
			stack( const stack& other ) { *this = other; }
			stack& operator=( const stack& other ) {
				this->c = other.c;
				return (*this);
			}
			//	Default Destructor
			~stack(void) {}
			// /*-----------------------------------------------------------------------------------------------------------------------------*/
			// /*-----[ Element Access Functions ]-----*/
			//	Returns reference to the top element in the stack
			reference top(void) { return (c.back()); }
			const_reference top(void) const { return (c.back()); }
			// /*-----------------------------------------------------------------------------------------------------------------------------*/
			// /*-----[ Capacity Functions ]-----*/
			//	Verify if the container is empty
			bool empty(void) const { return (c.empty()); }
			//	Getter for the size of the stack
			size_type size(void) const { return (c.size()); }
			// /*-----------------------------------------------------------------------------------------------------------------------------*/
			// /*-----[ Modifiers Functions ]-----*/
			//	Insert a 'value' to the top of the stack
			void push( const value_type& value ) { c.push_back(value); }
			//	Remove the element on the Top of the stack
			void pop(void) { c.pop_back(); }
			/*-----------------------------------------------------------------------------------------------------------------------------*/
		protected:
			/*-----[ Member Objects Functions ]-----*/
			//	Basicaly, the Underlyng container.
			container_type		c;
		private:
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			//	To access the 'c' container, we need to use friend to have the Non-Member Function access the private 'c'
			template< class Type, class Cont >
			friend bool operator==( const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs );
			template< class Type, class Cont >
			friend bool operator!=( const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs );
			template< class Type, class Cont >
			friend bool operator<( const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs );
			template< class Type, class Cont >
			friend bool operator<=( const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs );
			template< class Type, class Cont >
			friend bool operator>( const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs );
			template< class Type, class Cont >
			friend bool operator>=( const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs );
	};
	/*-----------------------------------------------------------------------------------------------------------------------------*/
	/*-----[ Non-Member Functions ]-----*/
	template< class T, class Container >
	bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c == rhs.c); }
	template< class T, class Container >
	bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c != rhs.c); }
	template< class T, class Container >
	bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c < rhs.c); }
	template< class T, class Container >
	bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c <= rhs.c); }
	template< class T, class Container >
	bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c > rhs.c); }
	template< class T, class Container >
	bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return (lhs.c >= rhs.c); }
	/*-----------------------------------------------------------------------------------------------------------------------------*/
}