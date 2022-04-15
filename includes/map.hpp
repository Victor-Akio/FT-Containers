/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:27:35 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/15 20:52:14 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "containers.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"
# include "utility.hpp"
# include "AVL.hpp"

/*-----[ MAP ]-----*/
//	Map is a sorted associative container that contains key-value pairs with unique keys. 
//	-> Keys are sorted by using the comparison function Compare. 
//	https://en.cppreference.com/w/cpp/container/map
namespace ft {
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> >
	class map {
		public:
			/*-----[ Member Types ]-----*/
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef std::size_t									size_type;
			typedef ptrdiff_t									difference_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			// typedef typename ft::bidirectional_iterator<>		iterator;
			// typedef typename ft::bidirectional_iterator<>		const_iterator;
			// typedef typename ft::reverse_iterator<iterator>		reverse_iterator;
			// typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Class ]-----*/
			class value_compare: public std::binary_function<value_type, value_type, bool> {
				//	A friend class can access private and protected members of other class in which it is declared as friend.
				friend class map;
				protected:
					Compare comp;
					value_compare( Compare c ): comp(c) {}
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator()( const value_type& lhs, const value_type& rhs ) const { return (comp(lhs.first, rhs.first)); }

			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Functions ]-----*/
			//	Construct a empty container
			map(void): _comp(NULL), _alloc(NULL), _size(0) {}
			explicit	map( const Compare& comp, const Allocator& alloc = Allocator() ): _comp(comp), _alloc(alloc), _size(0) {}
			//	Constructs the container with the contents of the range [first, last]. 
			//	If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ): _comp(comp), _alloc(alloc) {
				_size = 0;
				for (; first != last, first++)
					//insert->first;
			}
			//	Copy Constructor
			map( const map& other ) {
				_size = 0;
				*this = other;
			}
			//	Operator Overload =
			map& operator=( const map& other ) {}
			//	Default Destructor
			~map(void) { /*clear*/ }
			//	Getter for allocator
			allocator_type get_allocator() const { return (_alloc); }
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Element access ]-----*/
			// T& at( const Key& key );
			// const T& at( const Key& key ) const;
			// T& operator[]( const Key& key );
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Iterators ]-----*/
			// iterator begin();
			// const_iterator begin() const;
			// iterator end();
			// const_iterator end() const;
			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Capacity ]-----*/
			//	Functions related to the capacity management of elements in a Container.
			//	Check if the container is empty
			bool		empty(void) const { return (_size == 0 ? true : false); }
			//	Return the container size;
			size_type	size(void) const { return (_size); }
			//	Return the maximun size of the container
			size_type	max_size(void) const { return (_alloc.max_size()); }
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Modifiers ]-----*/
			// void clear();
			// std::pair<iterator, bool> insert( const value_type& value );
			// template< class InputIt >
			// void insert( InputIt first, InputIt last );
			// void erase( iterator pos );
			// void erase( iterator first, iterator last );
			// size_type erase( const Key& key );
			// void swap( map& other );
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Lookup ]-----*/
			// size_type count( const Key& key ) const;
			// iterator find( const Key& key );
			// const_iterator find( const Key& key ) const;
			// std::pair<iterator,iterator> equal_range( const Key& key );
			// std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
			// iterator lower_bound( const Key& key );
			// const_iterator lower_bound( const Key& key ) const;
			// iterator upper_bound( const Key& key );
			// const_iterator upper_bound( const Key& key ) const;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Observers ]-----*/
			// std::map::value_compare value_comp() const;
			// key_compare key_comp() const;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
		private:
			key_compare			_comp;
			allocator_type		_alloc;
			size_type			_size;
	}
	/*-----[ Non-member functions ]-----*/
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator==( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator!=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator<( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator<=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator>( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
	// template< class Key, class T, class Compare, class Alloc >
	// bool operator>=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
	// template< class Key, class T, class Compare, class Alloc >
	// /* see below */ operator<=>( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );

	// template< class Key, class T, class Compare, class Alloc >
	// void swap( std::map<Key,T,Compare,Alloc>& lhs, std::map<Key,T,Compare,Alloc>& rhs );
}

#endif
