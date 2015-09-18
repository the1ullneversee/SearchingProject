#ifndef DATALAYER_H
#define DATALAYER_H

#include "stdafx.h"
#define ret int

class dataLayer {
public:
	dataLayer();
	~dataLayer();
	void getCWD();
	bool directoryList(LPCTSTR pstr);
	ret readFile(std::string filename, int containerSelection);
	ret saveFile(std::string filename, int containerSelection, dataLayer &dataLayer_copy);
	ret randomNumbers();
	std::ifstream inFile;
	std::ofstream ofFile;
	ret containerFiller(std::vector<int> intVector, std::string filename);
	ret containerFiller(std::vector<std::string> stringVector, std::string filename);
	ret containerFiller(std::list<int> intList, std::string filename);
	ret containerFiller(std::list<std::string> stringList, std::string filename);
	friend std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString);
	friend std::ostream& operator << (std::ostream &out, std::vector<int> &vecInt);
	friend std::ostream& operator << (std::ostream &out, std::list<std::string> &listString);
	friend std::ostream& operator << (std::ostream &out, std::list<int> &listInt);
	std::string _directory;
	std::vector<int> intVector;
	std::list<int> intList;
	std::vector<std::string> stringVector;
	std::list<std::string> stringList;
	std::vector<std::vector<int>> vectorStorer;
	std::list<std::list<int>> listStorer;
private:
	char _cBaseDirectory[FILENAME_MAX];
	
	// Define error return types for greater reporting 
	//enum error_type : int {};
	enum _container_type : int {default,vectorInt, vectorString, listInt, listString};
	int _ret;
	std::string _stringTemp;
	int _intTemp;
	int active_containers;
	int count;
	int index;
	int temp;
	bool active;
};

#endif