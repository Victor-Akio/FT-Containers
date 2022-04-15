/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:52:56 by vminomiy          #+#    #+#             */
/*   Updated: 2022/04/16 01:02:12 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
# define AVL_HPP

namespace ft {
	/*-----[ Node Definitions ]-----*/
	//	Each individual node is defined as below.
	template<typename T, class Alloc>
	class Node {
		public:
			//	Variables, being used as public, because i did not wish to build getters and setters.
			Node	*left;
			Node	*right;
			Node	*parent;
			T		*data;
			int		height;
			Alloc	_alloc;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Functions ]-----*/
			Node(void): left(NULL), right(NULL), parent(NULL), data(NULL), height(0) {}
			Node(Node const &copy): left(NULL), right(NULL), parent(NULL), data(_alloc.allocate(1)), height(0) { _alloc.construct(data, copy); }
			Node	&operator=(Node const &copy) {
				if (this == &copy)
					return (*this);
				if (data)
					_alloc.deallocate(data, 1);
				left = copy.left;
				right = copy.right;
				parent = copy.parent;
				height = copy.height;
				data = _alloc.allocate(1);
				_alloc.construct(data, *copy.data);
				return (*this)
			}
			~Node(void) {}
		private:
	};
	template<typename T, class Compare, class Alloc>
	class AVL {
		public:
			/*-----[ Member Types ]-----*/
			typedef T					value_type;
			typedef Compare				key_compare
			typedef Alloc				allocator_type;
			Node< valute_type, Alloc >	*root;
			//	Rebind is for allocating memory for a type that differs from the element type of the container being implemented.
			//	In the context, when creating a new node, it is possible to create differen types of objects.
			//	https://stackoverflow.com/questions/14148756/what-does-template-rebind-do
			typename Alloc::template rebind<Node<value_type, Alloc>>::other		n_alloc;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Function ]-----*/
			AVL(void): root(NULL) {}
			AVL(AVL const &copy) { *this = copy; }
			AVL	&operator=(AVL const &copy) {
				if (this == copy)
					return (*this);
				root = copy.root;
				_comp = copy._comp;
				return (*this);
			}
			~AVL(void) {}
			//	Getter of the node height 
			int		getHeight(Node<value_type, Alloc>	*node) {
				if (!node) return (0);
				return ( node->height );
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Rotation ]-----*/
			/*	RIGHT ROTATION
				-> z, y, x will be the branch members being rotated. x - y - z
				-> T1, T2, T3 and T4 are subtrees.
						z                                      y 
					   / \                                   /   \
					  y   T4      Right Rotate (z)          x      z
					 / \          - - - - - - - - ->      /  \    /  \ 
					x   T3                               T1  T2  T3  T4
				   / \
				 T1   T2
				Generaly, it is like a swap exchange of pointers.
			*/
			Node<value_type, Alloc>		*rightRotate(Node<value_type, Alloc> *z) {
				Node<value_type, Alloc>		*y = z->left;	// set y
				if (!y) return (z);
				Node<value_type, Alloc>		*T3 = y->right;	// save for z->left
				if (y->right != NULL) 
					y->right->parent = z;					//	y->parent is z, everything is set to rotate
				y->right = z;
				z->left = T3;
				y->parent = z->parent;
				z->parent = y;
				z->height = std::max(getHeight(z->left), getHeight(z->right)) + 1;
				y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
				return (y);
			}
			/*	LEFT ROTATION
				-> z, y, x will be the branch members being rotated. x - y - z
				-> T1, T2, T3 and T4 are subtrees.
					  z                                y
					 /  \                            /   \ 
					T1   y     Left Rotate(z)       z      x
					    /  \   - - - - - - - ->    / \    / \
					   T2   x                     T1  T2 T3  T4
							/ \
						   T3  T4
				Generaly, it is like a swap exchange of pointers.
			*/
			Node<value_type, Alloc>		*leftRotate(Node<value_type, Alloc> *z) {
				Node<value_type, Alloc>		*y = z->right;		// set y
				Node<value_type, Alloc>		*T2 = y->left;		// save for z->left
				if (y->left != NULL) 
					y->left->parent = z;						//	y->parent is z, everything is set to rotate
				y->left = z;
				z->right = T2;
				y->parent = z->parent;
				z->parent = y;
				z->height = std::max(getHeight(z->left), getHeight(z->right)) + 1;
				y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
				return (y);
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Insert ]-----*/
			//	Create a New Node to the tree
			Node<value_type, Alloc>		*newNode(value_type	const &key) {
				Node<value_type, Alloc>		*node = n_alloc.allocate(1);
				n_alloc.construct(node, key);
				return (node);
			}
			//	Insert the key to the root node.
			Node<value_type, Alloc>		*insert(value_type const &key) {
				this->root = this->insert(this->root, key)
				return (root);
			}
			//	Balance the current branch, if needed it will rotate the  nodes, to return to an AVL tree status.
			//	The range of height of the AVL tree should be between "-1 to 1"
			AvlNode<value_type, Alloc>		*balance(AvlNode<value_type, Alloc> *node, value_type const &key) {
				if ((getHeight(node->right) - getHeight(node->left)) > 1) {
					if (_comp(key.first, node->left->data->first)) return (rightRotate(node));
					else {
						node->left = leftRotate(node->left);
						return (rightRotate(node));
					}
				}
				if ((getHeight(node->right) - getHeight(node->left)) < -1) {
					if (_comp(key.first, node->left->data->first)) return (leftRotate(node));
					else {
						node->left = rightRotate(node->left);
						return (leftRotate(node));
					}
				}
				return (node);
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Delete ]-----*/
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Element Access ]-----*/
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Comparison Functions ]-----*/
			//	Return the Max Node Element of the AVL tree
			Node<value_type, Alloc>		*Max(Node<value_type, Alloc> *node) const {
				if (!node) return (NULL);
				Node<value_type, Alloc> *max = node;
				while (max->right)
					max = max->right;
				return (max);
			}
			//	Return the Minimal Node Element of the AVL tree
			Node<value_type, Alloc>		*Min(Node<value_type, Alloc> *node) const {
				if (!node) return (NULL);
				Node<value_type, Alloc> *min = node;
				while (min->left)
					min = min->left;
				return (min);
			}
		private:
			key_compare		_comp;
			allocator_type	_alloc;
	};
}

#endif
