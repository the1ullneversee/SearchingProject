#include "stdafx.h"
std::unique_ptr<Time> timer(new Time);
std::unique_ptr<Menu> menu(new Menu);
searchTools::~searchTools(){

}


void searchTools::searchFunctionRouting(DataWrapper& dwrapper) { // change this to an error code return type yeah. Got err down there kk,
	//Can overload the functions, so do not need to know what type of variable per se. 
	//dataLayer dlayer;
	error_type err = func_passed;
	bool wantToSearch = true;
	std::string userChoice;
	try {
		while (wantToSearch) {
			//menu->clearScreen();
			switch (dwrapper.conType) // Type of container
			{
			case 1: //Vector
					//int
				std::cout << "Please Enter the element you would like to find: " << std::endl;
				std::cin >> _intKey;
				if (_intKey == NULL) {
					menu->errorToScreen("Nothing inputed", "function routing");
					_found = true; // Whats this for
				}
				switch (dwrapper.srchType) {
					//-> change
				case 1: linearSearch(dwrapper, _intKey, _intRec, true);  break;
				case 2: break;
				case 3: binarySearch(dwrapper, _intKey, _intRec, true); break;
				case 4: break; // fill in for every case
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

				switch (dwrapper.srchType) {
					//-> change
				case 1: linearSearch(dwrapper, _stringKey, _stringRec, true);  break;
				case 2: break;
				case 3: std::cout << "Cannot perfrom this type of search :( " << std::endl; break;
				case 4: break; // fill in for every case
				}
				break;
			case 3: //list int
				std::cout << "Please Enter the element you would like to find: " << std::endl;
				std::cin >> _intKey;
				if (_intKey == NULL) {
					throw "Nothing entered!";
					_found = true; // Whats this for
				}
				switch (dwrapper.srchType) {
					//-> change
				case 1: linearSearch(dwrapper, _intKey, _intRec, false);  break;
				case 2: break;
				case 3: binarySearch(dwrapper, _intKey, _intRec, false); break;
				case 4: break; // fill in for every case
				}
				break;
			case 4: // list string
				std::cout << "Please Enter the element you would like to find: " << std::endl;
				std::cin >> _stringKey;
				if (_stringKey == "") {
					throw "Nothing entered!";
					_found = true; // Whats this for
				}
				switch (dwrapper.srchType) {
					//-> change
				case 1: linearSearch(dwrapper, _stringKey, _stringRec, false);  break;
				case 2: break;
				case 3: std::cout << "Cannot perfrom this type of search :( " << std::endl; break;
				case 4: break; // fill in for every case
				}
				break;
			}

			std::cout << "Enter 'search' to search the container again" << std::endl << "Or enter 'exit' to go back to search menu." << std::endl;
			std::cin >> userChoice;
			if (userChoice == "exit" || userChoice == "Exit") { wantToSearch = false; }
		}
	}
	catch (std::string error) {
		std::cout << "Program has thrown the following error:" << error << std::endl;
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}
}
_searchType searchTools::searchSelect()
{
	_searchType srchType = _searchType::findElement;
	bool locVal = false;
	while (!locVal) {
		//{ linear = 1, findElement = 2, binary = 3, bubbleSort = 4, EndOfSearchEnum = 5 }
		std::cout << " Please Select your search type:" << "1: linear" << std::endl << "2: element find" << std::endl << "3: binary search" << std::endl;
		int search_type;
		// Doesnt work with matching to ENUM!!
		std::cin >> search_type;
		srchType = static_cast<_searchType>(search_type);
		for (int i = 0; i < EndOfSearchEnum; i++) {
			if (srchType == i) { locVal = true; break; }
		}
		if (!locVal) {
			std::cout << "Invalid container selection, try again" << std::endl;
		}
	}
	return srchType;
}
//&Datalayer.intVector, 
bool searchTools::linearSearch(DataWrapper& dwrapper, std::size_t key, std::size_t rec, bool vecORList)
{
	try {
		_found = false;
		std::size_t i = 0;
		rec = 0;
		if (vecORList) {
			if (dwrapper.intVector.size() <= 1) {
				throw std::exception("Container is empty, exiting operation");
			}
			std::cout << "Starting element find" << std::endl;
			timer->clock_start();
			for (rec; rec <= dwrapper.intVector.size() -1; rec++)
			{
				if (dwrapper.intVector[rec] == key)
				{
					std::cout << "Element Found Postion in container: " << rec << std::endl;
					_found = true;
					timer->clock_end();
					break;
				}
			}
			if (!_found) {
					std::cout << "Could not find element in container, key: " << key << std::endl;
					timer->clock_end();
			}
		}
		else {
			if (dwrapper.intList.size() <= 1) {
				throw std::exception("Container is empty, exiting operation");
			}
			std::cout << "Starting element find" << std::endl;
			//Need to make the time elements public or do not return the values.
			timer->clock_start();
			for (_listIntIT = dwrapper.intList.begin(); _listIntIT != dwrapper.intList.end(); _listIntIT++) {
				if (*_listIntIT == key) {
					std::cout << "Found the element, position: " << rec << std::endl;
					_found = true;
					timer->clock_end();
					break;
				}
				rec++;
			}
			if(!_found)
			{
				rec = 0;
				std::cout << "No element found" << std::endl;
				timer->clock_end();
			}
		}
		timer->duration();
		timer->capture(dwrapper._filename, std::to_string(key), rec, timer->_duration, "linearSearch", vecORList, _found);
	}
	catch (std::exception& e){
		menu->errorToScreen(e, "Integer Linear Search");
	}
	return _found;
}
bool searchTools::linearSearch(DataWrapper& dwrapper, std::string _stringKey, std::string _stringRec, bool vec_list)
{
	_found = false;
	std::size_t i = 0;
	std::size_t findPos = 0;
	try {
		std::cout << "Setting up Linear Search" << std::endl;
		if (vec_list) { // true = vector
			if (dwrapper.stringVector.empty()) {
				throw std::invalid_argument("Container empty exiting search"); // Throw is causing an unhanled exception, char at memory location when doing a string
			}
			else {
				timer->clock_start();
				for (i; i < dwrapper.stringVector.size(); i++)
				{
					findPos = dwrapper.stringVector[i].find(_stringKey);
					if (findPos != std::string::npos) {
						_found = true;
						timer->clock_end();
						break;
					}
				}
				if (!_found)
				{
					Menu::errorToScreen("No element found", "Vector linear search");
				}
				timer->clock_end();
				timer->duration();
			}
		}
		else // false = list
		{
			std::string tempString;
			if (dwrapper.stringList.size() == 0) { throw "Container empty, exiting search"; }
			timer->clock_start();
			for (_listStringIT = dwrapper.stringList.begin(); _listStringIT != dwrapper.stringList.end(); _listStringIT++)
			{
				tempString = *_listStringIT;
				findPos = tempString.find(_stringKey);
				if (findPos != std::string::npos)
				{
					_found = true;
					timer->clock_end();
					break;
				}
			}
			if (!_found)
			{
				Menu::errorToScreen("No element found", "String linear search");
			}
			timer->clock_end();
			timer->duration();
		}
		if (findPos == std::string::npos)
		{
			findPos = 0;
		}
		timer->capture(dwrapper._filename, _stringKey, findPos, timer->_duration, "linearSearch", vec_list, _found);
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}
	return _found;
}
bool searchTools::elementFind(std::list<std::size_t> &list, std::size_t key) //Finding an element in a int List. 
{
	_found = false;
	try{
		std::cout << "Checking container for elements\n";
		if (list.size() <= 1 || list.size() == NULL){
            	throw "Container is empty, exiting operation";
			}
		std::cout << "Starting element find\n";
		//Need to make the time elements public or do not return the values.
		timer->clock_start();
		for (_listIntIT = list.begin(); _listIntIT != list.end(); _listIntIT++){
			if (*_listIntIT == key)
			{
				_found = true;
			}
		}
		timer->clock_end();
		timer->duration();
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
bool searchTools::binarySearch(DataWrapper& dwrapper, std::size_t key, std::size_t rec, bool vec_list)
{
	bool found = false;
	try {
		bool active = true;
		std::size_t mid = 0;
		std::size_t i = 0;
		std::size_t low = 1;
		std::size_t max = dwrapper.intVector.size();
		std::cout << "For this search to work the list must be sorted!" << std::endl;
		timer->clock_start();
		if (vec_list)
		{
			while (active)
			{
				mid = low + (max - low) / 2;
				if (dwrapper.intVector[mid] == key)
				{
					found = true;
					active = false;
				}
				else if (dwrapper.intVector[mid] < key)
				{
					low = mid + 1;
				}
				else if (dwrapper.intVector[mid] > key)
				{
					max = mid - 1;
				}
				i++;
			}
			timer->clock_end();
			if (!found)
			{
				std::cout << "Could not find the element in the list" << std::endl;
			}
			else {
				timer->duration();
				std::cout << "Found the element!" << std::endl;
				timer->capture(dwrapper._filename, std::to_string(key), i, timer->_duration,"Binary Search", vec_list, found);
			}
		}
		else {

		}
	}
	catch (std::exception& e)
	{
		Menu::errorToScreen(e, "Binary Search");
	}
	return found;
}