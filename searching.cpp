
#ifndef SEARCHING_CPP
#define SEARCHING_CPP

#include "indexing.cpp"
template<typename T>
void pointSearch(AVL<T>& tree1, RedBlackTree<T>& tree2)
{
	string section, tuple, filenum;

	cout << "enter the section you want to search" << endl;
	getline(cin, section);
	Lowercase(section);
	if (section == "id" || section == "year" || section == "id" || section == "113 cause name"
		|| section == "cause name" || section == "state" || section == "deaths"
		|| section == "age-adjusted death rate")
	{
		cout << "enter the tuple you want to search" << endl;
		getline(cin, tuple);
		Lowercase(tuple);
		list lines1, lines2;
		fstream File;
		if (isNum(tuple))
		{
			if (isInt(tuple))
			{
				if (tree1.indexing == section)
					lines1.head = tree1.RetHead((double)toInt(tuple));
				if (tree2.indexing == section)
					lines2.head = tree2.RetHead((double)toInt(tuple));
			}
			else
			{
				if (tree1.indexing == section)
					lines1.head = tree1.RetHead(toDouble(tuple));
				if (tree2.indexing == section)
					lines2.head = tree2.RetHead(toDouble(tuple));
			}
		}
		else
		{
			if (tree1.indexing == section)
				lines1.head = tree1.RetHead(strEncode(tuple));
			if (tree2.indexing == section)
				lines2.head = tree2.RetHead(strEncode(tuple));
		}
		if (lines1.head != nullptr)
		{
			cout << endl;
			cout << "::DATA IN AVL TREE::" << endl;
			cout << endl;

			File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree2.Fileno) + ".csv", ios::in);
			if (File.fail())
			{ return; }
			int lineno = 2;
			string temp;
			getline(File, temp);
			while (!File.eof())
			{
				getline(File, temp);
				if (lines1.head != nullptr)
				{
					if (lineno == lines1.head->line)
					{
						cout << temp << endl;
						lines1.head = lines1.head->next;
					}
				}
				lineno++;
			}
			File.close();
		}
		else
		{
			cout << "No such data found in avl tree" << endl;
		}
		if (lines2.head != nullptr)
		{
			cout << endl;
			cout << "::DATA IN RED BLACK TREE::" << endl;
			cout << endl;

			File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree2.Fileno) + ".csv", ios::in);
			if (File.fail())
			{ return; }
			int lineno = 2;
			string temp;
			getline(File, temp);
			while (!File.eof())
			{
				getline(File, temp);
				if (lines2.head != nullptr)
				{
					if (lineno == lines2.head->line)
					{
						cout << temp << endl;
						lines2.head = lines2.head->next;
					}
				}
				lineno++;
			}
			File.close();
		}
		else
		{
			cout << "No such data found in red black tree" << endl;
		}
		cout << "give any input to exit to menu" << endl;
		getline(cin, tuple);
	}
}
template<typename T>
void rangeSearch(AVL<T>& tree1, RedBlackTree<T>& tree2)
{
	string section, tupleStart, tupleEnd;
	fstream File;
	cout << "enter the section you want to search" << endl;
	getline(cin, section);
	Lowercase(section);
	if (section == "id" || section == "year" || section == "id" || section == "113 cause name"
		|| section == "cause name" || section == "state" || section == "deaths"
		|| section == "age-adjusted death rate")
	{
		cout << "enter the minimum tuple you want to search" << endl;
		getline(cin, tupleStart);

		cout << "enter the maximum tuple you want to search" << endl;
		getline(cin, tupleEnd);

		if (tree1.indexing == section)
		{
			list lines;
			double x, y;
			if (isNum(tupleStart))
			{
				if (isInt(tupleStart))
					x = (double)toInt(tupleStart);
				else
					x = toDouble(tupleStart);
			}
			else
			{
				Lowercase(tupleStart);
				x = strEncode(tupleStart);
			}
			if (isNum(tupleEnd))
			{
				if (isInt(tupleEnd))
					y = (double)toInt(tupleEnd);
				else
					y = toDouble(tupleEnd);
			}
			else
			{
				Lowercase(tupleEnd);
				y = strEncode(tupleEnd);
			}
			tree1.RetList(x, y, lines);
			if (lines.head != nullptr)
			{
				cout << endl;
				cout << "::DATA IN AVL TREE::" << endl;
				cout << endl;

				File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree1.Fileno) + ".csv",
						  ios::in);
				if (File.fail())
				{ return; }
				int lineno = 2;
				string temp;
				getline(File, temp);
				while (!File.eof())
				{
					getline(File, temp);
					if (lines.head != nullptr)
					{
						Lnode *x = lines.head;
						while (x != nullptr)
						{
							if (x->line == lineno)
								cout << temp << endl;
							x = x->next;
						}
					}
					lineno++;
				}
				File.close();
			}
			else
			{
				cout << "No such data found in avl tree" << endl;
			}
		}

		if (tree2.indexing == section)
		{
			list lines;
			double x, y;
			if (isNum(tupleStart))
			{
				if (isInt(tupleStart))
					x = (double)toInt(tupleStart);
				else
					x = toDouble(tupleStart);
			}
			else
			{
				Lowercase(tupleStart);
				x = strEncode(tupleStart);
			}
			if (isNum(tupleEnd))
			{
				if (isInt(tupleEnd))
					y = (double)toInt(tupleEnd);
				else
					y = toDouble(tupleEnd);
			}
			else
			{
				Lowercase(tupleEnd);
				y = strEncode(tupleEnd);
			}
			tree2.RetList(x, y, lines);
			if (lines.head != nullptr)
			{
				cout << endl;
				cout << "::DATA IN RED BLACK TREE::" << endl;
				cout << endl;

				File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + to_string(tree2.Fileno) + ".csv",
						  ios::in);
				if (File.fail())
				{ return; }
				int lineno = 2;
				string temp;
				getline(File, temp);
				while (!File.eof())
				{
					getline(File, temp);
					if (lines.head != nullptr)
					{
						Lnode *x = lines.head;
						while (x != nullptr)
						{
							if (x->line == lineno)
								cout << temp << endl;
							x = x->next;
						}
					}
					lineno++;
				}
				File.close();
			}
			else
			{
				cout << "No such data found in Red Black tree" << endl;
			}
		}
		cout << "Enter any Key to exit back to the menu" << endl;
		getline(cin, tupleStart);
	}

}

#endif //SEARCHING_CPP
