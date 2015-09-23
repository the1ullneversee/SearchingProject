#include "stdafx.h"
std::unique_ptr<Menu> menu(new Menu);
std::unique_ptr<Time> timer(new Time);
searchTools::~searchTools(){

}
std::wstring searchTools::s2ws(const std::string& s)
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

void searchTools::functionRouting(dataLayer& dlayer, searchTools::_searchType srch, dataLayer::_container_type conType, std::string filename) { // change this to an error code return type yeah. Got err down there kk,
	//Can overload the functions, so do not need to know what type of variable per se. 
	//dataLayer dlayer;
	error_type err = func_passed;
	dlayer._filename = filename;
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
				menu->errorToScreen("Nothing inputed", "function routing");
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
	try {
		_found = false;
		std::size_t i = 0;
		if (vec_list) {
			if (dlayer.intVector.size() <= 1) {
				throw std::exception("Container is empty, exiting operation");
			}
			std::cout << "Starting element find" << std::endl;
			timer->clock_start();
			for (rec; rec < dlayer.intVector.size(); rec++)
			{
				if (dlayer.intVector[rec] == key)
				{
					std::cout << "Element Found Postion in container: " << rec << std::endl;
					_found = true;
					timer->clock_end();
					break;
				}
				if (rec >= dlayer.intVector.size() && dlayer.intVector[rec] != key) {
					std::cout << "Could not find element in container, key: " << key << std::endl;
				}
			}
		}
		else {
			if (dlayer.intList.size() <= 1) {
				throw std::exception("Container is empty, exiting operation");
			}
			std::cout << "Starting element find" << std::endl;
			//Need to make the time elements public or do not return the values.
			timer->clock_start();
			for (_listIntIT = dlayer.intList.begin(); _listIntIT != dlayer.intList.end(); _listIntIT++) {
				if (*_listIntIT == key) {
					_found = true;
					timer->clock_end();
					break;
				}
				rec++;
				if (i <= dlayer.intList.size()) {
					std::cout << "No element found" << std::endl;
					_found = false;
					rec = 0;
				}
			}
		}
		if (_found)
		{
			timer->duration();
			timer->capture(dlayer, key, rec, timer->_duration);
		}
	}
	catch (std::exception& e){
		menu->errorToScreen(e, "Integer Linear Search");
	}
	return _found;
}
bool searchTools::linearSearch(dataLayer& dlayer, std::string _stringKey, std::string _stringRec, bool vec_list)
{
	try {
		_found = false;
		std::size_t i = 0;
		std::cout << "Setting up Linear Search" << std::endl;
		if (vec_list) { // true = vector
			if (dlayer.stringVector.empty()) { 
				throw std::invalid_argument("Container empty exiting search"); // Throw is causing an unhanled exception, char at memory location when doing a string
			}
			else {
				timer->clock_start();
				for (i; i < dlayer.stringVector.size(); i++)
				{
					if (dlayer.stringVector[i] == _stringKey) {
						_found = true;
						timer->clock_end();
						break;
					}
				}
				timer->duration();
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