// SearchingAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv [])
{
	int ret = 0;
	fileHandler file;
	
	ret = file.readFile("\\String.txt", 2);
	if (ret){
		std::cout << "Error with read file function!\n";
	}
	ret = file.readFile("\\Numbers.txt", 1);
	if (ret){
		std::cout << "Error with read file function!\n";
	}
	std::cout << file.stringVector << std::endl;
	std::cout << file.intVector << std::endl;
	return 0;
}

