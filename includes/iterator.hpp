/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:23:25 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/12 01:54:48 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft {
	/*-----[ iterator_traits ]-----*/
	//	Generaly, the proprieties of the Iterator.
	//	https://www.cplusplus.com/reference/iterator/iterator_traits/
	template<class Iterator>
	class iterator_traits {
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template<class T>
	class iterator_traits<T *> {
		public:
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T										*pointer;
			typedef T										&reference;
			typedef std::random_access_iterator_tag				iterator_category;
	};
	
	template<class T>
	class iterator_traits<const T *> {
		public:
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T										*pointer;
			typedef T										&reference;
			typedef std::random_access_iterator_tag				iterator_category;
	};
	/*-----------------------------------------------------------------------------------------------------------------------------*/
	//	Random Access Iterator, generaly, can be compared as pointers functions;
	//	This can access any element in the container
	template<typename T>
	class random_access_iterator {
		public:
			/*-----[ Member Types ]-----*/
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T										*pointer;
			typedef T										&reference;
			typedef std::random_access_iterator_tag			iterator_category;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Functions ]-----*/
			random_access_iterator(void): _it(NULL) {}
			~random_access_iterator(void) {}
			explicit random_access_iterator(value_type *it): _it(it) {}
			random_access_iterator(random_access_iterator const &copy) { *this = copy; }
			random_access_iterator &operator=(random_access_iterator const &copy) {
				_it = copy._it;
				return (*this);
			}
			/*-----[ Expressions ]-----*/
			//	Equivalence operations (a == b / a != b)
			bool	operator==(random_access_iterator<T> const &obj) { return (_it == obj._it); }
			bool	operator!=(random_access_iterator<T> const &obj) { return (_it != obj._it); }
			//	Dereference as ab rvalue (*a or a->m) even as mutable iterator (*a = t)
			reference	operator*() { return (*_it); }
			pointer		operator->() { return (&operator*()); }
			//	increment and decrement (++a or a++ / --a or a--)
			random_access_iterator	&operator++() {
				_it++;
				return (*this);
			}
			random_access_iterator	operator++(int) {
				random_access_iterator	tmp = *this;
				++(*this);
				return (tmp);
			}
			random_access_iterator	&operator--() {
				_it--;
				return (*this);
			}
			random_access_iterator	operator--(int) {
				random_access_iterator	tmp = *this;
				--(*this);
				return (tmp);
			}
			//	Arithmetic operations (a + b / a - b)
			random_access_iterator	&operator+ (difference_type value){ return (random_access_iterator(_it + value)); }
			random_access_iterator	&operator- (difference_type value){ return (random_access_iterator(_it - value)); }
			//	Comparison operations ( a < b/ a > b / a <= b / a >= b )
			bool	operator< (random_access_iterator<T> const &obj) { return (_it < obj._it); }
			bool	operator> (random_access_iterator<T> const &obj) { return (_it > obj._it); }
			bool	operator<=(random_access_iterator<T> const &obj) { return (_it <= obj._it); }
			bool	operator>=(random_access_iterator<T> const &obj) { return (_it >= obj._it); }
			//	Compound assignment (a += b / a -= b)
			random_access_iterator	&operator+=(difference_type value) {
				_it += value;
				return (*this);
			}
			random_access_iterator	&operator-=(difference_type value) {
				_it -= value;
				return (*this);
			}
			//	Offset dereference (a[b])
			reference	operator[](difference_type value) const { return (_it[value]); }
			/*-----[ Extra ]-----*/
		private:
			pointer		_it;
	};
	
	/*-----------------------------------------------------------------------------------------------------------------------------*/
	/*-----[ Reverse Iterator ]-----*/
	//	This class reverses the direction in which a bidirectional or random-access iterator iterates through a range.
	template<class Iterator>
	class reverse_iterator {
		public:
			/*-----[ Member Types ]-----*/
			typedef Iterator								iterator_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference				reference;
			typedef typename iterator_traits<Iterator>::iterator_category		iterator_category;
			/*-----[ Member Functions ]-----*/
			//	Default constructor and destructor functions
			reverse_iterator(void) {}
			~reverse_iterator(void) {}
			//	Parametrized Costructor which receives a pointer to an existing iterator
			explicit reverse_iterator(iterator_type it): _it(it) {}
			//	This is a Copy of a exiting Reverted iterator
			template<class Iter>
			reverse_iterator(reverse_iterator<Iter> const &rev_it) { _it = rev_it.base(); }
			//	returns the copy of the base iterator
			iterator_type	base(void) const { return (_it); }
			//	A reference to the element pointed by the iterator. It decreases a copy of the base iterator.
			reference		operator*() const {return *(--Iterator(_it)); }
			//	Applies the inverse binary operator (-/+ or --/++, or +=/-=) to the iterator value
			reverse_iterator		&operator+ (difference_type value) { return (reverse_iterator(_it - value)); }
			reverse_iterator		&operator++() { 
				_it--;
				return (*this);
			}
			reverse_iterator		operator++(int) {
				reverse_iterator	tmp = *this;
				++(*this);
				return(tmp);
			}
			reverse_iterator		&operator+=(difference_type value) { 
				_it -= value;
				return (*this);
			 }
			reverse_iterator		&operator- (difference_type value) { return (reverse_iterator(_it + value)); }
			reverse_iterator		&operator--() {
				_it++;
				return (*this);
			}
			reverse_iterator		operator--(int) {
				reverse_iterator	tmp = *this;
				--(*this);
				return (tmp);
			}
			reverse_iterator		&operator-=(difference_type value) {
				_it += value;
				return (*this);
			}
			//	Returns a Pointer to the element apointed by the iterator
			pointer					operator->() const { return &(operator*()); }
			//	Access the element located within the iterator pointer in the "n" position
			reference				operator[](difference_type n) const { return (base()[- n - 1]); }
		private:
			iterator_type	_it;
	};
	/*-----[ Non-Member Functions - Reverse-Iterator]-----*/
	//	Overload functions external to the reverse-iterator class.
	//	Adding or substraction operators
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, 
	const reverse_iterator<Iterator>& rhs) { return (rhs.base() + lhs.base()); }

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator+(typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>& rev_it) { return (reverse_iterator<Iterator>(rev_it.base() - n)); }
	//	Comparison operators
	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }
	template <class Iterator>
	bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }
	template <class Iterator>
	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }
	/*-----------------------------------------------------------------------------------------------------------------------------*/
}

#endif
