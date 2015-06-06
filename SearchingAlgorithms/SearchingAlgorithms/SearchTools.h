#ifndef SEARCH_TOOLS_H
#define SEARCH_TOOLS_H


class searchTools
{
public:
	searchTools();
	~searchTools();
	virtual bool linearSearch(std::vector<int> &list, int size, int key, int*& rec);
	virtual bool linearSearch(std::vector<std::string> &list, int size, int key, int*& rec);
	virtual bool linearSearch(std::list<int> &list, int size, int key, int*& rec);
	virtual bool linearSearch(std::list<std::string> &list, int size, int key, int*& rec);
	bool elementFind();
private:
	bool _found;
	int _intKey;
	std::string _stringKey;

};

#endif SEARCH_TOOLS_H