#include "stdafx.h"

dataLayer::dataLayer()
{
	_ret = 0;
	if (!_getcwd(_cBaseDirectory, sizeof(_cBaseDirectory)))
	{
		std::cout << "Error with setting directory\n";
	}

	//_cBaseDirectory[sizeof(_cBaseDirectory) -1] = '\0'; /* not really required */
	std::cout << "The current working directory is: " << _cBaseDirectory;
}

dataLayer::~dataLayer()
{
	std::cout << "DESTRUCTION" << std::endl;
}

ret dataLayer::readFile(std::string filename, int containerSelection){
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

ret dataLayer::saveFile(std::string filename, int containerSelection, dataLayer &fhandler_copy)
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

ret dataLayer::randomNumbers()
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
std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString)
{
	for (unsigned int i = 0; i < vecString.size(); i++){
		out << vecString[i];
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::vector<int> &vecInt)
{
	for (unsigned int i = 0; i < vecInt.size(); i++){
		out << vecInt[i];
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::list<std::string>)
{
	return out;
}
std::ostream& operator << (std::ostream &out, std::list<int>)
{
	return out;
}