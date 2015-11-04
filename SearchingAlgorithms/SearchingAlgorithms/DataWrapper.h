#pragma once
#ifndef DATA_WRAPPER_H
#define DATA_WRAPPER_H
#include "stdafx.h"
class DataWrapper
{
public:
	DataWrapper();
	~DataWrapper();
	std::string _directory;
	std::vector<std::size_t> intVector;
	std::list<std::size_t> intList;
	std::vector<std::string> stringVector;
	std::list<std::string> stringList;
	std::vector<std::vector<std::size_t>> vectorStorer;
	std::list<std::list<std::size_t>> listStorer;
	std::string _filename;
	_searchType srchType{ linear };
	_container_type conType{ vectorInt };

	void setUserChoices(_searchType srchType, _container_type conType);
	static std::string returnSrchType(_searchType srchType);
	static std::string returnConType(_container_type conType);
protected:
	
};

#endif