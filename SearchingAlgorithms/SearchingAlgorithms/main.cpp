// SearchingAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv [])
{
	int rt = 0;
	// Smart pointers mean you do not have to worry about the deletion of the pointer when you are done using it.
	// Pass them around to different functions by references
	// you cannot copy them to stop them being deleted multiple times.
	std::unique_ptr<fileHandler> fhandler(new fileHandler);
	//fileHandler *file = new fileHandler();
	rt = fhandler->readFile("\\String.txt", 2);
	if (rt){
		std::cout << "Error with read file function!\n";
	}
	rt = fhandler->readFile("\\Numbers.txt", 1);
	if (rt){
		std::cout << "Error with read file function!\n";
	}
	fhandler->intVector.push_back(5);
	fhandler->intVector.push_back(22);
	fhandler->intVector.push_back(14);
	fhandler->intVector.push_back(8);
	fhandler->saveFile("\\newNumbers.txt", 1, fhandler);
	std::cout << fhandler->stringVector << std::endl;
	std::cout << fhandler->intVector << std::endl;
	return 0;
}

