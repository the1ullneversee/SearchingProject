#include "stdafx.h"

searchTools::searchTools(){
	_found = false; 
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
	return _found;
}
bool searchTools::linearSearch(std::list<int> &list, int size, int key, int*& rec)
{
	return _found;
}
bool searchTools::linearSearch(std::list<std::string> &list, int size, int key, int*& rec)
{
	return _found;
}
bool searchTools::elementFind()
{
	return _found;
}