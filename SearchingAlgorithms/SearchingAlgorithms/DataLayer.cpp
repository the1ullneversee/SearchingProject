#include "stdafx.h"

dataLayer::dataLayer()
{
	//std::cout << "Loading data layer" << std::endl;
	_ret = 0;
	dataLayer::getCWD();
	//dataLayer::_directory = "";
	dataLayer::intVector.push_back(0);
	dataLayer::intList.push_back(0);
	dataLayer::stringVector;
	dataLayer::stringList.push_back("");
	//dataLayer::vectorStorer.push_back(dataLayer::stringVector);
	//dataLayer::listStorer
}
void dataLayer::getCWD() {

	if (!_getcwd(_cBaseDirectory, sizeof(_cBaseDirectory)))
	{
		std::cout << "Error with setting directory\n";
	}

	_cBaseDirectory[sizeof(_cBaseDirectory) - 1] = '\0'; /* not really required */
	_directory = _cBaseDirectory;
	//Can add in for testing 
	//std::cout << "The current working directory is: " << _directory << std::endl;
}
dataLayer::~dataLayer()
{
	// Can add in for testing 
	std::cout << "DESTRUCTION" << std::endl;
}

error_type dataLayer::readFile(std::string filename, dataLayer::_container_type con_type){
	//_container_type con_type = static_cast<_container_type>(containerSelection);
	ret_code ret = func_passed;
	try{
		//std::cout << "FileName and Directory Test: " << filename << std::endl << _directory << std::endl;
		inFile.open(filename);
		//inFile.exceptions(std::ios::failbit);
		if (inFile) {
			//std::cout << "The current working directory is: " << _cBaseDirectory + filename
			while (!inFile.eof()) {
				switch (con_type) {
				case 0:
					throw "Container selection not supported";
					ret = bad_input;
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
					ret = function_fail;
					break;
				}
			}
			inFile.close();
		}
		else {
			std::cout << "Error reading file" << std::endl;
			throw std::exception("Error reading file");
			//free(&inFileTemp);
		}
	}
	catch (std::invalid_argument& e)
	{
		std::cout << "Function failed reason: "
			<< e.what() << std::endl;
	}
	catch (const std::exception & ex) {
		std::cerr << "Function failed - reason is "
			<< ex.what();
	}
	return ret;// Change this static cast. 
}

ret_code dataLayer::saveFile(std::string filename, int containerSelection, dataLayer &fhandler_copy)
{
	ret_code ret = func_passed;
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
			ret = function_fail;
		}
	}
	catch (std::string err) {
		std::cout << err << std::endl;
	}
	/*catch (const std::exception & ex) {
		std::cerr << "Saving operation failed - reason is "
			<< ex.what();
	}*/
	if (ofFile.is_open()){
		ofFile.close();
	}

	return ret;
}

ret_code dataLayer::randomNumbers()
{
	ret_code ret = func_passed;
	std::size_t random = 0;
	std::size_t MAX = std::numeric_limits<std::size_t>::max();
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
			ret = function_fail;
		}
	}
	catch (std::string err)
	{
		std::cout << "The following error has occured" << err << std::endl;
		//ret = 1;
	}
	/*catch (const std::exception & ex) {
		std::cerr << "File operation failed - reason is "
			<< ex.what();
	}*/
	if (ofFile.is_open()){
		ofFile.close();
	}
	return ret;
}
ret_code dataLayer::containerFiller(std::string filename,dataLayer::_container_type conType)
{
	return dataLayer::readFile(filename, conType);
}
std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString)
{
	for (std::size_t i = 0; i < vecString.size(); i++){
		out << vecString[i] << " ";
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::vector<std::size_t> &vecInt)
{
	for (std::size_t i = 0; i < vecInt.size(); i++){
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
std::ostream& operator << (std::ostream &out, std::list<std::size_t> &listInt)
{
	for (std::list<std::size_t>::const_iterator i = listInt.begin(); i != listInt.end(); i++)
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