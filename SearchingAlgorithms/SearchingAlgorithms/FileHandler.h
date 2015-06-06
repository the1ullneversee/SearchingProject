#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "stdafx.h"

class fileHandler : public DataContainer
{
public:
	fileHandler();
	~fileHandler();
	int readFile(std::string filename, int containerSelection);
	int saveFile(std::string filename, int containerSelection);

private:
	char _cBaseDirectory[FILENAME_MAX];
	enum _container_type : int {default,vectorInt, vectorString, listInt, listString};
	int _ret;
	std::string _stringTemp;
	int _intTemp;
};

#endif