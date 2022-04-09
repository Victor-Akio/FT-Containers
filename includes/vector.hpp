/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:25:22 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/09 02:20:14 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>
# include "iterator.hpp"

namespace ft {
	template< class T, class Alloc = std::allocator<T> >
	class vector {
		protected:
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
			vector(void): _size(0), _capacity(0), _ptr(NULL) {}

			//Constructs an empty container with the given allocator alloc.
			explicit vector( const allocator_type& alloc ): _alloc(alloc), _size(0), _capacity(0), _ptr(NULL) {}
			
			//Constructs the container with count copies of elements with value value.
			explicit vector( size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) {
				_size = count;
				_capacity = count;
				_alloc = alloc;
				_ptr = _alloc.allocate(count);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_ptr + i, value);
			}
			
			// Constructs the container with the contents of the range [first, last).
			template< class InputIt >
			vector( InputIt first, InputIt last, const allocator_type& alloc = allocator_type() ) {
				size_type	delta = last - first;
				_ptr = _alloc.allocate(delta);
				for (size_type i = 0; i < delta; i++)
					_alloc.construct(_ptr + i, first[i]);
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

			vector& operator=(const vector& other) {
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

			~vector(void) {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_ptr + i);
				if (_capacity)
					_alloc.deallocate(_ptr, _capacity);
			}

			void assign( size_type count, const value_type& value ) {
				_size = 0;
				reserve(count);
				for (size_type i = 0; i < count; i++)
					push_back(value);
			}

			template< class InputIt >
			void assign( InputIt first, InputIt last ) {
				size_type	delta = last - first;
				clear();
				reserve(delta);
				while (first != last)
					push_back(*first++);
			}

			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Element Access ]-----*/
			reference	at(size_type pos) {return (pos == this->size() ? _ptr[pos] : throw (std::out_of_range("Out of Range"))); }
			const_reference	at(size_type pos) const {return (pos == this->size() ? _ptr[pos] : throw (std::out_of_range("Out of Range"))); }
			reference operator[]( size_type pos ) { return (_ptr[pos]); }
			const_reference operator[]( size_type pos ) const { return (_ptr[pos]); }
			reference front() { return (_ptr[0]); }
			const_reference front() const { return (_ptr[0]); }
			reference back() { return (_ptr[_size - 1]); }
			const_reference back() const { return (_ptr[_size - 1]); }
			// data();

			/*-----[ Iterators ]-----*/
			iterator begin(void) { return (iterator(_ptr)); }
			const_iterator begin(void) const { return (const_iterator(_ptr)); }
			iterator end(void) { return (iterator(_ptr + _size)); }
			const_iterator end(void) const { return (const_iterator(_ptr + _size)); }
			reverse_iterator rbegin(void) { return (reverse_iterator(end())); }
			const_reverse_iterator rbegin(void) const { return (const_reverse_iterator(end())); }
			reverse_iterator rend(void) { return (reverse_iterator(begin())); }
			const_reverse_iterator rend(void) const { return (const_reverse_iterator(begin())); }

			/*-----[ Capacity ]-----*/
			bool		empty(void) const { return (size() == 0 ? true : false); }
			size_type	size(void) { return (_size); }
			size_type	max_size(void) const { return (_alloc.max_size()); }
			void		reserve( size_type new_cap ) {
				if (new_cap > max_size())
					throw std::length_error("Reserve Out of Limits");
				if (new_cap > _capacity) {
					pointer		ptr2 = _alloc.allocate(new_cap);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(ptr2 + i, _ptr[i]);
					_alloc.deallocate(_ptr, _capacity);
					std::swap(ptr2, _ptr);
					_capacity = new_cap;
				}
			}
			
			size_type	capacity(void) const { return (_capacity); }

			/*-----[ Modifiers ]-----*/
			void clear(void) {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_ptr + i);
				_size = 0;
			}
			
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
			//	template< class InputIt >
					// void insert( iterator pos, InputIt first, InputIt last );
			iterator erase( iterator pos ) {
				if (_size > 0)
					_alloc.destroy(&*pos);
				for (iterator it = pos; it != end(); it++) {
					_alloc.construct(&*it, *(it + 1));
					_alloc.destroy(&*(it + 1));
				}
				size--;
				return (pos);
			}
			
			// iterator erase( iterator first, iterator last ) {
			// 	iterator tmp = 
			// 	while (first != last) {
					
			// 	}
			// }
			
			void push_back( const value_type& value ) {
				if (_capacity == 0)
					reserve(1);
				else if (_size + 1 > _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_ptr + _size, value);
				_size++;
			}
			
			void pop_back(void) {
				if (_size > 0) {
					_alloc.destroy(_ptr + _size);
					size--;
				}
			}
			
			void resize( size_type count, value_type value = value_type() ) {
				if (count < _size) {
					for (; _size > count; size--)
						_alloc.destroy(_ptr + _size);
				} else if (count > _size) {
					reserve(count);
					for (size_type i = _size; i < count; i++) {
						_alloc.construct(_ptr + i, value);
						_size++;
					}
				}
			}

			void swap( vector& other ) {
				std::swap(_size, other._size);
				std::swap(_capacity, other._capacity);
				std::swap(_ptr, other._ptr);
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
		private:
			size_t			_size;
			size_t			_capacity;
			pointer			_ptr;
			allocator_type	_alloc;
	};
	/*-----[ Non-Member Function ]-----*/
	template< class T, class Alloc >
	void	swap( vector<T, Alloc>& lhs, vector<T, Alloc>& rhs ) { lhs.swap(rhs); }

	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {
		if (lhs._size() != rhs._size())
			return (false);
		return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {
		if (lhs._size() != rhs._size())
			return (true);
		return (!(std::equal(lhs.begin(), lhs.end(), rhs.begin())));
	}

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	// template< class T, class Alloc >
	// bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	// template< class T, class Alloc >
	// bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return !(std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
}

#endif
