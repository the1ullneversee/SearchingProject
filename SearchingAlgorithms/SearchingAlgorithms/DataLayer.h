#ifndef DATALAYER_H
#define DATALAYER_H

#include "stdafx.h"
typedef  error_type ret_code;

class dataLayer {
public:
	dataLayer();
	~dataLayer();
	void getCWD();
	bool directoryList(LPCTSTR pstr);
	enum _container_type : int { default = 0, vectorInt = 1, vectorString = 2, listInt = 3, listString = 4, enumTypeEnd = 5 };
	error_type readFile(std::string filename, dataLayer::_container_type con_type);
	ret_code saveFile(std::string filename, int containerSelection, dataLayer &dataLayer_copy);
	ret_code randomNumbers();
	std::ifstream inFile;
	std::ofstream ofFile;
	
	ret_code containerFiller(std::string filename, dataLayer::_container_type conType);

	friend std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString);
	friend std::ostream& operator << (std::ostream &out, std::vector<std::size_t> &vecInt);
	friend std::ostream& operator << (std::ostream &out, std::list<std::string> &listString);
	friend std::ostream& operator << (std::ostream &out, std::list<std::size_t> &listInt);
	std::string _directory;
	std::vector<std::size_t> intVector;
	std::list<std::size_t> intList;
	std::vector<std::string> stringVector;
	std::list<std::string> stringList;
	std::vector<std::vector<std::size_t>> vectorStorer;
	std::list<std::list<std::size_t>> listStorer;
private:
	char _cBaseDirectory[FILENAME_MAX];
	
	// Define error return types for greater reporting 
	
	
	int _ret;
	std::string _stringTemp;
	std::size_t _intTemp;
	int active_containers;
	std::size_t count;
	std::size_t index;
	int temp;
	bool active;
};

#endif