#ifndef SEARCH_TOOLS_H
#define SEARCH_TOOLS_H
#include "stdafx.h"

class searchTools
{
public:
	searchTools();
	~searchTools();
	virtual bool linearSearch(dataLayer *dlayer, int key, int rec, bool vec_list);
	virtual bool linearSearch(dataLayer *dlayer,std::string stringKey,std::string stringRec, bool vec_list);
	bool elementFind(std::list<int> &list, int key);
	bool elementFind(std::list<std::string> &list, std::string key);
	bool elementFind(std::vector<int> &vector, int key);
	bool elementFind(std::vector<std::string> &vector, std::string);
	void searchMenu();
private:
	unsigned int _conChoice = NULL;
	enum _searchType : int { linear = 1, findElement = 2, binary = 3, bubbleSort = 4 };
	enum _containerType : int {vector = 1, list = 2};
	unsigned int _varType = NULL;
	bool _found;
	int _intKey;
	int _intRec;
	std::string _stringRec;
	std::string _fileName;
	std::string _stringKey;
	std::vector<int>::const_iterator _vecIntIT;
	std::vector<std::string>::const_iterator _vecStringIT;
	std::list<int>::const_iterator _listIntIT;
	std::list<std::string>::const_iterator _listStringIT;
	void functionRouting(dataLayer *dlayer, searchTools::_searchType srch, searchTools::_containerType conType, int varType, std::string filename);

};

#endif SEARCH_TOOLS_H