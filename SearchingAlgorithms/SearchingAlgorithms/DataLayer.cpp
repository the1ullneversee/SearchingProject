#include "stdafx.h"

dataLayer::dataLayer()
{
	_ret = 0;
	if (!_getcwd(_cBaseDirectory, sizeof(_cBaseDirectory)))
	{
		std::cout << "Error with setting directory\n";
	}

	_cBaseDirectory[sizeof(_cBaseDirectory) -1] = '\0'; /* not really required */
	_directory = _cBaseDirectory;
	//Can add in for testing 
	//std::cout << "The current working directory is: " << _directory << std::endl;
}

dataLayer::~dataLayer()
{
	// Can add in for testing 
	//std::cout << "DESTRUCTION" << std::endl;
}

ret dataLayer::readFile(std::string filename, int containerSelection){
	_container_type con_type = static_cast<_container_type>(containerSelection);
	try{
		inFile.open(_directory + filename);
		//inFile.exceptions(std::ios::failbit);
		if (inFile){
			//std::cout << "The current working directory is: " << _cBaseDirectory + filename
			while (!inFile.eof()){
				switch (con_type) {
				case 0:
					throw "Container selection not supported";
					break;
				case 1:
					//Filling the int vector
					inFile >> _stringTemp;
					//std::getline(inFile, _stringTemp);
					_intTemp = std::atoi(_stringTemp.c_str());
					//std::cout << _stringTemp;
					intVector.push_back(_intTemp);
					break;
				case 2:
					// filling the String vector
					std::getline(inFile, _stringTemp);
					//std::cout << _stringTemp;
					stringVector.push_back(_stringTemp);
					break;
				case 3:
					//Filling the int list
					std::getline(inFile, _stringTemp);
					_intTemp = std::atoi(_stringTemp.c_str());
					//std::cout << _stringTemp;
					intList.push_back(_intTemp);
					break;
				case 4:
					//Filling the String List
					std::getline(inFile, _stringTemp);
					//std::cout << _stringTemp;
					stringList.push_back(_stringTemp);
					break;
				default:
					std::cout << "Couldn't find a matching case\n";
					_ret = 0;
					break;
				}
			}
			inFile.close();
		}
		else {
			std::cout << "Error reading file" << std::endl;
			throw "Error";
			//free(&inFileTemp);
		}
	}
	catch (std::string err)
	{
		std::cout << "Function failed reason: "
			<< err << std::endl;
	}
	/*catch (const std::exception & ex) {
		std::cerr << "Could not convert to int - reason is "
			<< ex.what();
	}*/
	return _ret;
}

ret dataLayer::saveFile(std::string filename, int containerSelection, dataLayer &fhandler_copy)
{
	_ret = 1;
	try {
		_container_type con_type = static_cast<_container_type>(containerSelection);
		ofFile.open(_directory + filename);
		//ofFile.exceptions(std::ios::failbit);
		if (ofFile) {
			switch (con_type)
			{
			case 1:
				//int vector
				ofFile << fhandler_copy.intVector;
				ofFile.close();
				break;
			case 2:
				//string vector
				ofFile << fhandler_copy.stringVector;
				ofFile.close();
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
		else {
			std::cout << "Error reading file" << std::endl;
			throw "Error";
		}
	}
	catch (std::string err) {
		std::cout << err << std::endl;
		_ret = 1;
	}
	/*catch (const std::exception & ex) {
		std::cerr << "Saving operation failed - reason is "
			<< ex.what();
	}*/
	if (ofFile.is_open()){
		ofFile.close();
	}

	return _ret;
}

ret dataLayer::randomNumbers()
{
	unsigned int random = 0;
	unsigned int MAX = 10000;
	try
	{
		ofFile.open(_directory + "\\randomNumbers.txt");
		ofFile.exceptions(std::ios::failbit);
		if (ofFile){
			// Going to file a file with random values so that elements can be found
			for (int i = 0; i < MAX; i++){
				ofFile << std::rand() % 3783 << std::endl;
			}
		}
		else {
			throw "Operation Failed";
		}
	}
	catch (std::string err)
	{
		std::cout << "The following error has occured" << err << std::endl;
	}
	/*catch (const std::exception & ex) {
		std::cerr << "File operation failed - reason is "
			<< ex.what();
	}*/
	if (ofFile.is_open()){
		ofFile.close();
	}
	return _ret;
}
std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString)
{
	for (unsigned int i = 0; i < vecString.size(); i++){
		out << vecString[i] << " ";
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::vector<int> &vecInt)
{
	for (unsigned int i = 0; i < vecInt.size(); i++){
		out << vecInt[i] << " ";
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::list<std::string> &listString)
{
	for (std::list<std::string>::const_iterator i = listString.begin(); i != listString.end(); i++)
	{
		out << *i << " ";
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::list<int> &listInt)
{
	for (std::list<int>::const_iterator i = listInt.begin(); i != listInt.end(); i++)
	{
		out << *i << " ";
	}

	return out;
}
bool dataLayer::directoryList(LPCTSTR pstr) {

	CFileFind finder;
	CString strWildCard(pstr);
	strWildCard += _T("\\*.*");
	bool bworking = finder.FindFile(strWildCard);
	while (bworking) {
		bworking = finder.FindNextFile();

		//Skip dots
		if (finder.IsDots())
			continue;

		if (finder.IsDirectory())
		{
			CString str = finder.GetFilePath();
			std::cout << (LPCTSTR) str << std::endl;
			directoryList(str);
		}
	}
	return 0;
}