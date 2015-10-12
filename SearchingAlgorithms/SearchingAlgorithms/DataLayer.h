#ifndef DATALAYER_H
#define DATALAYER_H

#include "stdafx.h"
typedef  error_type ret_code;
class Menu;
class dataLayer {
public:
	dataLayer();
	~dataLayer();
	Menu* getMenu();
	void getCWD();
	void containerFillFromFile(dataLayer& dlayer);
	enum _container_type : int { default = 0, vectorInt = 1, vectorString = 2, listInt = 3, listString = 4, enumTypeEnd = 5 };
	error_type readFile(std::string filename, dataLayer::_container_type con_type);
	_container_type dataLayer::containerTypeSelectionRoutine();
	ret_code saveFile(std::string filename, dataLayer::_container_type con_type, dataLayer &dataLayer_copy);
	ret_code randomNumbers();
	dataLayer::_container_type getUserConType();
	ret_code getFile(bool& functionAlive);
	std::ifstream inFile;
	std::ofstream ofFile;
	std::wstring s2ws(const std::string& s);
	ret_code printContainer(dataLayer& dlayer, dataLayer::_container_type conType);
	ret_code containerFiller(std::string filename, dataLayer::_container_type conType);
	std::string _directory;
	std::vector<std::size_t> intVector;
	std::list<std::size_t> intList;
	std::vector<std::string> stringVector;
	std::list<std::string> stringList;
	std::vector<std::vector<std::size_t>> vectorStorer;
	std::list<std::list<std::size_t>> listStorer;
	std::string _filename;
protected:
	Menu* menu;
	friend std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString);
	friend std::ostream& operator << (std::ostream &out, std::vector<std::size_t> &vecInt);
	friend std::ostream& operator << (std::ostream &out, std::list<std::string> &listString);
	friend std::ostream& operator << (std::ostream &out, std::list<std::size_t> &listInt);

private:
	char _cBaseDirectory[FILENAME_MAX];
	int _ret;
	std::string _stringTemp;
	std::size_t _intTemp;
	int active_containers;
	std::size_t _completion;
	std::size_t _fileSize;
	std::size_t count;
	std::size_t index;
	int temp;
	bool active;
};

#endif