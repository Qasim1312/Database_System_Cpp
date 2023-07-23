

#ifndef INDEXING_CPP
#define INDEXING_CPP

#include "Fileing.cpp"
#include "RedBlackTree.cpp"
#include "AVLTree.cpp"
#include <iostream>
#include <string>
using namespace std;

void clear()
{
	for (int a = 0; a < 100; a++)
		cout << endl;
}

void Lowercase(string& x)
{
	for (int a = 0; x[a]; a++)
		if (x[a] >= 'A' && x[a] <= 'Z')
			x[a] = x[a] - 'A' + 'a';
}

// returns true if the string holds integer value
bool isInt(string statement)
{
	for (int a = 0; statement[a]; a++)
	{
		if (statement[a] < '0' || statement[a] > '9')
			return false;
	}
	return true;
}
// returns integer equivilant of string
int toInt(string data)
{
	int x = 0;
	for (int a = 0; data[a]; a++)
	{
		x *= 10;
		x += data[a] - '0';
	}
	return x;
}

// returns double equivilant of string
double toDouble(string data)
{
	double x = 0;
	int diviser = 0;
	bool dot = false;
	for (int a = 0; data[a]; a++)
	{
		if (data[a] == '.')
		{
			dot = !dot;
			continue;
		}
		x *= 10;
		x += data[a] - '0';
		if (dot)
			diviser++;
	}
	if (diviser > 0)
	{
		x = x / (10 * diviser);
	}
	return x;
}

// returns double value by encoding the data in string via a specific formula
double strEncode(string data)
{
	double x = 0;
	for (int a = 0; data[a]; a++)
	{
		x *= 1.1;
		x += ((data[a] % 26) * (a + 1));
	}
	return x;
}

// returns true if the string holds numaric value
bool isNum(string statement)
{
	for (int a = 0; statement[a]; a++)
	{
		if (statement[a] < '0' || statement[a] > '9' || statement[a] != '.')
			return false;
	}
	return true;
}
template<typename T>
void indexing(AVL<T>& tree1, RedBlackTree<T>& tree2)
{
	string statement;
	bool check[3] = {false, false, false};
	while (true)
	{
		clear();
		cout << "Enter \"insert\" to enter the data or enter numbers 1 to 3 to select which tree to enter in" << endl;
		cout << "1::   [" << ((check[0]) ? ('X') : (' ')) << "]\t AVL Tree" << endl;
		cout << "2::   [" << ((check[1]) ? ('X') : (' ')) << "]\t Red and Black Tree" << endl;
		cout << "3::   [" << ((check[2]) ? ('X') : (' ')) << "]\t B Tree" << endl;
		getline(cin, statement);
		Lowercase(statement);
		if (statement == "insert")
		{
			clear();
			cout << "Enter which field you want to insert e.g; id, state, etc" << endl;
			getline(cin, statement);
			Lowercase(statement);
			if (statement == "id" || statement == "year" || statement == "id" || statement == "113 cause name"
				|| statement == "cause name" || statement == "state" || statement == "deaths"
				|| statement == "age-adjusted death rate")
			{

				fstream File;
				string filenum;
				cout << "Enter which file number you want to open : ";
				getline(cin, filenum);
				if (isInt(filenum))
				{
					File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + filenum + ".csv", ios::in);
					if (File.fail())
					{
						cout << "File Failed to Load" << endl;
						return;
					}
					else
					{
						File.close();
						if (check[0])
						{
							tree1.indexing = statement;
							tree1.Fileno = toInt(filenum);
							if (!hasPath("AVLTree"))
							{
								createFolder("AVLTree");
							}
							removeAll("AVLTree/node");
							remove("AVLTree/info.txt");
							File.open("AVLTree/info.txt", fstream::out);
							File << tree1.indexing << endl;
							File.close();
							File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + filenum + ".csv",
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
							File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + filenum + ".csv",
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
						}
						if (check[1])
						{
							tree2.indexing = statement;
							tree2.Fileno = toInt(filenum);
							if (!hasPath("RedBlackTree"))
							{
								createFolder("RedBlackTree");
							}
							removeAll("RedBlackTree/node");
							remove("RedBlackTree/info.txt");
							File.open("RedBlackTree/info.txt", fstream::out);
							File << tree2.indexing << endl;
							File.close();
							File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + filenum + ".csv",
									  ios::in);
							string temp;
							int skip = 0;
							while (getline(File, temp, ','))
							{
								Lowercase(temp);
								if (temp == tree2.indexing)
									break;
								skip++;
							}
							File.close();
							File.open("Data/NCHS_-_Leading_Causes_of_Death__United_States_" + filenum + ".csv",
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
					}
				}
			}
			return;
		}
		else if (statement == "1")
			check[0] = !check[0];
		else if (statement == "2")
			check[1] = !check[1];
		else if (statement == "3")
			check[2] = !check[2];
	}
}
#endif //INDEXING_CPP