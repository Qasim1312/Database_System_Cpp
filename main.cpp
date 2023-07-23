#include "deleting.cpp"
void clear();
template<typename T>
void menu(AVL<T>&, RedBlackTree<T>&);
int main()
{
	AVL<double> tree1; // AVL tree root
	RedBlackTree<double> tree2; // Red Black tree object

	menu(tree1, tree2);
	return 0;
}
template<typename T>
void menu(AVL<T>& tree1, RedBlackTree<T>& tree2)
{
	while (true)
	{
		clear();
		cout << ":::::::::::::::::::::::::::::::" << endl;
		cout << ":::: Hello welcome to DSDB ::::" << endl;
		cout << ":::::::::::::::::::::::::::::::" << endl;
		cout << endl;
		cout << endl;
		cout << "Enter \"create index\" to start indexing" << endl;
		cout << "Enter \"point search\" to search related data from data set" << endl;
		cout << "Enter \"range search\" to start ranged search of data set" << endl;
		cout << "Enter \"delete key\" to delete tuple from data set" << endl;
		string statement;
		getline(cin, statement);
		Lowercase(statement);
		if (statement == "create index")
		{
			indexing(tree1, tree2);
		}
		if (statement == "point search")
		{
			pointSearch(tree1, tree2);
		}
		if (statement == "range search")
		{
			rangeSearch(tree1, tree2);
		}
		if (statement == "delete key")
		{
			deleting(tree1, tree2);
		}
		else if (statement == "exit")
		{
			clear();
			cout << "Thank you for using our program Good Bye" << endl;
			break;
		}
	}

}