#include "stdafx.h"

DataContainer::DataContainer(){
	std::cout << "Container construction";
}
DataContainer::~DataContainer(){

}
std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString)
{
	for (unsigned int i = 0; i < vecString.size(); i++){
		out << vecString[i];
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::vector<int> &vecInt)
{
	for (unsigned int i = 0; i < vecInt.size(); i++){
		out << vecInt[i];
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::list<std::string>)
{
	return out;
}
std::ostream& operator << (std::ostream &out, std::list<int>)
{
	return out;
}