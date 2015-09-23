// SearchingAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv [])
{
	int rt = 0;
	// Smart pointers mean you do not have to worry about the deletion of the pointer when you are done using it.
	// Pass them around to different functions by references
	// you cannot copy them to stop them being deleted multiple times.
	//std::unique_ptr<dataLayer> dlayerhandle(new dataLayer);
	//std::unique_ptr<dataLayer> dlayerhandleTemp(new dataLayer);
	//fileHandler *file = new fileHandler();

	/*rt = dlayerhandle->randomNumbers();
	if (rt){ std::cout << "Error with rand file function!\n"; }
	rt = dlayerhandle->readFile("\\String.txt", 4);
	if (rt){ std::cout << "Error with read file function!\n";}
	rt = dlayerhandle->readFile("\\String.txt", 2);
	if (rt){
		std::cout << "Error with read file function!\n";
	}
	rt = dlayerhandle->readFile("\\randomNumbers.txt", 1);
	if (rt){
		std::cout << "Error with read file function!\n";
	}
	rt = dlayerhandle->readFile("\\Numbers.txt", 3);
	if (rt){
		std::cout << "Error with read file function!\n";
	}
	std::cout << dlayerhandle->stringList << std::endl;
	std::cout << dlayerhandle->stringVector << std::endl;
	std::cout << dlayerhandle->intVector << std::endl;
	std::cout << dlayerhandle->intList << std::endl;
	dlayerhandle->stringVector.push_back("the1ullneversee");
	dlayerhandle->saveFile("\\newNumbers.txt", 1,*dlayerhandle);
	dlayerhandle->saveFile("\\newStrings.txt", 2, *dlayerhandle);

	rt = dlayerhandleTemp->readFile("\\newNumbers.txt", 1);
	rt = dlayerhandleTemp->readFile("\\newStrings.txt", 2);
	if (rt){
		std::cout << "Error with read file function!\n";
	}
	std::cout << dlayerhandleTemp->intVector << std::endl << dlayerhandleTemp->stringVector;
	*/

	std::unique_ptr<Menu> menu(new Menu);
	menu->mainMenu();

	return 0;
}

