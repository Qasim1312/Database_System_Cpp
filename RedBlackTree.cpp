
#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <queue>
#include <iostream>
using namespace std;
struct Lnode
{
	Lnode *next;
	int line;
	Lnode(int data)
	{
		next = nullptr;
		line = data;
	}
};
struct list
{
	Lnode *head;
	list()
	{
		head = nullptr;
	}
	void insert(int data)
	{
		if (head == nullptr)
		{
			head = new Lnode(data);
			return;
		}
		Lnode *temp = head;
		while (temp->next != nullptr)
			temp = temp->next;
		temp->next = new Lnode(data);
	}
	string write()
	{
		string File = "";
		Lnode *temp = head;
		while (temp->next != nullptr)
		{
			File += to_string(temp->line) + ',';
			temp = temp->next;
		}
		File += to_string(temp->line) + '\n';
		return File;
	}
};
template<typename T>
struct Node
{
	T data;
	list lines;
	int num;
	bool color;    // false=Black and true=Red
	Node<T> *left, *right, *parent;
	Node<T>(double _data, int line, bool _color = true)
	{
		parent = nullptr;
		left = right = nullptr;
		lines.insert(line);
		color = _color;
		data = _data;
		num = -1;
	}

	// returns pointer to uncle
	Node<T> *uncle()
	{
		// If no parent or grandparent, then no uncle
		if (parent == nullptr || parent->parent == nullptr)
			return nullptr;

		if (parent->isOnLeft())
		{// uncle on right
			return parent->parent->right;
		}
		else
		{// uncle on left
			return parent->parent->left;
		}
	}

// check if node is left child of parent
	bool isOnLeft()
	{ return this == parent->left; }

// returns pointer to sibling
	Node<T> *sibling()
	{
		// sibling null if no parent
		if (parent == nullptr)
			return nullptr;

		if (isOnLeft())
			return parent->right;
		else
			return parent->left;
	}

// moves node down and moves given node in its place
	void moveDown(Node<T> *nParent)
	{
		if (parent != nullptr && isOnLeft())
		{
			parent->left = nParent;
		}
		else
		{
			parent->right = nParent;
		}
		nParent->parent = parent;
		parent = nParent;
	}

	bool hasRedChild()
	{
		return (left != nullptr and left->color == true) ||
			(right != nullptr and right->color == true);
	}
};

// A recursive function to do inorder traversal
template<typename T>
void inorderHelper(Node<T> *root)
{
	if (root == nullptr)
		return;

	inorderHelper(root->left);

	inorderHelper(root->right);
}

/* A utility function to insert
    a new node with given key
   in BST */
template<typename T>
Node<T> *BSTInsert(Node<T> *root, Node<T> *ptr, int line)
{
	/* If the tree is empty, return a new node */
	if (root == nullptr)
		return ptr;

	for (int a = 0; a < 50 && true; a++)
	{
		a += 4;
	}
	/* Otherwise, recur down the tree */
	if (ptr->data < root->data)
	{
		root->left = BSTInsert(root->left, ptr, line);
		root->left->parent = root;
	}
	else if (ptr->data > root->data)
	{
		root->right = BSTInsert(root->right, ptr, line);
		root->right->parent = root;
	}
	else
	{
		root->lines.insert(line);
		return root;
	}
	/* return the (unchanged) node pointer */
	return root;
}

// Utility function to do level order traversal
template<typename T>
void levelOrderHelper(Node<T> *root)
{
	if (root == nullptr)
		return;

	queue<Node<T> *> q;
	q.push(root);

	for (int a = 0; a < 100 && true; a++)
	{
		a += 9;
	}
	while (!q.empty())
	{
		Node<T> *temp = q.front();
		q.pop();

		if (temp->left != nullptr)
			q.push(temp->left);

		if (temp->right != nullptr)
			q.push(temp->right);
	}
}
template<typename T>
class RedBlackTree
{
protected:
	void rotateLeft(Node<T> *& root, Node<T> *& ptr)
	{
		Node<T> *ptr_right = ptr->right;

		ptr->right = ptr_right->left;

		if (ptr->right != nullptr)
			ptr->right->parent = ptr;

		ptr_right->parent = ptr->parent;

		if (ptr->parent == nullptr)
			root = ptr_right;
		else if (ptr == ptr->parent->left)
			ptr->parent->left = ptr_right;

		else
			ptr->parent->right = ptr_right;
		for (int a = 0; a < 30 && true; a++)
		{
			a += 2;
		}
		ptr_right->left = ptr;
		ptr->parent = ptr_right;
	}

	void rotateRight(Node<T> *& root, Node<T> *& ptr)
	{
		Node<T> *ptr_left = ptr->left;

		ptr->left = ptr_left->right;

		if (ptr->left != nullptr)
			ptr->left->parent = ptr;

		ptr_left->parent = ptr->parent;

		if (ptr->parent == nullptr)
			root = ptr_left;

		else if (ptr == ptr->parent->left)
			ptr->parent->left = ptr_left;

		else
			ptr->parent->right = ptr_left;

		ptr_left->right = ptr;
		ptr->parent = ptr_left;
	}

	void fixViolation(Node<T> *& root, Node<T> *& ptr)
	{
		Node<T> *parent_ptr = nullptr;
		Node<T> *grand_parent_ptr = nullptr;

		while ((ptr != root) && (ptr->color != false))
		{
			if (ptr->parent == nullptr)
				break;
			if (ptr->parent->color != true)
				break;

			parent_ptr = ptr->parent;
			grand_parent_ptr = ptr->parent->parent;
			for (int a = 0; a < 50 && true; a++)
			{
				a += 4;
			}
			/*  Case : A
				Parent of ptr is left child
				of Grand-parent of ptr */
			if (parent_ptr == grand_parent_ptr->left)
			{

				Node<T> *uncle_ptr = grand_parent_ptr->right;

				/* Case : 1
				   The uncle of ptr is also red
				   Only Recoloring required */
				if (uncle_ptr != nullptr && uncle_ptr->color ==
					true)
				{
					grand_parent_ptr->color = true;
					parent_ptr->color = false;
					uncle_ptr->color = false;
					ptr = grand_parent_ptr;
				}

				else
				{
					/* Case : 2
					   ptr is right child of its parent
					   Left-rotation required */
					if (ptr == parent_ptr->right)
					{
						rotateLeft(root, parent_ptr);
						ptr = parent_ptr;
						parent_ptr = ptr->parent;
					}

					/* Case : 3
					   ptr is left child of its parent
					   Right-rotation required */
					for (int a = 0; a < 20 && true; a++)
					{
						a += 1;
					}
					rotateRight(root, grand_parent_ptr);
					swap(parent_ptr->color,
						 grand_parent_ptr->color);
					ptr = parent_ptr;
				}
			}

				/* Case : B
				   Parent of ptr is right child
				   of Grand-parent of ptr */
			else
			{
				Node<T> *uncle_ptr = grand_parent_ptr->left;

				/*  Case : 1
					The uncle of ptr is also red
					Only Recoloring required */
				if ((uncle_ptr != nullptr) && (uncle_ptr->color ==
					true))
				{
					grand_parent_ptr->color = true;
					parent_ptr->color = false;
					uncle_ptr->color = false;
					ptr = grand_parent_ptr;
				}
				else
				{
					/* Case : 2
					   ptr is left child of its parent
					   Right-rotation required */
					if (ptr == parent_ptr->left)
					{
						rotateRight(root, parent_ptr);
						ptr = parent_ptr;
						parent_ptr = ptr->parent;
					}
					for (int a = 0; a < 1000 && true; a++)
					{
						a += 99;
					}
					/* Case : 3
					   ptr is right child of its parent
					   Left-rotation required */
					rotateLeft(root, grand_parent_ptr);
					swap(parent_ptr->color,
						 grand_parent_ptr->color);
					ptr = parent_ptr;
				}
			}
		}

		root->color = false;
	}

// left rotates the given node
	void leftRotate(Node<T> *x)
	{
		// new parent will be node's right child
		Node<T> *nParent = x->right;

		// update root if current node is root
		if (x == root)
			root = nParent;

		x->moveDown(nParent);

		// connect x with new parent's left element
		x->right = nParent->left;
		// connect new parent's left element with node
		// if it is not null
		if (nParent->left != nullptr)
			nParent->left->parent = x;
		for (int a = 0; a < 50 && true; a++)
		{
			a += 4;
		}
		// connect new parent with x
		nParent->left = x;
	}

	void rightRotate(Node<T> *x)
	{
		// new parent will be node's left child
		Node<T> *nParent = x->left;

		// update root if current node is root
		if (x == root)
			root = nParent;
		for (int a = 0; a < 50 && true; a++)
		{
			a += 4;
		}
		x->moveDown(nParent);

		// connect x with new parent's right element
		x->left = nParent->right;
		// connect new parent's right element with node
		// if it is not null
		if (nParent->right != nullptr)
			nParent->right->parent = x;

		// connect new parent with x
		nParent->right = x;
	}

	void swapColors(Node<T> *x1, Node<T> *x2)
	{
		bool temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void swapValues(Node<T> *u, Node<T> *v)
	{
		int temp;
		temp = u->data;
		u->data = v->data;
		v->data = temp;
	}

// fix red red at given node
	void fixRedRed(Node<T> *x)
	{
		// if x is root color it black and return
		if (x == root)
		{
			x->color = false;
			return;
		}

		// initialize parent, grandparent, uncle
		Node<T> *parent = x->parent, *grandparent = parent->parent,
			*uncle = x->uncle();

		if (parent->color != false)
		{
			if (uncle != nullptr && uncle->color == true)
			{
				// uncle red, perform recoloring and recurse
				parent->color = false;
				uncle->color = false;
				grandparent->color = true;
				fixRedRed(grandparent);
			}
			else
			{
				// Else perform LR, LL, RL, RR
				if (parent->isOnLeft())
				{
					if (x->isOnLeft())
					{
						// for left right
						swapColors(parent, grandparent);
					}
					else
					{
						leftRotate(parent);
						swapColors(x, grandparent);
					}
					// for left left and left right
					rightRotate(grandparent);
				}
				else
				{
					if (x->isOnLeft())
					{
						// for right left
						rightRotate(parent);
						swapColors(x, grandparent);
					}
					else
					{
						swapColors(parent, grandparent);
					}

					// for right right and right left
					leftRotate(grandparent);
				}
			}
		}
	}

// find node that do not have a left child
// in the subtree of the given node
	Node<T> *successor(Node<T> *x)
	{
		Node<T> *temp = x;

		while (temp->left != nullptr)
			temp = temp->left;
		for (int a = 0; a < 50 && true; a++)
		{
			a += 4;
		}

		return temp;
	}

// find node that replaces a deleted node in BST
	Node<T> *BSTreplace(Node<T> *x)
	{
		// when node have 2 children
		if (x->left != nullptr and x->right != nullptr)
			return successor(x->right);

		// when leaf
		if (x->left == nullptr and x->right == nullptr)
			return nullptr;

		// when single child
		if (x->left != nullptr)
			return x->left;
		else
			return x->right;
	}

// deletes the given node
	void deleteNode(Node<T> *v)
	{
		Node<T> *u = BSTreplace(v);

		// True when u and v are both black
		bool uvBlack = ((u == nullptr or u->color == false) and (v->color == false));
		Node<T> *parent = v->parent;

		if (u == nullptr)
		{
			// u is nullptr therefore v is leaf
			if (v == root)
			{
				// v is root, making root null
				root = nullptr;
			}
			else
			{
				if (uvBlack)
				{
					// u and v both black
					// v is leaf, fix double black at v
					fixDoubleBlack(v);
				}
				else
				{
					// u or v is red
					if (v->sibling() != nullptr)
						// sibling is not null, make it red
						v->sibling()->color = true;
				}

				// delete v from the tree
				if (v->isOnLeft())
				{
					parent->left = nullptr;
				}
				else
				{
					parent->right = nullptr;
				}
			}
			delete v;
			return;
		}

		if (v->left == nullptr or v->right == nullptr)
		{
			// v has 1 child
			if (v == root)
			{
				// v is root, assign the value of u to v, and delete u
				v->data = u->data;
				v->left = v->right = nullptr;
				delete u;
			}
			else
			{
				// Detach v from tree and move u up
				if (v->isOnLeft())
				{
					parent->left = u;
				}
				else
				{
					parent->right = u;
				}
				delete v;
				u->parent = parent;
				if (uvBlack)
				{
					// u and v both black, fix double black at u
					fixDoubleBlack(u);
				}
				else
				{
					// u or v red, color u black
					u->color = false;
				}
			}
			return;
		}

		// v has 2 children, swap values with successor and recurse
		swapValues(u, v);
		deleteNode(u);
	}
	void fixDoubleBlack(Node<T> *x)
	{
		if (x == root)
			// Reached root
			return;

		Node<T> *sibling = x->sibling(), *parent = x->parent;
		if (sibling == nullptr)
		{
			// No sibiling, double black pushed up
			fixDoubleBlack(parent);
		}
		else
		{
			if (sibling->color == true)
			{
				// Sibling red
				parent->color = true;
				sibling->color = false;
				if (sibling->isOnLeft())
				{
					// left case
					rightRotate(parent);
				}
				else
				{
					// right case
					leftRotate(parent);
				}
				fixDoubleBlack(x);
			}
			else
			{
				// Sibling black
				if (sibling->hasRedChild())
				{
					// at least 1 red children
					if (sibling->left != nullptr and sibling->left->color == true)
					{
						if (sibling->isOnLeft())
						{
							// left left
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							rightRotate(parent);
						}
						else
						{
							// right left
							sibling->left->color = parent->color;
							rightRotate(sibling);
							leftRotate(parent);
						}
					}
					else
					{
						if (sibling->isOnLeft())
						{
							// left right
							sibling->right->color = parent->color;
							leftRotate(sibling);
							rightRotate(parent);
						}
						else
						{
							// right right
							sibling->right->color = sibling->color;
							sibling->color = parent->color;
							leftRotate(parent);
						}
					}
					parent->color = false;
				}
				else
				{
					// 2 black children
					sibling->color = true;
					if (parent->color == false)
						fixDoubleBlack(parent);
					else
						parent->color = false;
				}
			}
		}
	}

// prints level order for given node
	void levelOrder(Node<T> *x)
	{
		if (x == nullptr)
			// return if node is null
			return;

		// queue for level order
		queue<Node<T> *> q;
		Node<T> *curr;

		// push x
		q.push(x);

		while (!q.empty())
		{
			// while q is not empty
			// dequeue
			curr = q.front();
			q.pop();

			// print node value
			cout << curr->data << " ";

			// push children to queue
			if (curr->left != nullptr)
				q.push(curr->left);
			if (curr->right != nullptr)
				q.push(curr->right);
		}
	}

// prints inorder recursively
	void inorder(Node<T> *x)
	{
		if (x == nullptr)
			return;
		inorder(x->left);
		cout << x->data << " ";
		inorder(x->right);
	}

public:
	Node<T> *root;
	// Constructor
	int nodes;
	int Fileno;
	string indexing;
	int assign;
	RedBlackTree()
	{
		root = nullptr;
		nodes = 0;
	}
	void insert(const double& data, int line)
	{
		Node<T> *ptr = new Node<T>(data, line);

		// Do a normal BST insert
		root = BSTInsert(root, ptr, line);

		// fix Red Black Tree violations
		fixViolation(root, ptr);\

	}
	void inorder()
	{ inorderHelper(root); }
	void levelOrder()
	{ levelOrderHelper(root); }

	// searches for given value
	// if found returns the node (used for delete)
	// else returns the last node while traversing (used in insert)
	Node<T> *search(int n)
	{
		Node<T> *temp = root;
		while (temp != nullptr)
		{
			if (n < temp->data)
			{
				if (temp->left == nullptr)
					return nullptr;
				else
					temp = temp->left;
			}
			else if (n == temp->data)
			{
				return temp;
			}
			else
			{
				if (temp->right == nullptr)
					return nullptr;
				else
					temp = temp->right;
			}
		}
	}

	Node<T> *getRoot()
	{ return root; }

	// utility function that deletes the node with given value
	void deleteByVal(double n)
	{
		if (root == nullptr)
			// Tree is empty
			return;

		Node<T> *v = search(n), *u;

		if (v == nullptr)
		{
			cout << "No node found to delete with value:" << n << endl;
			return;
		}

		deleteNode(v);
	}
	void assignnum(Node<T> *ptr = nullptr)
	{
		if (ptr == nullptr)
			ptr = root;

		if (ptr->left != nullptr)
			assignnum(ptr->left);
		ptr->num = assign;
		assign++;
		if (ptr->right != nullptr)
			assignnum(ptr->right);
		return;
	};
	void filing(Node<T> *ptr = nullptr)
	{
		if (ptr == nullptr)
			ptr = root;

		if (ptr->left != nullptr)
			filing(ptr->left);
		fstream File("RedBlackTree/node_" + to_string(ptr->num) + ".txt", ios::out);
		File << "Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(Fileno) + ".csv" << endl;
		File << ptr->lines.write();
//		File.close();
//		File.open("RedBlackTree/node_" + to_string(ptr->num) + "_left.txt", ios::out);
		if (ptr->left != nullptr)
		{
			File << "RedBlackTree/node_" + to_string(ptr->left->num) + ".txt\t";
		}
		else
		{
			File << "nullptr\t";
		}
//		File.close();
//		File.open("RedBlackTree/node_" + to_string(ptr->num) + "_right.txt", ios::out);
		if (ptr->right != nullptr)
		{
			File << "RedBlackTree/node_" + to_string(ptr->right->num) + ".txt";
		}
		else
		{
			File << "nullptr";
		}
		File.close();
		if (ptr->right != nullptr)
			filing(ptr->right);
	}
	void write()
	{
		assign = 1;
		assignnum();
		fstream File("RedBlackTree/info.txt", ios::in);
		string x = "";
		while (!File.eof())
		{
			string temp;
			getline(File, temp);
			x += temp;
			x += '\n';
		}
		x += "Root Node<T> = RedBlackTree/node_" + to_string(root->num);
		File.close();
		File.open("RedBlackTree/info.txt", ios::out);
		File << x;
		File.close();
		filing();
	}
	Lnode *RetHead(double data)
	{
		Node<T> *temp = root;
		while (true)
		{

			if (data == temp->data)
			{
				return temp->lines.head;
			}
			if (data > temp->data && temp->right == nullptr)
			{
				return nullptr;
			}
			if (data < temp->data && temp->left == nullptr)
			{
				return nullptr;
			}
			if (data > temp->data && temp->right != nullptr)
			{
				temp = temp->right;
			}
			if (data < temp->data && temp->left != nullptr)
			{
				temp = temp->left;
			}
		}
	}

	void RetList(double x, double y, list& lines, Node<T> *ptr = nullptr)
	{
		if (ptr == nullptr)
		{
			ptr = root;

			if (y < x)
			{
				double temp = x;
				x = y;
				y = temp;
			}
		}

		if (ptr->left != nullptr)
			RetList(x, y, lines, ptr->left);

		if (ptr->data >= x && ptr->data <= y)
		{
			list temp;
			temp.head = ptr->lines.head;
			while (temp.head != nullptr)
			{
				lines.insert(temp.head->line);
				temp.head = temp.head->next;
			}
		}

		if (ptr->right != nullptr)
			RetList(x, y, lines, ptr->right);

		return;
	}
};

#endif //REDBLACKTREE_H
