#pragma once
#ifndef DATA_WRAPPER_H
#define DATA_WRAPPER_H
#include "stdafx.h"
class DataWrapper
{
public:
	DataWrapper();
	~DataWrapper();
	std::vector<std::size_t> intVector;
	std::list<std::size_t> intList;
	std::vector<std::string> stringVector;
	std::list<std::string> stringList;
	std::vector<std::vector<std::size_t>> vectorStorer;
	std::list<std::list<std::size_t>> listStorer;
	std::string getFilename();
	void setFilename(std::string filename);
	std::string getDirectory();
	void setDirectory(std::string directory);
	void dataCopier(std::string _directory, std::string _filename);
	void dataCopierFull(dataLayer& copDlay);
	void setUserChoices(_searchType srchType, _container_type conType);
	_container_type getConType();
	void setConType(_container_type conType);
	_searchType getSrchType();
	void setSearchType(_searchType srch);
	static std::string returnSrchTypeString(_searchType srchType);
	static std::string returnConTypeString(_container_type conType);
protected:
	std::string _directory;
	_searchType _srchType{ linear };
	_container_type _conType{ vectorInt };
	std::string _filename;
};

#endif