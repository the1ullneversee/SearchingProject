#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#pragma once
typedef error_type ret;
#include "stdafx.h"
class Menu// Access to protected values so we can output to screen easier
{
public:
	Menu();
	~Menu();
	ret searchMenu();
	ret timeMenu();
	ret dataMenu();
	void mainMenu();
	void errorToScreen(std::exception& excpt, std::string functionName);
	void errorToScreen(std::invalid_argument& invArg, std::string functionName);
	void errorToScreen(std::string strErr, std::string functionName);
	ret textToScreen(std::string); // Want a function to output errors and stuff to screen.
	ret printContainer(dataLayer& dlayer, dataLayer::_container_type conType);
	ret clearScreen();
	ret changeColourScreen(std::string textColour, std::string backgroundColour);
protected:
	friend std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString);
	friend std::ostream& operator << (std::ostream &out, std::vector<std::size_t> &vecInt);
	friend std::ostream& operator << (std::ostream &out, std::list<std::string> &listString);
	friend std::ostream& operator << (std::ostream &out, std::list<std::size_t> &listInt);
private:
	enum menuItems : int { searching = 1, data_functions = 2, time_functions = 3, ENDOFENUM = 4 };
	enum colour : int {Black = 0, Blue = 1, Green = 2, Aqua = 3, Red = 4, Purple = 5, Yellow = 6, White =7};
};



#endif MAIN_MENU_H