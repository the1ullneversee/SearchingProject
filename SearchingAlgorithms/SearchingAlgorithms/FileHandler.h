#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "stdafx.h"
#define ret int

class fileHandler : public DataContainer
{
public:
	fileHandler();
	~fileHandler();
	ret readFile(std::string filename, int containerSelection);
	ret saveFile(std::string filename, int containerSelection, fileHandler &fhandler_copy);
	ret randomNumbers();
	std::ifstream inFile;
	std::ofstream ofFile;
private:
	char _cBaseDirectory[FILENAME_MAX];
	// Define error return types for greater reporting 
	//enum error_type : int {};
	enum _container_type : int {default,vectorInt, vectorString, listInt, listString};
	int _ret;
	std::string _stringTemp;
	int _intTemp;
};

#endif