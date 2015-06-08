#include "stdafx.h"

fileHandler::fileHandler()
{
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

ret fileHandler::readFile(std::string filename, int containerSelection){
	_container_type con_type = static_cast<_container_type>(containerSelection);
	try{
		//std::ifstream inFile
		inFile.open(_cBaseDirectory + filename);
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
		}
		else {
			_ret = 1;
			throw "File could not be opened";
		}
	}
	catch (std::string err)
	{
		std::cout << "Function failed reason: "
			<< err << std::endl;
		_ret = 1; 
	}
	inFile.close();
	return _ret;
}

ret fileHandler::saveFile(std::string filename, int containerSelection, fileHandler &fhandler_copy)
{
	_ret = 1;
	try {
		_container_type con_type = static_cast<_container_type>(containerSelection);
		ofFile.open(_cBaseDirectory + filename);
		switch (con_type)
		{
		case 1:
			//int vector
			ofFile << fhandler_copy.intVector; 
			break;
		case 2:
			//string vector
			break;
		case 3:
			//int list
			break;
		case 4:
			//string list
			break;
		default:
			throw "No container type selection";
			break;
		}
	}
	catch(std::string err) {
		std::cout << err << std::endl;
		_ret = 1;
	}
	
	
	return _ret;
}

ret fileHandler::randomNumbers()
{
	unsigned int random = 0;
	unsigned int MAX = 468;
	try
	{
		// Going to file a file with random values so that elements can be found
		for (int i = 0; i < MAX; i++){
			random = std::rand() % 3783;
		}

	}
	catch (std::string err)
	{

	}
	return _ret;
}
