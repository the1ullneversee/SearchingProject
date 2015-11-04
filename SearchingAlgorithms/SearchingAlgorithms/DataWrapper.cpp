#include "stdafx.h"

DataWrapper::DataWrapper()
{

}
DataWrapper::~DataWrapper()
{

}

void DataWrapper::setUserChoices(_searchType srchType, _container_type conType)
{
	this->srchType = srchType;
	this->conType = conType;
}

std::string DataWrapper::returnSrchType(_searchType srchType)
{
	std::string returnString = "";
	try {
		switch (srchType)
		{
		case 1: returnString = "Linear Search"; break;
		case 2: returnString = "Element find"; break;
		case 3: returnString = "Binary Search"; break;
		case 4: returnString = "Bubble Sort"; break;
		default: throw std::exception("Could not match the search type");
			break;
		}
	}
	catch (std::exception& e)
	{
		Menu::errorToScreen(e, "Returning Search Type!");
	}
	return std::string();
}

std::string DataWrapper::returnConType(_container_type conType)
{
	std::string returnString = "";
	try {
		switch (conType)
		{
		case 1: returnString = "Integer Vector"; break;
		case 2: returnString = "String Vector"; break;
		case 3: returnString = "Integer List"; break;
		case 4: returnString = "String List"; break;
		default: throw std::exception("Could not match the search type");
			break;
		}
	}
	catch (std::exception& e)
	{
		Menu::errorToScreen(e, "Returning Search Type!");
	}
	return returnString;
}
