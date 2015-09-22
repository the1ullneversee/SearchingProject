#include "stdafx.h"

searchTools::searchTools(){
	_found = false; 
	Time timer;
}
searchTools::~searchTools(){

}
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int) s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete [] buf;
	return r;
}
void searchTools::searchMenu()
{
	try {
		bool locVal = false;
		std::unique_ptr<dataLayer> dlay(new dataLayer);
		_searchType srch = linear;
		_searchType srchType = linear;
		WIN32_FIND_DATA winData;
		dataLayer::_container_type conType = dataLayer::vectorInt;
		//std::wstring stemp = s2ws("C:\\Users\\thomaskn\\Downloads\\*");
		LPCTSTR errorText = NULL;

		while (!locVal) {
			std::cout << "Please enter in the file name you want to search" << std::endl << "Or enter 1 to get local file list" << std::endl;
			//try to open the file incase invalid file name;
			std::cin >> _fileName;
			if (_fileName == "1") {
				bool found = false;
				std::string locChoice;
				std::wstring locDirFileName;
				std::cout << dlay->_directory << std::endl;
				while (!found) {
					std::wstring stemp = s2ws(dlay->_directory + "\\*");
					LPCWSTR dirwstr = stemp.c_str();
					HANDLE searchHandle = FindFirstFile(dirwstr, &winData);
					locDirFileName = winData.cFileName;
					std::cout << "Listing directory!" << std::endl;
					std::wcout << "First name" << locDirFileName << std::endl;
					//Only finds one file which so happens to be the same as the last folder in directory address? Returns Error 18
					do {
						//std::wcout << dirwstr << std::endl;
						std::wcout << winData.cFileName << std::endl;
					} while (FindNextFile(searchHandle, &winData));
					/*_com_error error(GetLastError());
					errorText = error.ErrorMessage();
					std::wcout << "Error Code is: " << errorText << std::endl;*/
					SetConsoleTextAttribute(searchHandle, FOREGROUND_RED | BACKGROUND_BLUE | FOREGROUND_INTENSITY);

					std::cout << std::endl << "Enter up to go up a directory level" << std::endl << "Alternatively type the folder name to enter." << std::endl << "OR type exit if filename is found" << std::endl;
					std::cin >> locChoice;
					if (locChoice == "exit" || locChoice == "Exit") {
						found = true;
					}
					else if (locChoice == "up" || locChoice == "Up")
					{
						//std::cout << dlay._directory.size() << locDirFileName.size() << dlay._directory << std::endl;
						//dlay._directory.pop_back();
						//dlay._directory.erase(dlay._directory.size() - 1, 1);
						
						std::size_t Textfound = dlay->_directory.find_last_of("/\\");
						std::cout << dlay->_directory << "Size:" << dlay->_directory.size() << "found: " << Textfound << std::endl;
						dlay->_directory = dlay->_directory.substr(0, Textfound);
						std::cout << dlay->_directory << "Size: " << dlay->_directory.size() << std::endl;
					}
					else {
						dlay->_directory = dlay->_directory += "\\" + locChoice;
					}
					//reverting back to the normal color
					SetConsoleTextAttribute(searchHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					FindClose(searchHandle);
				}
			}
			else {
				dlay->getCWD();
				std::ifstream infile;
				infile.open(dlay->_directory + "\\" + _fileName);
				if (infile.is_open()) { locVal = true; }
				else { std::cout << "Could not open file, try again!" << std::endl; }
			}
		}
		locVal = false;
		while (!locVal) {
			std::cout << " Please Select your container type: " << std::endl << "1: integer vector" << std::endl << "2: string vector" << std::endl << "3: integer list" << std::endl << "4: string list" << std::endl;
			std::cin >> _conChoice;
			conType = static_cast<dataLayer::_container_type>(_conChoice);
			for (int i = 0; i < dataLayer::enumTypeEnd; i++) {
				if (conType == i) { locVal = true; break; }
			}
			if (!locVal){
				std::cout << "Invalid container selection, try again" << std::endl;
			}
		}
		/*locVal = false;
		while (!locVal) {
			std::cout << " Please Select your data type:/n" << "1: string" << "2: int" << std::endl;
			std::cin >> _varType;
			if (_conChoice == 1 || _conChoice == 2) { locVal = true; }
			else { std::cout << "Invalid container selection, try again" << std::endl; }
		}*/
		locVal = false;
		while (!locVal) {
			std::cout << " Please Select your search type:/n" << "1: linear/n" << "2: element find/n" << "3: binary search" << std::endl;
			int search_type;
			// Doesnt work with matching to ENUM!!
			std::cin >> search_type;
			if (search_type >= 1 && search_type < 5) {
				locVal = true;
				srchType = static_cast<_searchType>(search_type); // static casting the int fed in to match the enums of search types.
			}
			else { std::cout << "Invalid container selection, try again" << std::endl; }


		}
		std::string tempFileName = dlay->_directory + "\\" + _fileName;
		std::cout << "Checking file name: " << tempFileName << std::endl;
		if (tempFileName.length() == 0) {
			throw std::exception("FileName is empty!");
		}
		searchTools::functionRouting(*dlay,srchType, conType, _varType, tempFileName);

	}
	catch (std::string err){
		std::cout << "Operation failed with fatal error: " << err << std::endl;
	}
	catch (std::exception& excep)
	{
		std::cout << "Exception thrown, reason: " << excep.what() << std::endl;
	}
}
void searchTools::functionRouting(dataLayer& dlayer, searchTools::_searchType srch, dataLayer::_container_type conType, std::size_t varType, std::string filename) { // change this to an error code return type yeah. Got err down there kk,
	//Can overload the functions, so do not need to know what type of variable per se. 
	//dataLayer dlayer;
	error_type err = func_passed;
	try {
		//read the file into relevant container, then pass to the searching algorithm. 
		//WE have to read file in and do the search that way.
		//Move the container selection into the data layer!
	//CONTAINER TYPE DEFINTION{ default = 0, vectorInt = 1, vectorString = 2, listInt = 3, listString = 4 };
		switch (conType) // Type of container
		{
		case 1: //Vector
				//int
			std::cout << "Please Enter the element you would like to find: " << std::endl;
			std::cin >> _intKey;
			if (_intKey == NULL) {
				throw "Nothing entered!";
				_found = true; // Whats this for
			}
			err = dlayer.containerFiller(filename, conType);
			if (err == func_passed) {
				switch (srch) {
				case 1: linearSearch(dlayer, _intKey, _intRec, true);  break; case 2: break; case 3: break; case 4: break; // fill in for every case
				}
			}
			else {
				throw std::invalid_argument("Filling Function failed, Cannot complete search!");
				err = function_fail;
			}
			
			break;
		case 2:
			//vect string
			std::cout << "Please Enter the element you would like to find: " << std::endl;
			std::cin >> _stringKey;
			if (_stringKey == "exit") {
				throw "Nothing entered!";
				_found = true; // Whats this for
			}
			err = dlayer.containerFiller(filename, conType);
			if (err == func_passed) {
				switch (srch) {
				case 1: linearSearch(dlayer, _stringKey, _stringRec, true);  break; case 2:  break; case 3: break; case 4: break; // fill in for every case
				}
			}
			else {
				throw std::invalid_argument("Filling Function failed, Cannot complete search!");
				err = function_fail;
			}
			break;
		case 3: //list int
			std::cout << "Please Enter the element you would like to find: " << std::endl;
			std::cin >> _intKey;
			if (_intKey == NULL) {
				throw "Nothing entered!";
				_found = true; // Whats this for
			}
			err = dlayer.containerFiller(filename, conType);
			if (err == func_passed) {
				switch (srch) {
				case 1: linearSearch(dlayer, _intKey, _intRec, false);  break; case 2:  break; case 3: break; case 4: break; // fill in for every case
				}
			}
			else {
				throw std::invalid_argument("Filling Function failed, Cannot complete search!");
				err = function_fail;
			}
			break;
		case 4: // list string

			break;
		}
	}
	catch (std::string error) {
		std::cout << "Program has thrown the following error:" << error << std::endl;
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}
	//So we choose Vector|List -> Int|String -> Linear | bubble etc..
	

}
//&Datalayer.intVector, 
bool searchTools::linearSearch(dataLayer& dlayer, std::size_t key, std::size_t rec, bool vec_list)
{
	Time timer;
	_found = false;
	std::size_t i = 0;
	
	if (dlayer.intList.size() <= 1 || dlayer.intList.size() == NULL) {
		throw "Container is empty, exiting operation";
	}
	std::cout << "Starting element find\n";
	//Need to make the time elements public or do not return the values.
	timer.clock_start();
	for (_listIntIT = dlayer.intList.begin(); _listIntIT != dlayer.intList.end(); _listIntIT++) {
		if (*_listIntIT == key){
			break;
		}
		/*if (i < dlayer->intList.size()) {
			_found = true;
		}*/
	}

	return _found;
}
bool searchTools::linearSearch(dataLayer& dlayer, std::string _stringKey, std::string _stringRec, bool vec_list)
{
	try {
		Time timer;
		_found = false;
		std::size_t i = 0;
		std::cout << "Setting up Linear Search" << std::endl;
		if (vec_list) { // true = vector
			if (dlayer.stringVector.empty()) { 
				throw std::invalid_argument("Container empty exiting search"); // Throw is causing an unhanled exception, char at memory location when doing a string
			}
			else {
				timer.clock_start();
				for (i; i < dlayer.stringVector.size(); i++)
				{
					if (dlayer.stringVector[i] == _stringKey) {
						_found = true;
						//timer.clock_end();
						break;
					}
				}
				timer.duration();
			}
		}
		else // false = list
		{
			if (dlayer.stringList.size() == 0) { throw "Container empty, exiting search"; }

		}
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}
	return _found;
}
bool searchTools::elementFind(std::list<std::size_t> &list, std::size_t key) //Finding an element in a int List. 
{
	_found = false;
	Time timer;
	try{
		std::cout << "Checking container for elements\n";
		if (list.size() <= 1 || list.size() == NULL){
            	throw "Container is empty, exiting operation";
			}
		std::cout << "Starting element find\n";
		//Need to make the time elements public or do not return the values.
		timer.clock_start();
		for (_listIntIT = list.begin(); _listIntIT != list.end(); _listIntIT++){
			if (*_listIntIT == key)
			{
				_found = true;
			}
		}
		timer.clock_end();
		timer.duration();
	}
	catch (std::string e){
		std::cout << "The operation has failed for the following reason: " << e << std::endl;
	}
	return _found;
}
bool searchTools::elementFind(std::list<std::string> &list, std::string key)
{
	_found = false;


	return _found;
}
bool searchTools::elementFind(std::vector<std::size_t> &vector, std::size_t key)
{
	_found = false;

	return  _found;
}
bool searchTools::elementFind(std::vector<std::string> &vector, std::string)
{
	_found = false;

	return _found;
}