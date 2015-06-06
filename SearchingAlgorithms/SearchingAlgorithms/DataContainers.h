#ifndef DATA_CONTAINER_H
#define DATA_CONTAINER_H

#include "stdafx.h"

class DataContainer
{
public:
	DataContainer();
	~DataContainer();
	std::vector<int> intVector;
	std::list<int> intList;
	std::vector<std::string> stringVector;
	std::list<std::string> stringList;
	std::vector<std::vector<int>> vectorStorer;
	std::list<std::list<int>> listStorer;
	friend std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString);
	friend std::ostream& operator << (std::ostream &out, std::vector<int> &vecInt);
	friend std::ostream& operator << (std::ostream &out, std::list<std::string>);
	friend std::ostream& operator << (std::ostream &out, std::list<int>);
private:
	int active_containers;
	int count;
	int index;
	int temp;
	bool active;
};

#endif DATA_CONTAINER_H