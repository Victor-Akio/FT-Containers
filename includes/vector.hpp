/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:25:22 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/30 18:40:54 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>
# include "type_traits.hpp"
# include "utility.hpp"
# include "algorithm.hpp"
# include "iterator.hpp"

/*-----[ VECTOR ]-----*/
/*	Vector is a sequence container that encapsulates dynamic size arrays. It is not accessable through iterators,
**	also using offsets to regular pointers to elements.
**	-> "T" will recieve a type of array;
**	->	"Alloc" is used to acquire/release memory and to construct/destroy the elements in that memory
*/
namespace ft {
	template< class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			/*-----[ Member Types ]-----*/
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Functions ]-----*/
			//	Default Constructor with zero or null inicialization.
			vector(void): _size(0), _capacity(0), _ptr(NULL) {}
			//	Constructs an empty container with the given allocator alloc.
			explicit vector( const allocator_type& alloc ): _alloc(alloc), _size(0), _capacity(0), _ptr(NULL) {}
			//	Constructs the container with "count" copies of elements with "value"
			explicit vector( size_type count, const value_type &value = value_type(), const allocator_type& alloc = allocator_type()) {
				_size = count;
				_capacity = count;
				_alloc = alloc;
				_ptr = _alloc.allocate(count);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_ptr + i, value);
			}
			//	Constructs the container with the contents of the range [first, last].
			template< class InputIt >
			vector( InputIt first, InputIt last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt() ) {
				size_type	delta = (last - first);
				_ptr = _alloc.allocate(delta);
				for (size_type i = 0; i < delta; i++) {
					_alloc.construct(_ptr + i, *first);
					first++;
				}
				_size = delta;
				_capacity = delta;
				_alloc = alloc;
			}
			//  Copy constructor. Constructs the container with the copy of the contents of other.
			vector( const vector& other ) {
				_size = 0;
				_capacity = 0;
				*this = other;
			}
			//	Operator overload for "="
			vector& operator= (const vector& other) {
				if (this != &other) {
					clear();
					if (_capacity)
						_alloc.deallocate(_ptr, _capacity);
					_size = other._size;
					_capacity = other._capacity;
					_alloc = other._alloc;
					if (_capacity)
						_ptr = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(_ptr + i, other._ptr[i]);
				}
				return (*this);
			}
			//	Default Destructor, responsible to destroy and free
			~vector(void) {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_ptr + i);
				if (_capacity)
					_alloc.deallocate(_ptr, _capacity);
			}

			//	Replaces the content with "count" copies of "value".
			void assign( size_type count, const value_type& value ) {
				_size = 0;
				reserve(count);
				for (size_type i = 0; i < count; i++)
					push_back(value);
			}

			//	Replaces the content with the range [first, last]
			//	obs: The enable if is used to restrict the types of elements according to the available to is_integral.
			//	The program will not compile, IF the element type is not "Integral"
			template< class InputIt >
			void assign( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt() ) {
				size_type	delta = last - first;
				clear();
				reserve(delta);
				while (first != last)
					push_back(*first++);
			}

			//	Returns the allocator associated with the container
			allocator_type	get_allocator(void) const { return (_alloc); }

			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Element Access ]-----*/
			//	Functions that access elements within the vector
			//	-> "pos" - in (at and [] overload) it can access specified element (at "pos" position) with bounds checking;
			reference	at(size_type pos) { return (pos < this->size() ? _ptr[pos] : throw (std::out_of_range("Out of Range"))); }
			const_reference	at(size_type pos) const { return (pos < this->size() ? _ptr[pos] : throw (std::out_of_range("Out of Range"))); }
			reference operator[] ( size_type pos ) { return (_ptr[pos]); }
			const_reference operator[] ( size_type pos ) const { return (_ptr[pos]); }
			//	The function below, thos can access the first (front) or the last (back) element within the vector
			reference front() { return (_ptr[0]); }
			const_reference front() const { return (_ptr[0]); }
			reference back() { return (_ptr[_size - 1]); }
			const_reference back() const { return (_ptr[_size - 1]); }
			//	A direct access to the underlying array
			value_type			*data(void) { return (_ptr ? _ptr : NULL); }
			const value_type	*data(void) const { return (_ptr ? _ptr : NULL); }

			/*-----[ Iterators ]-----*/
			//	Functions related to the capability to run through a conteiner.
			iterator begin(void) { return (iterator(_ptr)); }
			const_iterator begin(void) const { return (const_iterator(_ptr)); }
			iterator end(void) { return (iterator(_ptr + _size)); }
			const_iterator end(void) const { return (const_iterator(_ptr + _size)); }
			reverse_iterator rbegin(void) { return (reverse_iterator(end())); }
			const_reverse_iterator rbegin(void) const { return (const_reverse_iterator(end())); }
			reverse_iterator rend(void) { return (reverse_iterator(begin())); }
			const_reverse_iterator rend(void) const { return (const_reverse_iterator(begin())); }

			/*-----[ Capacity ]-----*/
			//	Functions related to the capacity management of elements in a Container.
			//	Check if the container is empty
			bool		empty(void) const { return (_size == 0 ? true : false); }
			//	Return the container size;
			size_type	size(void) const { return (_size); }
			//	Return the maximun size of the container
			size_type	max_size(void) const { return (_alloc.max_size()); }
			//	Reserve is responsible to increase the capacity of the container, if it did not reach the max capacity.
			void		reserve( size_type new_cap ) {
				if (new_cap > max_size())
					throw std::length_error("Reserve Out of Limits");
				if (new_cap > _capacity) {
					pointer		ptr2 = _alloc.allocate(new_cap);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(ptr2 + i, _ptr[i]);
					if (_capacity)
						_alloc.deallocate(_ptr, _capacity);
					std::swap(ptr2, _ptr);
					_capacity = new_cap;
				}
			}
			//	getter for the capacity of the container
			size_type	capacity(void) const { return (_capacity); }

			/*-----[ Modifiers ]-----*/
			//	Functions responsible for modifying the container elements

			//	It will destroy the elements of the containeir
			void clear(void) {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_ptr + i);
				_size = 0;
			}
			//	Insert a "value" in the position before "pos" of the container
			//	-> "tmp" vector is created to be inserted after last position of container.
			iterator insert( iterator pos, const value_type& value ) {
				vector			tmp;
				size_type		index = pos - begin();
				size_type		tmp_end = end() - pos;

				tmp.assign(pos, end());
				_size = index;
				push_back(value);
				for (size_type i = 0; i < tmp_end; i++)
					push_back(tmp[i]);
				return (begin() + index);
			}
			//	In this case, It will insert "count" copies of "value" in the position before "pos" of the container.
			void insert( iterator pos, size_type count, const value_type& value ) {
				vector			tmp;
				size_type		index = pos - begin();
				size_type		tmp_end = end() - pos;

				tmp.assign(pos, end());
				if ((count + _capacity) > (_capacity * 2))
					reserve(_size + count);
				else if (!_size)
					reserve(count);
				_size = index;
				for (size_type i = 0; i < count; i++)
					push_back(value);
				for (size_type i = 0; i < tmp_end; i++)
					push_back(tmp[i]);
			}
			//	In this case, it will insert a range of elements to the position before "pos" of the container.
			//	Where [fist, last] refers to the range.
			//	obs: The enable if is used to restrict the types of elements according to the available to is_integral.
			//	The program will not compile, IF the element type is not "Integral"
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt() ) {
				vector			tmp;
				size_type		index = pos - begin();
				size_type		tmp_end = end() - pos;
				difference_type	delta = last - first;

				tmp.assign(pos, end());
				if ((delta + _capacity) > (_capacity * 2))
					reserve(_size + delta);
				else if (!_size)
					reserve(delta);
				_size = index;
				while (first != last)
					push_back(*first++);
				for (size_type i = 0; i < tmp_end; i++)
					push_back(tmp[i]);
			}
			//	The Erase will destroy a element in the "pos" position, and adjust the container
			iterator erase( iterator pos ) {
				if (_size > 0)
					_alloc.destroy(&*pos);
				for (iterator it = pos; it != end(); it++) {
					_alloc.construct(&*it, *(it + 1));
					_alloc.destroy(&*(it + 1));
				}
				_size--;
				return (pos);
			}
			//	This will erase a range of elements.
			//	Invalidates iterators and references at or after the point of the erase, including the end() iterator
			iterator erase( iterator first, iterator last ) {
				iterator	tmp = first;
				while (last != end()) {
					*tmp = *last;
					tmp++; last++;
				}
				_size -= last - first;
				return (tmp);
			}
			//	It will add a "value" element to the end of the container
			void push_back( const value_type& value ) {
				if (_capacity == 0)
					reserve(1);
				else if (_size + 1 > _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_ptr + _size, value);
				_size++;
			}
			//	It will destroy the last element of the container.
			void pop_back(void) {
				if (_size > 0) {
					_alloc.destroy(_ptr + _size);
					_size--;
				}
			}
			//	Resizes the container to contain "count" elements.
			//	If the current size is greater than "count", the container is reduced to its first "count" elements.
			//	If the current size is less than "count", additional copies of "value" are appended.
			void resize( size_type count, value_type value = value_type() ) {
				if (count < _size) {
					for (; _size > count; _size--)
						_alloc.destroy(_ptr + _size);
				} else if (count > _size) {
					reserve(count);
					for (size_type i = _size; i < count; i++) {
						_alloc.construct(_ptr + i, value);
						_size++;
					}
				}
			}
			//	Generaly, swaps the contents of a container with the "other" container.
			void swap( vector& other ) {
				std::swap(_size, other._size);
				std::swap(_capacity, other._capacity);
				std::swap(_ptr, other._ptr);
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
		private:
			//	A few variables are needed to run a Vector container:
			//	-> "_size" is related to the current size of the container, while the "_capacity" refers to the maximum size possible.
			//	-> "_ptr" is a pointer where the vector will be stored.
			//	-> "_alloc" with store the allocator passed with the container creation.
			size_type		_size;
			size_type		_capacity;
			pointer			_ptr;
			allocator_type	_alloc;
	};
	/*-----[ Non-Member Function ]-----*/
	//	Exchange the contents of the "lhs" container and "rhs" container
	template< class T, class Alloc >
	void	swap( vector<T, Alloc>& lhs, vector<T, Alloc>& rhs ) { lhs.swap(rhs); }
	//	The following overloads correspond to the comparison overloads outside the vector container.
	template< class T, class Alloc >
	bool	operator== ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return (ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
	template< class T, class Alloc >
	bool	operator!= ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return (!(ft::equal(lhs.begin(), lhs.end(), rhs.begin()))); }
	template< class T, class Alloc >
	bool	operator<  ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	template< class T, class Alloc >
	bool	operator<= ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return ((lhs > rhs) ? false : true); }
	template< class T, class Alloc >
	bool	operator>  ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }
	template< class T, class Alloc >
	bool	operator>= ( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return ((lhs < rhs) ? false : true); }
}

#endif
