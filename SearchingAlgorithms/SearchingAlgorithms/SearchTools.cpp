#include "stdafx.h"

searchTools::searchTools(){
	_found = false; 
	Time timer;
}
searchTools::~searchTools(){

}
void searchTools::searchMenu()
{
	try {
		bool locVal = false;
		while (!locVal){
			std::cout << "Please enter in the file name you want to search or enter 1 to get directory list" << std::endl;
			//try to open the file incase invalid file name;
			std::cin >> _fileName;
			if (_fileName == "1") {
				std::cout << "Listing directory!" << std::endl;
				bool found = false;
				while (!found)
				{

				}
			} 
			dataLayer dlay;
			std::ifstream infile;
			infile.open(dlay._directory + "\\" + _fileName);
			if (infile.is_open()) { locVal = true; }
			else { std::cout << "Could not open file, try again!" << std::endl; }
		}
		while (!locVal){
			std::cout << " Please Select your container type:/n" << "1: Vector/n" << "2: List/n" << std::endl;
			std::cin >> _conChoice;
			if (_conChoice == 1 || _conChoice == 2) { locVal = true; }
			else { std::cout << "Invalid container selection, try again" << std::endl; }
		}
		locVal = false;
		while (!locVal){
			std::cout << " Please Select your container type:/n" << "1: int/n" << "2: string/n" << std::endl;
			std::cin >> _varType;
			if (_conChoice == 1 || _conChoice == 2) { locVal = true; }
			else { std::cout << "Invalid container selection, try again" << std::endl; }
		}
		locVal = false;
		while (!locVal){
			std::cout << " Please Select your search type:/n" << "1: linear/n" << "2: element find/n" <<"3: binary search" << std::endl;
			int search_type;
			_searchType srch;
			std::cin >> search_type;
			if (search_type == _searchType{}) {
				locVal = true;
				_searchType srchType = static_cast<_searchType>(search_type); // static casting the int fed in to match the enums of search types.
			}
			else { std::cout << "Invalid container selection, try again" << std::endl; }
			
			
		}
		locVal = false;
		switch (_conChoice)
		{
		case 1:
			//Vector
			switch (_varType){
			case 1:
				//String
				std::cout << "Please Enter the element you would like to find: " << std::endl;
				std::cin >> _stringKey;
				break;
			case 2:
				//Int
				std::cout << "Please Enter the element you would like to find: " << std::endl;
				std::cin >> _intKey;
				break;
			default:

				break;
			}
			break;
		case 2:
			//List
			switch (_varType){
			case 1:
				//String
				std::cout << "Please Enter the element you would like to find: " << std::endl;
				std::cin >> _stringKey;
				break;
			case 2:
				//Int
				std::cout << "Please Enter the element you would like to find: " << std::endl;
				std::cin >> _intKey;
				break;
			default:

				break;
			}
			break;
		default:
			throw "invalid container choice selection";
			break;
		}
		/*switch ()
		{
		default:
			break;
		}*/
		
	}
	catch (std::string err){
		std::cout << "Operation failed with fatal error: " << err << std::endl;
	}
}
bool searchTools::linearSearch(std::vector<int> &list, int size, int key, int*& rec)
{
	_found = false;
	int i;
	for (i = 0; i < size; i++){
		if (key == list[i]){
			break;
		}
		if (i < size) {
			_found = true;
			rec = &list[i];
		}
	}

	return _found;
}
bool searchTools::linearSearch(std::vector<std::string> &list, int size, int key, int*& rec)
{
	_found = false;

	return _found;
}
bool searchTools::linearSearch(std::list<int> &list, int size, int key, int*& rec)
{
	_found = false;

	return _found;
}
bool searchTools::linearSearch(std::list<std::string> &list, int size, int key, int*& rec)
{
	_found = false;

	return _found;
}
bool searchTools::elementFind(std::list<int> &list, int key) //Finding an element in a int List. 
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
bool searchTools::elementFind(std::vector<int> &vector, int key)
{
	_found = false;

	return  _found;
}
bool searchTools::elementFind(std::vector<std::string> &vector, std::string)
{
	_found = false;

	return _found;
}