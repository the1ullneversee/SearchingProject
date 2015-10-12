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
	std::cout << "Data layer ending" << std::endl;
}

Menu * dataLayer::getMenu()
{
	return menu;
}

error_type dataLayer::readFile(std::string filename, dataLayer::_container_type con_type){ // Might have to pass in a handle to stop corruption of data when doing threading. 
	//_container_type con_type = static_cast<_container_type>(containerSelection);
	ret_code ret = func_passed;
	Time timer;

	try{
		//std::cout << "FileName and Directory Test: " << filename << std::endl << _directory << std::endl;
		inFile.open(filename);
		float bar;
		float prog = 0.00;
		std::ifstream::pos_type filesize;
		std::ifstream in(filename, std::ios::binary | std::ios::ate);
		dataLayer::_fileSize = in.tellg();
		std::cout << "File Size: " << dataLayer::_fileSize << std::endl;
		//inFile.exceptions(std::ios::failbit);
		if (inFile) {
			timer.clock_start();
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
				
				while (!inFile.eof()) {
					
					prog = _completion / float(_fileSize);
					//if (prog == bar || prog == 0.2 || prog == 0.3 || prog == 0.00) {
					if (prog == bar)
					{
						if (bar == 0.00)
						{
							bar = 0.10;
						}
						else {
							bar = bar * 2;
						}
						cur = std::ceil(_completion * _fileSize);
						std::cout << std::fixed << std::setprecision(2)
							<< "\r   [" << std::string(0, '#')
							<< "] " << 100 * prog << "%";
					}
					std::getline(inFile, _stringTemp);
					//std::cout << _stringTemp;
					stringVector.push_back(_stringTemp);
					_completion++;
				}
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
				while (!inFile.eof()) {
					std::getline(inFile, _stringTemp);
					//std::cout << _stringTemp;
					stringList.push_back(_stringTemp);
				}
				break;
			default:
				std::cout << "Couldn't find a matching case\n";
				ret = function_fail;
				break;
			}
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
	timer.clock_end();
	timer.duration();
	inFile.close();
	return ret;// Change this static cast. 
}

ret_code dataLayer::saveFile(std::string filename, dataLayer::_container_type con_type, dataLayer &fhandler_copy)
{
	ret_code ret = func_passed;
	try {
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
ret dataLayer::printContainer(dataLayer& dlayer, dataLayer::_container_type conType) {
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
		menu->clearScreen();
	}
	catch (std::exception& e)
	{
		menu->errorToScreen(e, "Print Container");
	}
	return error;
}
void dataLayer::containerFillFromFile(dataLayer& dlayer) {
	//We will ask what container they wish to have
	//What the file name is
}
dataLayer::_container_type dataLayer::containerTypeSelectionRoutine()
{
	_container_type conType = vectorInt;


	return dataLayer::listInt;
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
dataLayer::_container_type dataLayer::getUserConType()
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