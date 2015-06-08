#include "stdafx.h"

searchTools::searchTools(){
	_found = false; 
	Time timer;
}
searchTools::~searchTools(){

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
bool searchTools::elementFind(std::list<int> &list, int key)
{
	_found = false;
	Time timer;
	try{
		std::cout << "Checking container for elements\n";
		if (list.size() <= 1 || list.size() == NULL){
			std::cout << "Container is empty, exiting operation\n";
			throw; 
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
	catch (...){
		std::cout << "Element find operation has failed\n";
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