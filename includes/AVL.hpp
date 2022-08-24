/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 20:52:56 by vminomiy          #+#    #+#             */
/*   Updated: 2022/05/02 23:10:32 by vminomiy         ###   ########.fr       */
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
			//	Also, pdf specifies the usage of public, private and protected to the containers.
			Node	*left;
			Node	*right;
			Node	*parent;
			T		*data;
			int		height;
			Alloc	_alloc;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Functions ]-----*/
			Node(void): left(NULL), right(NULL), parent(NULL), data(NULL), height(0) {}
			Node(T const &copy): left(NULL), right(NULL), parent(NULL), height(1) {
				data = _alloc.allocate(1);
				_alloc.construct(data, copy);
			}

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
				return (*this);
			}
			~Node(void) {}
	};
	template<typename T, class Compare, class Alloc>
	class AVL {
		public:
			/*-----[ Member Types ]-----*/
			typedef T									value_type;
			typedef Compare								key_compare;
			typedef Alloc								allocator_type;
			typedef Node<value_type, Alloc>				node_type;
			node_type									*root;
			//	Rebind is for allocating memory for a type that differs from the element type of the container being implemented.
			//	In the context, when creating a new node, it is possible to create differen types of objects.
			//	https://stackoverflow.com/questions/14148756/what-does-template-rebind-do
			typename Alloc::template rebind< node_type >::other		n_alloc;
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Member Function ]-----*/
			AVL(void): root(NULL) {}
			AVL(AVL const &copy) { *this = copy; }
			AVL		&operator=(AVL const &copy) {
				if (this == &copy)
					return (*this);
				root = copy.root;
				_comp = copy._comp;
				return (*this);
			}
			~AVL(void) {}
			//	Getter of the node height 
			int		getHeight(node_type *node) {
				if (!node) return (0);
				return ( node->height );
			}
			//	Assign all node subtrees in sequence.
			void	assign(const node_type *node) {
				if (!node) return ;
				assign(node->left);
				if (node->data)
					insert(*(node->data));
				assign(node->right);
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
			node_type		*rightRotate(node_type *z) {
				node_type		*y = z->left;	// set y
				if (!y) return (z);
				node_type		*T3 = y->right;	// save for z->left
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
			node_type		*leftRotate(node_type *z) {
				node_type		*y = z->right;		// set y
				node_type		*T2 = y->left;		// save for z->left
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
			node_type		*newNode(const value_type &key) {
				node_type		*node = n_alloc.allocate(1);
				n_alloc.construct(node, key);
				return (node);
			}
			//	Insert the key to the root node.
			node_type		*insert(value_type key) {
				this->root = this->insert(this->root, key);
				return (root);
			}
			//	Balance the current branch, if needed it will rotate the  nodes, to return to an AVL tree status.
			//	The range of height of the AVL tree nodes should be between "-1 to 1", if higher it will right rotate and if it is lower than -1, left rotate it.
			//	_comp is TRUE if less, FALSE if greater or equal
			node_type		*balance(node_type *node, value_type const &key) {
				if ((getHeight(node->left) - getHeight(node->right)) > 1) {
					if (_comp(key.first, node->left->data->first)) return (rightRotate(node));
					else {
						node->left = leftRotate(node->left);
						return (rightRotate(node));
					}
				}
				if ((getHeight(node->left) - getHeight(node->right)) < -1) {
					if (_comp(node->right->data->first, key.first)) return (leftRotate(node));
					else {
						node->left = rightRotate(node->left);
						return (leftRotate(node));
					}
				}
				return (node);
			}
			//	Insert a node to the tree and rebalance if needed.
			//	The insertion will be on the right node, if the current key is greater than the root key, or in the left node if the current key is lower than the root key.
			//	_comp is TRUE if less, FALSE if greater or equal
			node_type		*insert(node_type *node, const value_type &key) {
				if (!node) return (newNode(key));
				if (_comp(key.first, node->data->first)) {
					node->left = insert(node->left, key);
					node->left->parent = node;
				} else if (_comp(node->data->first, key.first)) {
					node->right = insert(node->right, key);
					node->right->parent = node;
				} else
					return (node);
				node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
				return (balance(node, key));
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Delete ]-----*/
			//	Delete the root node, if there is one.
			bool		del(value_type key) {
				if (find(root, key)) {
					this->root = this->del(this->root, key);
					return (true);
				}
				return (false);
			}
			//	Delete a node recursively form the last node to the root node:
			//	- (1) Child Nodes receives a NULL;
			//	- (2) In case of one Child node, the parent of the node, will become the parent of the child.
			//	- (3) If thre is 2 child nodes, You should find the next child (Min of the right child) rotate the node and delete the child.
			//	_comp is TRUE if less, FALSE if greater or equal
			node_type		*del(node_type *node, value_type const &key) {
				if (!node) return (node);						//(1)
				if (_comp(key.first, node->data->first))
					node->left = del(node->left, key);
				else if (_comp(node->data->first, key.first))
					node->right = del(node->right, key);
				else if (node->data->first == key.first) {
					if (!node->left || !node->right) {
						node_type *tmp = node->left ? node->left : node->right;
						if (!tmp) {
							tmp = node;
							node = NULL;
						} else {
							node_type *nodeParent = node->parent;		//(2)
							*node = *tmp;
							node->parent = nodeParent;
						}
						_alloc.deallocate(tmp->data, 1);
						n_alloc.deallocate(tmp, 1);
					} else {
					node_type *tmp = Min(node->right);				//(3)
					_alloc.construct(node->data, *tmp->data);
					node->right = del(node->right, *tmp->data);
					}
				} 
				if (!node) return (node);											//After onde deletion, it updates the height and return the node.
				node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
				return (balance(node, key));
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Element Access ]-----*/
			//	Return a child node, if exists
			//	_comp is TRUE if less, FALSE if greater or equal
			node_type		*find(node_type *node, value_type const &key) const {
				if (!node) return (NULL);
				if (node->data && node->data->first == key.first) return (node);
				if (_comp(key.first, node->data->first)) return (find(node->left, key));
				else if (_comp(node->data->first, key.first)) return (find(node->right, key));
				return (node);
			}
			/*	Return the next node:
						- Return NULL if there is no next;
						- If there is a right subtree, find the minimal node of the subtree;
						- If there is only a left subtree, check if the parent is not the next node, instead of the left one.
			*/		
			node_type		*next(value_type const &key) const {
				node_type		*node = find(root, key);
				if (!node) return (NULL);
				if (node->right != NULL) return (Min(node->right));
				node_type		*next = node->parent;
				while (next != NULL && node == next->right) {
					node = next;
					next = next->parent;
				}
				node = next;
				return (node);
			}
			/*	Return the next node:
						- Return NULL if there is no next;
						- If there is a left subtree, find the minimal node of the subtree;
						- If there is only a right subtree, check if the parent is not the next node, instead of the right one.
			*/
			node_type		*previous(value_type const &key) const {
				node_type		*node = find(root, key);
				if (!node) return (NULL);
				if (node->left != NULL) return (Max(node->left));
				node_type		*previous = node->parent;
				while (previous != NULL && node == previous->left) {
					node = previous;
					previous = previous->parent;
				}
				node = previous;
				return (node);
			}
			/*-----------------------------------------------------------------------------------------------------------------------------*/
			/*-----[ Utility ]-----*/
			//	Return the Max Node Element of the AVL tree
			node_type		*Max(node_type *node) const {
				if (!node) return (NULL);
				node_type *max = node;
				while (max->right)
					max = max->right;
				return (max);
			}
			//	Return the Minimal Node Element of the AVL tree
			node_type		*Min(node_type *node) const {
				if (!node) return (NULL);
				node_type *min = node;
				while (min->left)
					min = min->left;
				return (min);
			}
			//	From the end to begining, it will deallocate all nodes
			void		PreOrder(node_type *node) {
				if (!node) return ;
				PreOrder(node->left);
				_alloc.deallocate(node->data, 1);
				PreOrder(node->right);
				n_alloc.deallocate(node, 1);
				node = NULL;
			}
		private:
			key_compare		_comp;
			allocator_type	_alloc;
	};
}

#endif
