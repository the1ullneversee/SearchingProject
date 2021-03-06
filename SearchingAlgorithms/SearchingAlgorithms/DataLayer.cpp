#include "stdafx.h"

dataLayer::dataLayer()
{
	_ret = 0;
	dataLayer::getCWD();
	dataLayer::intVector.push_back(0);
	dataLayer::intList.push_back(0);
	dataLayer::stringVector;
	this->stringList.push_back("");
	this->_completion = 0;

}
void dataLayer::getCWD() {

	if (!_getcwd(_cBaseDirectory, sizeof(_cBaseDirectory)))
	{
		std::cout << "Error with setting directory\n";
	}

	_cBaseDirectory[sizeof(_cBaseDirectory) - 1] = '\0'; /* not really required */
	_directory = _cBaseDirectory;
}
dataLayer::~dataLayer()
{
	std::cout << "Data layer ending" << std::endl;
}
error_type dataLayer::readFile(DataWrapper& dwrap, _container_type con_type) {
	ret_code ret = func_passed;
	Time timer;

	try {
		float bar = 0.00;
		int i = 0;
		float prog = 0.00;
		std::size_t _completion = 0;
		std::string tempString = "";
		std::size_t filesize = 0;
		std::size_t line_count = 0;
		std::string s;
		std::ifstream in(dwrap.getFilename(), std::ios::binary | std::ios::ate);
		filesize = in.tellg();
		std::fstream myfile(dwrap.getFilename(), std::ios_base::in);
		std::ifstream inFile;
		switch (con_type) {
		case 0:
			throw "Container selection not supported";
			ret = bad_input;
			break;
		case 1:
			timer.clock_start();
			if (!myfile.is_open())
				throw std::exception("Failed to open function");
			while (!myfile.eof()) {
				myfile >> tempString;
				_intTemp = std::atoi(tempString.c_str());
				dwrap.intVector.push_back(_intTemp);
			}
			timer.clock_end();
			timer.duration();
			break;
		case 2:
			// filling the String vector
			int cur;
			timer.clock_start();
			if (filesize > 100000) {
				dwrap.stringVector.resize(filesize / 100);
				inFile.open(dwrap.getFilename());
				if (!inFile.is_open())
					throw std::exception("Failed to open function");
				while (std::getline(inFile, tempString)) {
					if (i <= (dwrap.stringVector.capacity() - 1))
					{
						dwrap.stringVector[i] = tempString;
					}
					else {
						dwrap.stringVector.push_back(tempString);
					}
					i++;
					_completion++;
				}
			}
			else {
				inFile.open(dwrap.getFilename());
				while (std::getline(inFile, tempString)) {
					dwrap.stringVector.push_back(tempString);
				}
			}
			timer.clock_end();
			timer.duration();
			break;
		case 3:
			timer.clock_start();
			if (filesize > 100000) {
				dwrap.intList.resize(filesize / 100);
				inFile.open(dwrap.getFilename());
				if (!inFile.is_open())
					throw std::exception("Failed to open function");
				auto listStringIT = dwrap.intList.begin();
				while (std::getline(inFile, tempString)) {
					if (listStringIT != dwrap.intList.end())
					{
						_intTemp = std::atoi(tempString.c_str());
						dwrap.intList.insert(listStringIT, _intTemp);
						listStringIT++;
					}
					else {
						_intTemp = std::atoi(tempString.c_str());
						dwrap.intList.push_back(_intTemp);
					}
					i++;
					_completion++;
				}
			}
			else {
				if (!myfile.is_open())
					throw std::exception("Failed to open function");
				while (!myfile.eof()) {
					myfile >> tempString;
					_intTemp = std::atoi(tempString.c_str());
					dwrap.intList.push_back(_intTemp);
				}
			}
			timer.clock_end();
			timer.duration();
			break;
		case 4:
			//Filling the String List
			timer.clock_start();
			if (filesize > 100000) {
				dwrap.stringList.resize(filesize / 100);
				inFile.open(dwrap.getFilename());
				if (!inFile.is_open())
					throw std::exception("Failed to open function");
				auto listStringIT = dwrap.stringList.begin();
				while (std::getline(inFile, tempString)) {
					if (listStringIT != dwrap.stringList.end())
					{
						dwrap.stringList.insert(listStringIT, tempString);
						listStringIT++;
					}
					else {
						dwrap.stringList.push_back(tempString);
					}
					i++;
					_completion++;
				}
			}
			else {
				inFile.open(dwrap.getFilename());
				while (std::getline(inFile, tempString)) {
					dwrap.stringList.push_back(tempString);
				}
			}
			timer.clock_end();
			timer.duration();
			break;
		default:
			std::cout << "Couldn't find a matching case\n";
			ret = function_fail;
			break;
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
	catch (...) {   // catch block will only be executed under /EHa
		std::cout << "Caught an exception in catch(...)." << std::endl;
	}
	inFile.close();
	return ret;
}
error_type dataLayer::readFile(dataLayer& dlay, _container_type con_type){ // Might have to pass in a handle to stop corruption of data when doing threading. 

	//_container_type con_type = static_cast<_container_type>(containerSelection);
	ret_code ret = func_passed;
	Time timer;

	try {
		//std::cout << "FileName and Directory Test: " << filename << std::endl << _directory << std::endl;
		float bar = 0.00;
		int i = 0;
		float prog = 0.00;
		std::size_t line_count = 0;
		std::ifstream::pos_type filesize;
		std::string s;
		std::ifstream in(dlay._filename, std::ios::binary | std::ios::ate);
		dataLayer::_fileSize = in.tellg();
		std::ofstream os;
		std::ostringstream osString;
		std::cout << "File Size: " << dataLayer::_fileSize << std::endl;
		std::vector<std::string> heapVect;
		std::size_t sint = 0;
		std::vector<std::string> data;
		
		std::vector<std::string> test1Vect;
		std::vector<std::string> test2Vect;
		//inFile.exceptions(std::ios::failbit);
		std::string s4;
		//if (inFile) {
		std::ifstream inFile;
		std::ifstream file(dlay._filename);
		//std::cout << "The current working directory is: " << _cBaseDirectory + filenam
		switch (con_type) {
		case 0:
			throw "Container selection not supported";
			ret = bad_input;
			break;
		case 1:
			while (!inFile.eof()) {
				_completion++;
				float prog(_completion / float(_fileSize));
				std::cout << std::fixed << std::setprecision(2)
					<< "\r   [" << std::string(_completion, '#')
					<< std::string(_fileSize + 1 - _completion, ' ') << "] " << 100 * prog << "%";

				//Filling the int vector
				inFile >> _stringTemp;
				//std::getline(inFile, _stringTemp);
				_intTemp = std::atoi(_stringTemp.c_str());
				//std::cout << _stringTemp;
				intVector.push_back(_intTemp);
			}
			break;
		case 2:
			// filling the String vector
			int cur;
			if (_fileSize > 100000) {
				dlay.stringVector.resize(_fileSize / 100);
				/*for (unsigned int ui = 0; ui < dlay.stringVector.capacity() - 1; ui++) {
					dlay.stringVector[ui].reserve(sizeof(_stringTemp));
				}*/
				inFile.open(dlay._filename);
				if (!inFile)
					throw std::exception("File not open!");
				while (std::getline(inFile, _stringTemp)) {
					if (i <= (dlay.stringVector.capacity() - 1))
					{
						dlay.stringVector[i] = _stringTemp;
					}
					else {
						dlay.stringVector.push_back(_stringTemp);
					}
					i++;
					_completion++;
				}
			}
			else {
				while (std::getline(inFile, _stringTemp)) {
					dlay.stringVector.push_back(_stringTemp);
				}
			}
			//inFile.close();
			/*inFile.open(dlay._filename);
			while (std::getline(inFile, _stringTemp)) {
				dlay.stringVector.push_back(_stringTemp);
			}*/
			timer.clock_end();
			timer.duration();
			break;
		case 3:
			//Filling the int list
			while (!inFile.eof()) {
				std::getline(inFile, _stringTemp);
				_intTemp = std::atoi(_stringTemp.c_str());
				//std::cout << _stringTemp;
				intList.push_back(_intTemp);
			}
			break;
		case 4:
			//Filling the String List
			timer.clock_start();
			while (std::getline(inFile, _stringTemp)) {
				//std::cout << _stringTemp;
				stringList.push_back(_stringTemp);
			}
			timer.clock_end();
			timer.duration();
			break;
		default:
			std::cout << "Couldn't find a matching case\n";
			ret = function_fail;
			break;
		}
		//else {
		//	std::cout << "Error reading file" << std::endl;
		//	throw std::exception("Error reading file");
		//	//free(&inFileTemp);
		//}
		std::cout << "Size of vect: " << heapVect.size() << std::endl;
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
	inFile.close();
	return ret;// Change this static cast. 
}

ret_code dataLayer::saveFile(std::string filename, _container_type con_type, dataLayer &fhandler_copy)
{
	ret_code ret = func_passed;
	try {
		ofFile.open(_directory + filename);
		ofFile.exceptions(std::ios::failbit);
		if (ofFile)
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
				ofFile << fhandler_copy.intList;
				ofFile.close();
				break;
			case 4:
				//string list
				ofFile << fhandler_copy.stringList;
				ofFile.close();
				break;
			default:
				throw "No container type selection";
				break;
			}
		else {
			throw std::exception("Error opening file");
			ret = function_fail;
		}
	}
	catch (std::exception& ex) {
		Menu::errorToScreen(ex, "Read File");
	}
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
			throw std::exception("File could not be opened");
		}
	}
	catch (std::exception & ex) {
		Menu::errorToScreen(ex, "Random numbers");
		ret = function_fail;
	}
	if (ofFile.is_open()){
		ofFile.close();
	}
	return ret;
}
ret_code dataLayer::linearNumbers(std::size_t amount, std::string fileName)
{
	ret_code ret = function_fail;
	std::ofstream out(fileName);
	try {
		if (!out)
			throw std::exception("Could not create file");
		for (auto i = 0; i < amount; i++)
		{
			out << i << std::endl;
		}
	}
	catch (std::exception& e)
	{
		Menu::errorToScreen(e, "Linear Numbers");
	}
	if (out.is_open())
	{
		out.close();
	}
	return ret;
}
ret_code dataLayer::containerFiller(DataWrapper*& dwrap)
{
	ret_code ret = function_fail;
	try {
		dataLayer dlay;
		ret = dlay.readFile(*dwrap, dwrap->getConType());
	}
	catch(...)
	{ 
		std::cout << "Caught an exception in catch(...)." << std::endl;
	}
	return ret;
}
std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString)
{
	for (std::size_t i = 0; i < vecString.size(); i++) {
		out << vecString[i] << " ";
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::vector<std::size_t> &vecInt)
{
	for (std::size_t i = 0; i < vecInt.size(); i++) {
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
ret dataLayer::printContainer(DataWrapper& dlayer, _container_type conType) {
	error_type error = func_passed;// Think we need a better way of doing this
	try {
		switch (conType)
		{
		case 1:
			if (dlayer.intVector.size() == 0 || dlayer.intVector.empty()) { throw std::exception("Container is empty!"); }
			std::cout << dlayer.intVector;
			break;
		case 2:
			if (dlayer.stringVector.size() == 0 || dlayer.stringVector.empty()) { throw std::exception("Container is empty!"); }
			std::cout << dlayer.stringVector;
			break;
		case 3:
			if (dlayer.intList.size() == 0 || dlayer.intList.empty()) { throw std::exception("Container is empty!"); }
			std::cout << dlayer.intList;
			break;
		case 4:
			if (dlayer.stringList.size() == 0 || dlayer.stringList.empty()) { throw std::exception("Container is empty!"); }
			std::cout << dlayer.stringList;
			break;
		default:
			
			break;
		}
	}
	catch (std::exception& e)
	{
		menu->errorToScreen(e, "Print Container");
	}
	catch (...) {   // catch block will only be executed under /EHa
		std::cout << "Caught an exception in catch(...)." << std::endl;
	}
	return error;
}
void dataLayer::containerFillFromFile(DataWrapper& dwrap_) {
	//We will ask what container they wish to have
	//What the file name is
	try {
		readFile(dwrap_, dwrap_.getConType());
	}
	catch (std::exception& e)
	{
		Menu::errorToScreen(e, "Container Fill From File");
	}
}
std::wstring dataLayer::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
ret_code dataLayer::getFile(bool& functionAlive)
{
	bool locVal = false;
	bool functionLocalAlive = true;
	functionAlive = functionLocalAlive;
	LPCTSTR errorText = NULL;
	WIN32_FIND_DATA winData;
	while (!locVal) {
		std::cout << "Please enter in the file name you want to search" << std::endl << "Enter 1 to get local file list" << std::endl << "Enter exit  to go back to main menu" << std::endl;
		//try to open the file incase invalid file name;
		std::cin >> _filename;
		if (_filename == "exit" || _filename == "Exit") {
			locVal = true;
			functionLocalAlive = false;
			functionAlive = false;
		}
		else if (_filename == "1") {
			bool found = false;
			menu->clearScreen();
			std::string locChoice;
			std::wstring locDirFileName;
			std::cout << _directory << std::endl;
			while (!found) {

				std::wstring stemp = s2ws(_directory + "\\*");
				LPCWSTR dirwstr = stemp.c_str();
				HANDLE searchHandle = FindFirstFile(dirwstr, &winData);
				locDirFileName = winData.cFileName;
				std::cout << "Listing directory!" << std::endl;
				//Only finds one file which so happens to be the same as the last folder in directory address? Returns Error 18
				do {
					//std::wcout << dirwstr << std::endl;
					std::wcout << winData.cFileName << std::endl;
				} while (FindNextFile(searchHandle, &winData));
				menu->changeColourScreen("blue", "Red");
				std::cout << std::endl << "Enter up to go up a directory level" << std::endl << "Alternatively type the folder name to enter." << std::endl << "OR type exit if filename is found" << std::endl;
				std::cin >> locChoice;
				if (locChoice == "exit" || locChoice == "Exit") {
					found = true;
				}
				else if (locChoice == "up" || locChoice == "Up")
				{

					std::size_t Textfound = _directory.find_last_of("/\\");
					std::cout << _directory << "Size:" << _directory.size() << "found: " << Textfound << std::endl;
					_directory = _directory.substr(0, Textfound);
					std::cout << _directory << "Size: " << _directory.size() << std::endl;
				}
				else {
					_directory = _directory += "\\" + locChoice;
				}
				//reverting back to the normal color
				FindClose(searchHandle);
			}
		}
		else {
			getCWD();
			std::ifstream infile;
			infile.open(_directory + "\\" + _filename);
			if (infile.is_open()) { locVal = true; }
			else { std::cout << "Could not open file, try again!" << std::endl; }
		}
	}

	return func_passed;
}
_container_type dataLayer::getUserConType()
{
	bool locVal = false;
	_container_type conType = vectorInt;
	int conChoice;
	while (!locVal) {
		std::cout << " Please Select your container type: " << std::endl << "1: integer vector" << std::endl << "2: string vector" << std::endl << "3: integer list" << std::endl << "4: string list" << std::endl;
		std::cin >> conChoice;
		conType = static_cast<_container_type>(conChoice);
		for (int i = 0; i < enumTypeEnd; i++) {
			if (conType == i) { locVal = true; break; }
		}
		if (!locVal) {
			std::cout << "Invalid container selection, try again" << std::endl;
		}
	}
	return conType;
}