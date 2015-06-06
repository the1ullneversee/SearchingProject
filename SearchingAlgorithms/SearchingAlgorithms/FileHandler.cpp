#include "stdafx.h"

fileHandler::fileHandler(){
	_ret = 0;
	if (!_getcwd(_cBaseDirectory, sizeof(_cBaseDirectory)))
	{
		std::cout << "Error with setting directory\n";
	}

	//_cBaseDirectory[sizeof(_cBaseDirectory) -1] = '\0'; /* not really required */
	std::cout << "The current working directory is: " << _cBaseDirectory;
}

fileHandler::~fileHandler()
{
	std::cout << "DESTRUCTION" << std::endl;
}

int fileHandler::readFile(std::string filename, int containerSelection){
	_container_type con_type = static_cast<_container_type>(containerSelection);
	std::ifstream inFile(_cBaseDirectory + filename);
	std::cout << "The current working directory is: " << _cBaseDirectory + filename;
	if (inFile.is_open()){
		while (!inFile.eof()){
			switch (con_type) {
			case 0:

				break;
			case 1:
				std::getline(inFile, _stringTemp);
				_intTemp = std::atoi(_stringTemp.c_str());
				intVector.push_back(_intTemp);
				break;
			case 2:
				std::getline(inFile, _stringTemp);
				stringVector.push_back(_stringTemp);
				break;
			case 3:

				break;
			default:
				std::cout << "Couldn't find a matching case\n";
				_ret = 0;
				break;
			}
		}
	} else {
		_ret = 1;
		std::cout << "File could not be opened" << std::endl;
	}
	return _ret;
}

int fileHandler::saveFile(std::string filename, int containerSelection){
	_container_type con_type = static_cast<_container_type>(containerSelection);
	std::ofstream ofFile(_cBaseDirectory + filename);
	return 0;
}