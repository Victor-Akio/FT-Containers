/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:27:35 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/29 01:45:23 by vminomiy         ###   ########.fr       */
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
# include "vector.hpp"

/*-----[ MAP ]-----*/
//	Map is a sorted associative container that contains key-value pairs with unique keys. 
//	-> Keys are sorted by using the comparison function Compare. 
//	https://en.cppreference.com/w/cpp/container/map
namespace ft {
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
	class map {
		public:
			/*-----[ Member Types ]-----*/
			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef ft::pair<const key_type, mapped_type>								value_type;
			typedef std::size_t															size_type;
			typedef ptrdiff_t															difference_type;
			typedef Compare																key_compare;
			typedef Alloc																allocator_type;
			typedef typename allocator_type::reference									reference;
			typedef typename allocator_type::const_reference							const_reference;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;
			typedef typename ft::bidirectional_iterator<value_type, Compare, Alloc>		iterator;
			typedef typename ft::bidirectional_iterator<value_type, Compare, Alloc>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;
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
					bool	operator()( const value_type &lhs, const value_type &rhs ) const { return (comp(lhs.first, rhs.first)); }
			};
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Functions ]-----*/
			//	Construct a empty container
			explicit	map( const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type() ): _comp(comp), _alloc(alloc), _size(0) {}
			//	Constructs the container with the contents of the range [first, last]. 
			//	If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
			template< class InputIt >
			map( InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type &alloc = allocator_type() ): _comp(comp), _alloc(alloc), _size(0) {
				_size = 0;
				for (; first != last; first++)
					insert(*first);
				_comp = comp;
				_alloc = alloc;
			}
			//	Copy Constructor
			map( const map &other ) {
				_size = 0;
				*this = other;
			}
			//	Operator Overload =
			map		&operator=( const map &other ) {
				clear();
				_avl.assign(other._avl.root);
				_size = other.size();
				return (*this);
			}
			//	Default Destructor
			~map(void) { clear(); }
			//	Getter for allocator
			allocator_type get_allocator() const { return (_alloc); }
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Element access ]-----*/
			//	Returns a reference to the mapped value of the element with key equivalent to key.
			//	If no such element exists, an exception is thrown.
			mapped_type	&at( const key_type &key ) {
				value_type	value = ft::make_pair<key_type const, mapped_type> (key, mapped_type());
				Node<value_type, Alloc>		*node = _avl.find(_avl.root, value);
				return (node ? node->data : throw (std::out_of_range("Out of Range")));
			}
			const mapped_type	&at( const key_type &key ) const {
				value_type	value = ft::make_pair<key_type const, mapped_type> (key, mapped_type());
				Node<value_type, Alloc>		*node = _avl.find(_avl.root, value);
				return (node ? node->data : throw (std::out_of_range("Out of Range")));
			}
			mapped_type	&operator[] ( const key_type &key ) {
				value_type	value = ft::make_pair<key_type const, mapped_type> (key, mapped_type());
				Node<value_type, Alloc>		*node = _avl.find(_avl.root, value);
				if (!node) {
					node = _avl.insert(value);
					_size++;
					return (_avl.find(_avl.root, value)->data->second);
				}
				return (node->data->second);
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Iterators ]-----*/
			//	Functions related to the capability to run through a conteiner.
			iterator begin(void) { return (iterator(_avl.Min(_avl.root) ? _avl.Min(_avl.root)->data : NULL, &_avl)); }
			const_iterator begin(void) const { return (const_iterator(_avl.Min(_avl.root) ? _avl.Min(_avl.root)->data : NULL, &_avl)); }
			iterator end(void) { return (iterator(NULL, &_avl)); }
			const_iterator end(void) const { return (const_iterator(NULL, &_avl)); }
			reverse_iterator rbegin(void) { return (reverse_iterator(end())); }
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
			reverse_iterator rend()  { return (reverse_iterator(begin())); }
			const_reverse_iterator rend() const  { return (const_reverse_iterator(begin())); }
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
			//	Functions responsible for modifying the container elements
			//	It will destroy each node of the container
			void clear(void) {
				_avl.PreOrder(_avl.root);
				_avl.root = NULL;
				_size = 0;
			}
			//	Insert a "value" to a node
			//	The first element of pair, refers to the new iterator being inserted, or the key of the element being accessed,
			//	While the second element of the pair, is true if it is a new element, or false, if it is a existing key
			pair<iterator, bool>		insert( const value_type &value ) {
				Node<value_type, Alloc>		*node = _avl.find(_avl.root, value);
				bool	second = false;
				if (!node) {
					node = _avl.insert(value);
					second = true;
					_size++;
				}
				return (ft::make_pair<iterator, bool> (iterator(node->data, &_avl), second));
			}
			//	Insert a "value" in the position (hint), althought it may not, so just point to the new inserted element
			iterator	insert( iterator hint, const value_type &value ) {
				(void)hint;
				return (insert(value).first);
			}
			//	Insert a range [first, last] os elements to the tree. no return was mentioned here.
			template< class InputIt >
			void	insert( InputIt first, InputIt last ) {
				while (first != last) {
					insert(*first);
					first++;
				}
			}
			//	Erase a determined element int eh position "pos"
			void	erase( iterator pos ) {
				_avl.del(*pos);
				_size--;
			}
			//	Erase a range [first, last] elements of the tree
			void	erase( iterator first, iterator last ) {
				ft::vector<key_type> keys;

				while (first != last)
				{
					keys.push_back(first->first);
					first++;
				}
				for(size_t i = 0; i < keys.size(); i++)
					erase(keys[i]);
			}
			//	Erase an Element of a "key"
			size_type	erase( const key_type &key ) {
				_size--;
				return (_avl.del(ft::make_pair(key, mapped_type())));
			}
			//	Exchange the contents of two Map containers (current one and "other")
			void	swap( map &other ) {
				map		tmp;
				tmp._avl = _avl;
				tmp._alloc = _alloc;
				tmp._size = _size;
				this->_avl = other._avl;
				this->_alloc = other._alloc;
				this->_size	= other._size;
				other._avl = tmp._avl;
				other._alloc = tmp._alloc;
				other._size = tmp._size;
				tmp._avl.root = NULL;
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Lookup ]-----*/
			//	Returns the number of elements with key "key".
			size_type	count( const key_type &key ) const {
				if (_avl.find(_avl.root, ft::make_pair(key, mapped_type())) != NULL)
					return (1);
				return (0);
			}
			//	Iterator to an element with key equivalent to "key".
			//	If no such element is found, NULL iterator is returned.
			iterator find( const key_type &key ) {
				Node<value_type, Alloc>		*node = _avl.find(_avl.root, ft::make_pair(key, mapped_type()));
				return (iterator(node ? node->data : NULL, &_avl));
			}
			//	same goes to Constant Iterator, although, it is a const
			const_iterator find( const key_type &key ) const {
				Node<value_type, Alloc>		*node = _avl.find(_avl.root, ft::make_pair(key, mapped_type()));
				return (const_iterator(node ? node->data : NULL, &_avl));
			}
			//	Compares the keys to "key".
			//	Returns a range containing all elements with the given "key" in the container.
			pair<iterator,iterator> equal_range( const key_type &key ) { return (ft::make_pair(lower_bound(key), upper_bound(key))); }
			pair<const_iterator,const_iterator> equal_range( const key_type &key ) const { return (ft::make_pair(lower_bound(key), upper_bound(key))); }
			//	Returns an iterator to the first element not less than the given "key".
			iterator lower_bound( const key_type &key ) {
				Node<value_type, Alloc>		*node = _avl.root;
				Node<value_type, Alloc>		*lower = node;

				while (node != NULL) {
					if (!_comp(node->data->first, key)) {
						lower = node;
						node = node->left;
					} else
						node = node->right;
				}
				return (iterator(lower ? lower->data : NULL, &_avl));
			}
			const_iterator lower_bound( const key_type &key ) const {
				Node<value_type, Alloc>		*node = _avl.root;
				Node<value_type, Alloc>		*lower = node;

				while (node != NULL) {
					if (!_comp(node->data->first, key)) {
						lower = node;
						node = node->left;
					} else
						node = node->right;
				}
				return (const_iterator(lower ? lower->data : NULL, &_avl));
			}
			//	Returns an iterator to the first element greater than the given "key"
			iterator upper_bound( const key_type &key ) {
				Node<value_type, Alloc>		*node = _avl.root;
				Node<value_type, Alloc>		*upper = node;

				while (node != NULL) {
					if (_comp(key, node->data->first)) {
						upper = node;
						node = node->left;
					} else
						node = node->right;
				}
				return (iterator(upper ? upper->data : NULL, &_avl));
			}
			const_iterator upper_bound( const key_type &key ) const {
				Node<value_type, Alloc>		*node = _avl.root;
				Node<value_type, Alloc>		*upper = node;

				while (node != NULL) {
					if (_comp(key, node->data->first)) {
						upper = node;
						node = node->left;
					} else
						node = node->right;
				}
				return (const_iterator(upper ? upper->data : NULL, &_avl));
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Observers ]-----*/
			//	Returns the function object that compares the keys, which is a copy of this container's constructor argument comp.
			//	Generaly, a getter.
			key_compare		key_comp(void) const { return (_comp); }
			//	Returns a function object that compares objects of type value_type by using "key_comp" to compare the first components of the pairs.
			value_compare	value_comp(void) const { return (value_compare(_comp)); }
			/*-----------------------------------------------------------------------------------------------------------------------------*/
		private:
			key_compare			_comp;
			allocator_type		_alloc;
			size_type			_size;
			AVL<value_type, key_compare, allocator_type>	_avl;
	};
	/*-----[ Non-member functions ]-----*/
	//	The following overloads correspond to the comparison overloads outside the vector container.
	template< class Key, class T, class Compare, class Alloc >
	bool	operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
	template< class Key, class T, class Compare, class Alloc >
	bool	operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (!(ft::equal(lhs.begin(), lhs.end(), rhs.begin()))); }
	template< class Key, class T, class Compare, class Alloc >
	bool	operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	template< class Key, class T, class Compare, class Alloc >
	bool	operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (lhs <= rhs ? true : false); }
	template< class Key, class T, class Compare, class Alloc >
	bool	operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }
	template< class Key, class T, class Compare, class Alloc >
	bool	operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) { return (lhs >= rhs ? true : false); }
	//	Swap the content of lhs and rhs
	template< class Key, class T, class Compare, class Alloc >
	void	swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs ) { lhs.swap(rhs); }
}

#endif
