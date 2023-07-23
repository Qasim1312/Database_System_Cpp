
#ifndef DELETING_CPP
#define DELETING_CPP

#include "searching.cpp"
template<typename T>
void deleting(AVL<T>& tree1, RedBlackTree<T>& tree2)
{
	fstream File;
	string field, data;
	cout << "enter the field the data is from you want to remove" << endl;
	getline(cin, field);

	cout << "enter the data you want to remove" << endl;
	getline(cin, data);
	bool del = false;
	if (tree1.indexing == field)
	{
		if (!del)
		{
			File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree1.Fileno) + ".csv",
					  ios::in);
			list x;
			if (isNum(data))
			{
				if (isInt(data))
					x.head = tree1.RetHead((double)toInt(data));
				else
					x.head = tree1.RetHead(toDouble(data));
			}
			else
			{
				Lowercase(data);
				x.head = tree1.RetHead(strEncode(data));
			}
			string newfile = "", g;
			int lineno = 1;
			while (!File.eof())
			{
				if (lineno == x.head->line)
				{
					string t;
					getline(File, t);
					x.head = x.head->next;
				}
				else
				{
					getline(File, g);
					newfile = newfile + g + '\n';
				}
			}
			File.close();
			File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree1.Fileno) + ".csv",
					  ios::out);
			File << newfile << endl;
			File.close();
			del = true;
		}

	}
	if (tree2.indexing == field)
	{
		if (!del)
		{
			File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree2.Fileno) + ".csv",
					  ios::in);
			list x;
			if (isNum(data))
			{
				if (isInt(data))
					x.head = tree2.RetHead((double)toInt(data));
				else
					x.head = tree2.RetHead(toDouble(data));
			}
			else
			{
				Lowercase(data);
				x.head = tree2.RetHead(strEncode(data));
			}
			string newfile, g;
			int lineno = 1;
			while (!File.eof())
			{
				if (lineno == x.head->line)
				{
					string t;
					getline(File, t);
					x.head = x.head->next;
				}
				else
				{
					getline(File, g);
					newfile = newfile + g + '\n';
				}
			}
			File.close();
			File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree1.Fileno) + ".csv",
					  ios::out);
			File << newfile << endl;
			File.close();
			del = true;
		}

	}
	removeAll("AVLTree/node");
	remove("AVLTree/info.txt");
	File.open("AVLTree/info.txt", fstream::out);
	File << tree1.indexing << endl;
	File.close();
	File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree1.Fileno) + ".csv",
			  ios::in);
	string temp;
	int skip = 0;
	while (getline(File, temp, ','))
	{
		Lowercase(temp);
		if (temp == tree1.indexing)
			break;
		skip++;
	}
	File.close();
	File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree1.Fileno) + ".csv",
			  ios::in);
	getline(File, temp);
	int line = 1;
	temp = "temp";
	while (!File.eof())
	{
		line++;
		for (int a = 0; a < skip; a++)
		{
			getline(File, temp, ',');
			if (temp == "")
				break;
			if (temp[0] == '\"')
			{
				string x;
				getline(File, x, '\"');
				temp += x;
				char z;
				File >> z;
			}
		}
		if (temp != "")
			getline(File, temp);
		if (temp[0] == '\"')
		{
			string x;
			for (int a = 0; temp[a]; a++)
			{
				x += temp[a];
				if (temp[a] == '\"')
					break;
			}
			temp = x;
		}
		if (temp == "")
			continue;
		string data = "";
		for (int a = 0; temp[a]; a++)
		{
			if (temp[a] == ',' || temp[a] == '\n')
				break;
			data += temp[a];
		}

		if (isNum(data))
		{
			if (isInt(data))
			{
				Lowercase(data);
				TreeNode<T> *x = new TreeNode((double)toInt(data));
				x->lines.head = new Lnode(line);
				tree1.root = tree1.insert(tree1.root, x);
			}
			else
			{
				Lowercase(data);
				TreeNode<T> *x = new TreeNode(toDouble(data));
				x->lines.head = new Lnode(line);
				tree1.root = tree1.insert(tree1.root, x);
			}
		}
		else
		{
			Lowercase(data);
			TreeNode<T> *x = new TreeNode(strEncode(data));
			x->lines.head = new Lnode(line);
			tree1.root = tree1.insert(tree1.root, x);
		}

	}
	tree1.write();
	File.close();


	removeAll("RedBlackTree/node");
	remove("RedBlackTree/info.txt");
	File.open("RedBlackTree/info.txt", fstream::out);
	File << tree2.indexing << endl;
	File.close();
	File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree2.Fileno) + ".csv",
			  ios::in);
	temp = "";
	skip = 0;
	while (getline(File, temp, ','))
	{
		Lowercase(temp);
		if (temp == tree2.indexing)
			break;
		skip++;
	}
	File.close();
	File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree2.Fileno) + ".csv",
			  ios::in);
	getline(File, temp);
	line = 1;
	temp = "temp";
	while (!File.eof())
	{
		line++;
		for (int a = 0; a < skip; a++)
		{
			getline(File, temp, ',');
			if (temp == "")
				break;
			if (temp[0] == '\"')
			{
				string x;
				getline(File, x, '\"');
				temp += x;
				char z;
				File >> z;
			}
		}
		if (temp != "")
			getline(File, temp);
		if (temp[0] == '\"')
		{
			string x;
			for (int a = 0; temp[a]; a++)
			{
				x += temp[a];
				if (temp[a] == '\"')
					break;
			}
			temp = x;
		}
		if (temp == "")
			continue;
		string data = "";
		for (int a = 0; temp[a]; a++)
		{
			if (temp[a] == ',' || temp[a] == '\n')
				break;
			data += temp[a];
		}

		if (isNum(data))
		{
			if (isInt(data))
			{
				tree2.insert((double)toInt(data), line);
			}
			else
			{
				tree2.insert(toDouble(data), line);
			}
		}
		else
		{
			Lowercase(data);
			tree2.insert(strEncode(data), line);
		}

//								tree2.insert(data, line);
	}

	tree2.write();
	File.close();
}


#endif //DELETING_CPP
