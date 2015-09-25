#ifndef CONTAINERPRO_H
#define CONTAINERPRO_H
#pragma once
class ContainerPro {
public:
	ContainerPro();
	~ContainerPro();
	std::size_t IDWorked(std::size_t mainSize, std::vector<size_t>& IDsInUse);
	std::string fillMetaData(searchTools::_searchType srchType, dataLayer::_container_type conType, std::string time, std::size_t idToUse);
	std::size_t ContainerID; //The object ID instance
	std::string metaDataName;
	int container;
	void saveContainer(dataLayer& dlayerSwap, dataLayer::_container_type conType);
	std::vector<std::string> stringVect;
	std::vector<std::size_t> intVect;
	std::list<std::size_t> intList;
	std::list<std::string> stringList;
protected:

};


#endif CONTAINERPRO_H
