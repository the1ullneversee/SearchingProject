// SearchingAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv [])
{
	int rt = 0;
	// Smart pointers mean you do not have to worry about the deletion of the pointer when you are done using it.
	// Pass them around to different functions by references
	// you cannot copy them to stop them being deleted multiple times.
	std::unique_ptr<dataLayer> dlayerhandle(new dataLayer);
	//fileHandler *file = new fileHandler();
	rt = dlayerhandle->readFile("\\String.txt", 2);
	if (rt){
		std::cout << "Error with read file function!\n";
	}
	rt = dlayerhandle->readFile("\\Numbers.txt", 1);
	if (rt){
		std::cout << "Error with read file function!\n";
	}
	dlayerhandle->intVector.push_back(5);
	dlayerhandle->intVector.push_back(22);
	dlayerhandle->intVector.push_back(14);
	dlayerhandle->intVector.push_back(8);
	dlayerhandle->saveFile("\\newNumbers.txt", 1,*dlayerhandle);
	std::cout << dlayerhandle->stringVector << std::endl;
	std::cout << dlayerhandle->intVector << std::endl;
	return 0;
}

