#ifndef SEARCH_TOOLS_H
#define SEARCH_TOOLS_H
#include "stdafx.h"

class searchTools
{
public:
	searchTools();
	~searchTools();
	virtual bool linearSearch(std::vector<int> &list, int size, int key, int*& rec);
	virtual bool linearSearch(std::vector<std::string> &list, int size, int key, int*& rec);
	virtual bool linearSearch(std::list<int> &list, int size, int key, int*& rec);
	virtual bool linearSearch(std::list<std::string> &list, int size, int key, int*& rec);
	bool elementFind(std::list<int> &list, int key);
	bool elementFind(std::list<std::string> &list, std::string key);
	bool elementFind(std::vector<int> &vector, int key);
	bool elementFind(std::vector<std::string> &vector, std::string);
	void searchMenu();
private:
	unsigned int _conChoice = NULL;
	enum _searchType : int { linear, elementFind, binary, bubbleSort };
	unsigned int _varType = NULL;
	bool _found;
	int _intKey;
	std::string _fileName;
	std::string _stringKey;
	std::vector<int>::const_iterator _vecIntIT;
	std::vector<std::string>::const_iterator _vecStringIT;
	std::list<int>::const_iterator _listIntIT;
	std::list<std::string>::const_iterator _listStringIT;

};

#endif SEARCH_TOOLS_H