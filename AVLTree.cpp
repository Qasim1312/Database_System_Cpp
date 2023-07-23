#ifndef AVLTREE_CPP
#define AVLTREE_CPP

#include<iostream>
#include <queue>
using namespace std;

template<typename T>
class TreeNode
{
public:
	T value;
	int num;
	TreeNode *left;
	TreeNode *right;
	list lines;

	TreeNode()
	{
		value = 0;
		left = nullptr;
		num = -1;
		right = nullptr;
	}
	TreeNode(T v)
	{
		value = v;
		left = nullptr;
		num = -1;
		right = nullptr;
	}
};
template<typename T>
class AVL
{
public:

	string indexing;
	TreeNode<T> *root;
	AVL()
	{
		root = nullptr;
	}
	bool isTreeEmpty()
	{
		if (root == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int getBalanceFactor(TreeNode<T> *n)
	{
		if (n == nullptr)
			return -1;
		return height(n->left) - height(n->right);
	}

	TreeNode<T> *rightRotate(TreeNode<T> *y)
	{
		TreeNode<T> *x = y->left;
		TreeNode<T> *T2 = x->right;

		// Perform rotation
		x->right = y;
		y->left = T2;

		return x;
	}

	TreeNode<T> *leftRotate(TreeNode<T> *x)
	{
		TreeNode<T> *y = x->right;
		TreeNode<T> *T2 = y->left;

		// Perform rotation
		y->left = x;
		x->right = T2;

		return y;
	}

	void printPreorder(TreeNode<T> *r)
	{
		if (r == nullptr)
		{
			return;
		}

		cout << r->value << " ";

		printPreorder(r->left);

		printPreorder(r->right);
	}

	void printInorder(TreeNode<T> *r) //  (Left, current node, Right)
	{
		if (r == nullptr)
		{
			return;
		}

		printInorder(r->left);

		cout << r->value << " ";

		printInorder(r->right);
	}
	void printPostorder(TreeNode<T> *r) //(Left, Right, Root)
	{
		if (r == nullptr)
		{
			return;
		}

		printPostorder(r->left);

		printPostorder(r->right);

		cout << r->value << " ";
	}

	TreeNode<T> *iterativeSearch(double v)
	{
		if (root == nullptr)
		{
			return root;
		}
		else
		{
			TreeNode<T> *temp = root;
			while (temp != nullptr)
			{
				if (v == temp->value)
				{
					return temp;
				}
				else if (v < temp->value)
				{
					temp = temp->left;
				}
				else
				{
					temp = temp->right;
				}
			}
			return nullptr;
		}
	}

	void printLevelOrder(TreeNode<T> *root)
	{
		if (root == nullptr)
		{
			return;
		}
		queue<TreeNode<T> *> q;
		q.push(root);
		while (q.empty() == false)
		{
			TreeNode<T> *temp = q.front();
			cout << temp->value << " ";
			q.pop();
			if (temp->left != nullptr)
				q.push(temp->left);
			if (temp->right != nullptr)
				q.push(temp->right);
		}
	}
	int height(TreeNode<T> *r)
	{
		if (r == nullptr)
			return -1;
		else
		{
			int lheight = height(r->left);
			int rheight = height(r->right);
			if (lheight > rheight)
				return (lheight + 1);
			else return (rheight + 1);
		}
	}
	TreeNode<T> *recursiveSearch(TreeNode<T> *r, double val)
	{
		if (r == nullptr || r->value == val)
			return r;

		else if (val < r->value)
			return recursiveSearch(r->left, val);

		else
			return recursiveSearch(r->right, val);
	}

	TreeNode<T> *insert(TreeNode<T> *r, TreeNode<T> *new_node)
	{
		int counter = 0;
		if (r == nullptr)
		{
			r = new_node;
			return r;
		}
		for (int i = 0; i < 5; i++)
		{
			counter++;
		}
		if (new_node->value < r->value)
		{
			r->left = insert(r->left, new_node);
		}

		else if (new_node->value > r->value)
		{
			r->right = insert(r->right, new_node);
		}
		else
		{
			r->lines.insert(new_node->lines.head->line);
			delete new_node;
			return r;
		}
		for (int i = 0; i < 5; i++)
		{
			counter++;
		}
		int bf = getBalanceFactor(r);
		// Left Left Case
		if (bf > 1)
		{
			if (new_node->value < r->left->value)
			{
				return rightRotate(r);
			}
		}

		// Right Right Case
		if (bf < -1)
		{
			if (new_node->value > r->right->value)
			{
				return leftRotate(r);
			}
		}

		// Left Right Case
		if (bf > 1)
		{
			if (new_node->value > r->left->value)
			{
				r->left = leftRotate(r->left);
				return rightRotate(r);
			}
		}

		// Right Left Case
		if (bf < -1)
		{
			if (new_node->value < r->right->value)
			{
				r->right = rightRotate(r->right);
				return leftRotate(r);
			}
		}

		/* return the (unchanged) node pointer */
		return r;

	}
	TreeNode<T> *minValueNode(TreeNode<T> *node)
	{
		TreeNode<T> *current = node;
		while (current->left != nullptr)
		{
			current = current->left;
		}
		return current;
	}

	TreeNode<T> *deleteNode(TreeNode<T> *r, double v)
	{
		int c = 0;
		bool check = true;
		// base case
		if (r == nullptr)
		{
			return nullptr;
		}

			// If the key to be deleted is smaller than the root's key,
			// then it lies in left subtree
		else if (v < r->value && check == true)
		{
			r->left = deleteNode(r->left, v);
		}
			// If the key to be deleted is greater than the root's key,
			// then it lies in right subtree
		else if (v > r->value)
		{
			r->right = deleteNode(r->right, v);
		}
			// if key is same as root's key, then This is the node to be deleted
		else
		{
			// node with only one child or no child
			if (r->left == nullptr && check == true)
			{
				TreeNode<T> *temp = r->right;
				delete r;
				return temp;
			}
			else if (r->right == nullptr)
			{
				TreeNode<T> *temp = r->left;
				delete r;
				return temp;
			}
			else
			{
				// node with two children: Get the inorder successor (smallest
				// in the right subtree)
				TreeNode<T> *temp = minValueNode(r->right);
				// Copy the inorder successor's content to this node
				r->value = temp->value;
				// Delete the inorder successor
				r->right = deleteNode(r->right, temp->value);
				//deleteNode(r->right, temp->value);
			}
		}
		for (int i = 0; i < 5; i++)
		{
			c++;
		}
		int bf = getBalanceFactor(r);

		// Left Left Imbalance/Case or Right rotation

		if (bf == 2)
		{
			if (getBalanceFactor(r->left) >= 0)
				return rightRotate(r);
		}

			// Left Right Imbalance/Case or LR rotation

		else if (bf == 2)
		{
			if (getBalanceFactor(r->left) == -1)
			{
				r->left = leftRotate(r->left);
				return rightRotate(r);
			}
		}
			// Right Right Imbalance/Case or Left rotation
		else if (bf == -2)
		{
			if (getBalanceFactor(r->right) <= -0)
			{
				return leftRotate(r);
			}
		}
			// Right Left Imbalance/Case or RL rotation
		else if (bf == -2 && check)
		{
			if (getBalanceFactor(r->right) == 1)
			{
				r->right = rightRotate(r->right);
				return leftRotate(r);
			}
		}

		return r;
	}
	int assign;
	int Fileno;
	// assignes each node a unique number
	void assignnum(TreeNode<T> *ptr = nullptr)
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
	// writes each node into the form of a file
	void filing(TreeNode<T> *ptr = nullptr)
	{
		if (ptr == nullptr)
			ptr = root;

		if (ptr->left != nullptr)
			filing(ptr->left);
		fstream File("AVLTree/node_" + to_string(ptr->num) + ".txt", ios::out);
		File << "Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(Fileno) + ".csv" << endl;
		File << ptr->lines.write();
//		File.close();
//		File.open("RedBlackTree/node_" + to_string(ptr->num) + "_left.txt", ios::out);
		if (ptr->left != nullptr)
		{
			File << "AVLTree/node_" + to_string(ptr->left->num) + ".txt\t";
		}
		else
		{
			File << "nullptr\t";
		}
//		File.close();
//		File.open("RedBlackTree/node_" + to_string(ptr->num) + "_right.txt", ios::out);
		if (ptr->right != nullptr)
		{
			File << "AVLTree/node_" + to_string(ptr->right->num) + ".txt";
		}
		else
		{
			File << "nullptr";
		}
		File.close();
		if (ptr->right != nullptr)
			filing(ptr->right);
	}
	// writes the tree into file form
	void write()
	{
		assign = 1;
		assignnum();
		fstream File("AVLTree/info.txt", ios::in);
		string x = "";
		while (!File.eof())
		{
			string temp;
			getline(File, temp);
			x += temp;
			x += '\n';
		}
		x += "Root Node = AVLTree/node_" + to_string(root->num);
		File.close();
		File.open("AVLTree/info.txt", ios::out);
		File << x;
		File.close();
		filing();
	}

	// returns the head node of searched data's list of lines
	Lnode *RetHead(double data)
	{
		TreeNode<T> *temp = root;
		while (true)
		{

			if (data == temp->value)
			{
				return temp->lines.head;
			}
			if (data > temp->value && temp->right == nullptr)
			{
				return nullptr;
			}
			if (data < temp->value && temp->left == nullptr)
			{
				return nullptr;
			}
			if (data > temp->value && temp->right != nullptr)
			{
				temp = temp->right;
			}
			if (data < temp->value && temp->left != nullptr)
			{
				temp = temp->left;
			}
		}
	}

	void RetList(double x, double y, list& lines1, TreeNode<T> *ptr = nullptr)
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
			RetList(x, y, lines1, ptr->left);
		if (ptr->value >= x && ptr->value <= y)
		{
			list temp;
			temp.head = ptr->lines.head;
			while (temp.head != nullptr)
			{
				lines1.insert(temp.head->line);
				temp.head = temp.head->next;
			}
		}
		if (ptr->right != nullptr)
			RetList(x, y, lines1, ptr->right);

		return;
	}

};


#endif //AVLTREE_CPP
