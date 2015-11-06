#include "stdafx.h"

DataWrapper::DataWrapper()
{
	this->_conType = _container_type::default;
	this->_srchType = _searchType::defaults;
	this->_filename = "default";
	this->_directory = "default";
}
DataWrapper::~DataWrapper()
{
}

void DataWrapper::dataCopier(std::string _directory, std::string _filename)
{
	this->_directory = _directory;
	this->_filename = _filename;
}

std::string DataWrapper::getFilename()
{
	return this->_filename;
}

void DataWrapper::setFilename(std::string filename)
{
	this->_filename = filename;
}

std::string DataWrapper::getDirectory()
{
	return this->_directory;
}

void DataWrapper::setDirectory(std::string directory)
{
	this->_directory = directory;
}

_container_type DataWrapper::getConType()
{
	if (this->_conType)
		return this->_conType;
	else
		return default;
}

void DataWrapper::setConType(_container_type conType)
{
	this->_conType = conType;
}

_searchType DataWrapper::getSrchType()
{
	return this->_srchType;
}

void DataWrapper::setSearchType(_searchType srch)
{
	this->_srchType = srch;
}

void DataWrapper::dataCopierFull(dataLayer & copDlay)
{

}

void DataWrapper::setUserChoices(_searchType srchType, _container_type conType)
{
	setSearchType(srchType);
	setConType(conType);
}

std::string DataWrapper::returnSrchTypeString(_searchType srchType)
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

std::string DataWrapper::returnConTypeString(_container_type conType)
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
