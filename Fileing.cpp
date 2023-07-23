
#ifndef FILEING_CPP
#define FILEING_CPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdio>
#include <sys/stat.h>

using namespace std;

// tells if a file/folder even exists or not
bool hasPath(string path)
{
	struct stat buffer{};
	return (stat(path.c_str(), &buffer) == 0);
}

// removes all the nodes
void removeAll(string path)
{
	int a = 1;
	while (remove((path + '_' + to_string(a) + ".txt").c_str()) == 0)
	{
//		remove((path + '_' + to_string(a) + "_left.txt").c_str());
//		remove((path + '_' + to_string(a) + "_right.txt").c_str());
		a++;
	}
}

// makes a folder if one doesnt exist
void createFolder(string path)
{
	if (mkdir(path.c_str()) == -1)
	{
		cerr << "Error :  " << strerror(errno) << endl;
	}
}

#endif //FILEING_CPP
