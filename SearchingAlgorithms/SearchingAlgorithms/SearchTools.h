#ifndef SEARCH_TOOLS_H
#define SEARCH_TOOLS_H
#include "stdafx.h"

class searchTools
{
public:
	searchTools()
	{
		_found = false;
		_alive = true;
	}
	~searchTools();
	unsigned int _conChoice;
	unsigned int _varType;
	bool _found;
	bool _alive;
	bool linearSearch(DataWrapper& dwrapper, std::size_t key, std::size_t rec, bool vec_list);
	bool linearSearch(DataWrapper& dwrapper,std::string stringKey,std::string stringRec, bool vec_list);
	bool elementFind(std::list<std::size_t> &list, std::size_t key);
	bool elementFind(std::list<std::string> &list, std::string key);
	bool elementFind(std::vector<std::size_t> &vector, std::size_t key);
	bool elementFind(std::vector<std::string> &vector, std::string);
	bool binarySearch(DataWrapper& dwrapper, std::size_t key, std::size_t rec, bool vec_list);
	static bool bubbleSort(std::vector<std::size_t> intVec);
	void searchFunctionRouting(DataWrapper& dwrapper);
	_searchType searchSelect();
	std::size_t _intKey;
	std::size_t _intRec;
	std::string _stringRec;
	std::string _stringKey;
	
private:
	
	std::vector<std::size_t>::const_iterator _vecIntIT;
	std::vector<std::string>::const_iterator _vecStringIT;
	std::list<std::size_t>::const_iterator _listIntIT;
	std::list<std::string>::const_iterator _listStringIT;
	

};

#endif SEARCH_TOOLS_H