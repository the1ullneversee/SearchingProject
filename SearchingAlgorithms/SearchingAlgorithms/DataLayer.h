#ifndef DATALAYER_H
#define DATALAYER_H

#include "stdafx.h"
typedef  error_type ret_code;
class Menu;
class DataWrapper;
class dataLayer {
public:
	dataLayer();
	~dataLayer();
	dataLayer(const dataLayer&) = default;
	//dataLayer& operator=(const dataLayer&) = default; // Move and copy constructors 
	Menu* getMenu();
	void getCWD();
	void containerFillFromFile(std::string _filename);
	//void containerFillFromFile(dataLayer& dlayer);
	
	error_type readFile(dataLayer& dlay, _container_type con_type);
	error_type readFile(DataWrapper& dwrap, _container_type con_type);
	_container_type dataLayer::containerTypeSelectionRoutine();	
	ret_code saveFile(std::string filename, _container_type con_type, dataLayer &dataLayer_copy);
	ret_code linearNumbers(std::size_t amount, std::string fileName);
	ret_code randomNumbers();
	dataLayer::_container_type getUserConType();
	ret_code getFile(bool& functionAlive);
	std::ifstream inFile;
	std::ofstream ofFile;
	std::wstring s2ws(const std::string& s);
	ret_code printContainer(DataWrapper& dlayer, _container_type conType);
	//ret_code containerFiller(dataLayer& dlay);
	ret_code containerFiller(DataWrapper*& dwrap);
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