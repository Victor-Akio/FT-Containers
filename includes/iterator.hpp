/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:23:25 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/30 17:36:31 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "AVL.hpp"
# include "containers.hpp"

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
			typedef T*										pointer;
			typedef T&										reference;
			typedef std::random_access_iterator_tag			iterator_category;
	};

	template<class T>
	class iterator_traits<const T *> {
		public:
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef std::random_access_iterator_tag			iterator_category;
	};
	/*----------------------------------------------------------------------------------------------------------------------------*/
	/*-----[ Random Access Iterator - Vector ]-----*/
	//	Random Access Iterator, generaly, can be compared as pointers functions;
	//	This can access any element in the container
	template<typename T>
	class random_access_iterator {
		public:
			/*-----[ Member Types ]-----*/
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef std::random_access_iterator_tag			iterator_category;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Functions ]-----*/
			random_access_iterator(void): _it(NULL) {}
			explicit random_access_iterator(value_type *it): _it(it) {}
			random_access_iterator(random_access_iterator const &copy) { *this = copy; }
			random_access_iterator &operator=(random_access_iterator const &copy) {
				_it = copy._it;
				return (*this);
			}
			pointer		base(void) const { return (_it); }
			~random_access_iterator(void) {}
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
			random_access_iterator	operator+  (difference_type value) const { return (random_access_iterator(_it + value)); }
			random_access_iterator	operator-  (difference_type value) const { return (random_access_iterator(_it - value)); }
			//	Comparison operations ( a < b/ a > b / a <= b / a >= b )
			bool	operator<  (random_access_iterator<T> const &obj) { return (_it < obj._it); }
			bool	operator>  (random_access_iterator<T> const &obj) { return (_it > obj._it); }
			bool	operator<= (random_access_iterator<T> const &obj) { return (_it <= obj._it); }
			bool	operator>= (random_access_iterator<T> const &obj) { return (_it >= obj._it); }
			//	Compound assignment (a += b / a -= b)
			random_access_iterator	&operator+= (difference_type value) {
				_it += value;
				return (*this);
			}
			random_access_iterator	&operator-= (difference_type value) {
				_it -= value;
				return (*this);
			}
			//	Offset dereference (a[b])
			reference	operator[] (difference_type value) const { return (_it[value]); }
			/*-----[ Extra ]-----*/
		private:
			pointer		_it;
	};
	/*-----[ Non Member Functions - Random Access Iterator ]-----*/
	template <class Iterator>
	typename random_access_iterator<Iterator>::difference_type operator-(const random_access_iterator<Iterator>& lhs, 
	const random_access_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }

	template <class Iterator>
	typename random_access_iterator<Iterator>::difference_type operator+(typename random_access_iterator<Iterator>::difference_type n,
	const random_access_iterator<Iterator> &it) { return (random_access_iterator<Iterator>(it.base() + n)); }
	//	Comparison operators
	template <class Iterator>
	bool operator== (const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }
	template <class Iterator>
	bool operator!= (const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }
	template <class Iterator>
	bool operator< (const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }
	template <class Iterator>
	bool operator> (const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }
	template <class Iterator>
	bool operator<= (const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }
	template <class Iterator>
	bool operator>= (const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }
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
	/*-----[ BiDirectional Iterator ]-----*/
	//	Is a type of iterator, as for Random Access Iterator and reverse iterator above.
	//	It is an iterator that can be used to access the sequence of elements in a range in both directions, towards the end and towards the begining.
	//	As when compared to the "Forward Iterator", the biggest difference is that it can also be decremented.
	template<typename T, typename Compare, typename Alloc>
	class bidirectional_iterator {
		public:
			/*-----[ Member Types ]-----*/
			typedef int									difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef Node<value_type, Alloc>				node_type;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Functions ]-----*/
			bidirectional_iterator(void): _it(NULL) {}
			explicit bidirectional_iterator(pointer it, const AVL<value_type, Compare, Alloc> *avl = NULL): _it(it), _avl(avl) {}
			bidirectional_iterator(bidirectional_iterator const &copy) { *this = copy; }
			bidirectional_iterator &operator=(bidirectional_iterator const &copy) {
				_it = copy._it;
				_avl = copy._avl;
				return (*this);
			}
			operator	bidirectional_iterator<const T, Compare, Alloc> () const { return (bidirectional_iterator<const T, Compare, Alloc>(_it, reinterpret_cast<AVL<const value_type, Compare, Alloc> const *>(_avl))); }
			~bidirectional_iterator(void) {}
			/*-----[ Expressions ]-----*/
			//	Equivalence operations (a == b / a != b)
			bool	operator== (bidirectional_iterator const &obj) { return (_it == obj._it); }
			bool	operator!= (bidirectional_iterator const &obj) { return (_it != obj._it); }
			//	Dereference as ab value (*a or a->m) even as mutable iterator (*a = t)
			reference	operator*() { return (*_it); }
			pointer		operator->() { return (&operator*()); }
			// increment and decrement (++a or a++ / --a or a--)
			bidirectional_iterator	&operator++() {
				node_type *node = _avl->find(_avl->root, *_it);
				if (node) {
					node_type *tmp = _avl->next(*_it);
					if (tmp) _it = tmp->data;
					else _it = NULL;
				}
				return (*this);
			}
			bidirectional_iterator	operator++(int) {
				bidirectional_iterator	tmp = *this;
				++(*this);
				return (tmp);
			}
			bidirectional_iterator	&operator--() {
				node_type	*node = NULL;
				if (!_it) {
					node = _avl->Max(_avl->root);
					if (node) _it = node->data;
					return (*this);
				}
				node = _avl->find(_avl->root, *_it);
				if (node) {
					node_type *tmp = _avl->previous(*_it);
					if (tmp) _it = tmp->data;
					else _it = NULL;
				}
				return (*this);
			}
			bidirectional_iterator	operator--(int) {
				bidirectional_iterator	tmp = *this;
				--(*this);
				return (tmp);
			}
		private:
			pointer									_it;
			const AVL<value_type, Compare, Alloc>	*_avl;
	};
};

#endif
