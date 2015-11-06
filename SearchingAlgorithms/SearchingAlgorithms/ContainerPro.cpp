#include "stdafx.h"

ContainerPro::ContainerPro()
{
}

ContainerPro::~ContainerPro()
{
}
std::size_t ContainerPro::IDWorked(std::size_t mainSize, std::vector<size_t>& IDsInUse)
{
	bool found = false;
	std::size_t indexer = 0;
	for (indexer; indexer < mainSize; indexer++)
	{
		if (indexer == IDsInUse[indexer])
		{
			IDsInUse[indexer] = indexer;
		}
	}
	if (!found)
	{
		indexer = 0;
		indexer = indexer + IDsInUse.size();
		IDsInUse.push_back(indexer);
	}
	return indexer;
}
//WILL NEED A CONTAINER BROWSER TO UNFILL THE VECTORS.

// This also fills the ID number for the container reference.
std::string ContainerPro::fillMetaData(_searchType srchType, _container_type conType, std::string time, std::size_t idToUse, std::string origin) {
	std::string searchTypeString, ContainerTypeString;
	switch (conType)
	{
	case 1:
		ContainerTypeString = "Integer Vector ";
		break;
	case 2:
		ContainerTypeString = "String Vector ";
		break;
	case 3:
		ContainerTypeString = "Integer List ";
		break;
	case 4:
		ContainerTypeString = "String List ";
		break;
	}
	switch (srchType)
	{
	case 1:
		searchTypeString = "Linear Search ";
		break;
	case 2:
		searchTypeString = "Element Find ";
		break;
	case 3:
		searchTypeString = "Binary Search ";
		break;
	case 4:
		searchTypeString = "BubbleSort ";
		break;
	}
	ContainerID = idToUse;
	return searchTypeString + ContainerTypeString + time + origin;
}

void ContainerPro::saveContainer(DataWrapper& dwrapSwap)
{
	switch (dwrapSwap.getConType())
	{
	case 1:
		std::swap(dwrapSwap.intVector, intVect);
		break;
	case 2:
		std::swap(dwrapSwap.stringVector, stringVect);
		break;
	case 3:
		std::swap(dwrapSwap.intList, intList);
		break;
	case 4:
		std::swap(dwrapSwap.stringList, stringList);
		break;
	}
}
