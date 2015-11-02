#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#pragma once
typedef error_type ret;
#include "stdafx.h"
class dataLayer;
class ContainerPro;
class Menu
{
public:
	Menu();
	~Menu();
	dataLayer* getDataLayer();
	ret searchMenu(Menu& menu);
	ret timeMenu();
	ret dataMenu();
	void mainMenu();
	ret multiContainersJoin(std::vector<std::thread>& threadVec);
	void errorToScreen(std::exception& excpt, std::string functionName);
	void errorToScreen(std::invalid_argument& invArg, std::string functionName);
	void errorToScreen(std::string strErr, std::string functionName);
	ret textToScreen(std::string); // Want a function to output errors and stuff to screen.
	bool functionReRouting;
	ret clearScreen();
	ret changeColourScreen(std::string textColour, std::string backgroundColour);
protected:
	std::vector<std::unique_ptr<ContainerPro>> containerMaster;
	std::vector<std::size_t> IDsInUse;
	bool menuReRouting;
	dataLayer* dlayerMain; // Might still need this. 
	//dataLayer* dlayerMain;
	//WE gonna store some references to pass around super sneaky style. 
	//searchTools &searchToolsMaster;
private:
	enum menuItems : int { searching = 1, data_functions = 2, time_functions = 3, ENDOFMenuEnum = 4 };
	enum colour : int {Black = 0, Blue = 1, Green = 2, Aqua = 3, Red = 4, Purple = 5, Yellow = 6, White =7};
	enum dataMenuItems : int { CreateContainer = 1, PrintContainer = 2, SaveAContainer = 3, LoadAContainer = 4, ENDOFDataMenuEnum = 5 };
};



#endif MAIN_MENU_H