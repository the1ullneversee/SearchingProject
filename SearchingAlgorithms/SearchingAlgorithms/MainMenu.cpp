
#include "stdafx.h"
Menu::Menu()
{

}
Menu::~Menu()
{

}
void Menu::mainMenu()
{
	error_type err = func_passed;
	bool Alive = true;
	int choice = 0;
	bool valid = false;
	changeColourScreen("Blue", "Black");
	std::cout << "Welcome to the Searching Utility Application." << std::endl << "Use this application to perform different searches on different C++ container types!" << std::endl;
	while (Alive) {
		std::cout << "Here is the Menu enter the corresponding function number to proceed!" << std::endl;
		changeColourScreen("Red", "Black");
		while (!valid) {
			std::cout << "1. Searching Functions" << std::endl
				<< "2. Data Functions" << std::endl
				<< "3. Time Functions" << std::endl;
			std::cin >> choice;
			for (int i = 0; i < ENDOFENUM; i++)
			{
				if (choice == i)
				{
					valid = true;
					break;
				}
			}
			if (!valid)
			{
				errorToScreen("Bad Input, Please choose again. Loading Menu...", "Menu");
			}
		}
		valid = false;
		menuItems menuItms = static_cast<menuItems>(choice);
		switch (menuItms)
		{
		case 1:
			clearScreen();
			err = searchMenu();
			break;
		case 2:
			clearScreen();
			err = dataMenu();
			break;
		case 3:
			clearScreen();
			err = timeMenu();
			break;
		default:
			errorToScreen("Oops invalid selection, restarting application!", "Menu main");
			break;
		}
		if (err == killApplication)
		{
			Alive = false;
		}
		clearScreen();
	}
}
ret Menu::textToScreen(std::string stringToScreen) {
	error_type locRet = func_passed;
	//If we had large values to print, look to preload OS stream buffer. YEAH!
	std::cout << stringToScreen << std::endl;
	return locRet;
}
std::ostream& operator << (std::ostream &out, std::vector<std::string> &vecString)
{
	for (std::size_t i = 0; i < vecString.size(); i++) {
		out << vecString[i] << " ";
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::vector<std::size_t> &vecInt)
{
	for (std::size_t i = 0; i < vecInt.size(); i++) {
		out << vecInt[i] << " ";
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::list<std::string> &listString)
{
	for (std::list<std::string>::const_iterator i = listString.begin(); i != listString.end(); i++)
	{
		out << *i << " ";
	}
	return out;
}
std::ostream& operator << (std::ostream &out, std::list<std::size_t> &listInt)
{
	for (std::list<std::size_t>::const_iterator i = listInt.begin(); i != listInt.end(); i++)
	{
		out << *i << " ";
	}

	return out;
}
ret Menu::printContainer(dataLayer& dlayer, dataLayer::_container_type conType) {
	error_type error = func_passed;// Think we need a better way of doing this.
	//Need a switch statement here to print the different container types to screen. Can do some fancy formatting. 
	try {
		switch (conType)
		{
		case 1:

			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}
		clearScreen();
	}
	catch (std::exception& e)
	{

	}
	return error;
}
ret Menu::clearScreen() {

	COORD topLeft = { 0,0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	SetConsoleCursorPosition(console, topLeft);

	return func_passed;
}
ret Menu::changeColourScreen(std::string textColour, std::string backgroundColour)
{
	
	/*switch (colour) {
	case 1:
		break;
	}*/
	//0 = Black 8 = Gray
	//1 = Blue 9 = Light Blue
	//2 = Green a = Light Green
	//3 = Aqua b = Light Aqua
	//4 = Red c = Light Red
	//5 = Purple d = Light Purple
	//6 = Yellow e = Light Yellow
	//7 = White f = Bright White

	//clearScreen();
	system("color 0f");
	//std::cout << "This is your new console colour!" << std::endl;
	return func_passed;
}
void Menu::errorToScreen(std::exception& e, std::string functionName) {
	changeColourScreen("red", "black");
	std::cout << std::endl << "The function " << functionName << "has failed with the following exception: " << std::endl << e.what() << std::endl;
}
void Menu::errorToScreen(std::invalid_argument& invArg, std::string functionName) {
	std::cout << std::endl << "The function " << functionName << "has failed with the following invalid argument: " << std::endl << invArg.what() << std::endl;
}
void Menu::errorToScreen(std::string strErr, std::string functionName) {
	std::cout << std::endl << "The function " << functionName << "has failed with the following error message: " << std::endl << strErr << std::endl;
}
ret Menu::searchMenu()
{
	bool _alive = true;
	bool locVal = false;
	error_type ret_err = func_passed;
	std::unique_ptr<searchTools> search(new searchTools);
	std::unique_ptr<dataLayer> dlay(new dataLayer);
	while (_alive) {
		try {

			searchTools::_searchType srch = searchTools::linear;
			searchTools::_searchType srchType = searchTools::linear;
			WIN32_FIND_DATA winData;
			dataLayer::_container_type conType = dataLayer::vectorInt;
			//std::wstring stemp = s2ws("C:\\Users\\thomaskn\\Downloads\\*");
			LPCTSTR errorText = NULL;

			while (!locVal) {
				std::cout << "Please enter in the file name you want to search" << std::endl << "Enter 1 to get local file list" << std::endl << "Enter exit  to go back to main menu" << std::endl;
				//try to open the file incase invalid file name;
				std::cin >> search->_fileName;
				if (search->_fileName == "exit" || search->_fileName == "Exit") {
					locVal = true;
					_alive = false;
				}
				else if (search->_fileName == "1") {
					bool found = false;
					clearScreen();
					std::string locChoice;
					std::wstring locDirFileName;
					std::cout << dlay->_directory << std::endl;
					while (!found) {

						std::wstring stemp = search->s2ws(dlay->_directory + "\\*");
						LPCWSTR dirwstr = stemp.c_str();
						HANDLE searchHandle = FindFirstFile(dirwstr, &winData);
						locDirFileName = winData.cFileName;
						std::cout << "Listing directory!" << std::endl;
						//Only finds one file which so happens to be the same as the last folder in directory address? Returns Error 18
						do {
							//std::wcout << dirwstr << std::endl;
							std::wcout << winData.cFileName << std::endl;
						} while (FindNextFile(searchHandle, &winData));
						changeColourScreen("blue", "Red");
						std::cout << std::endl << "Enter up to go up a directory level" << std::endl << "Alternatively type the folder name to enter." << std::endl << "OR type exit if filename is found" << std::endl;
						std::cin >> locChoice;
						if (locChoice == "exit" || locChoice == "Exit") {
							found = true;
						}
						else if (locChoice == "up" || locChoice == "Up")
						{

							std::size_t Textfound = dlay->_directory.find_last_of("/\\");
							std::cout << dlay->_directory << "Size:" << dlay->_directory.size() << "found: " << Textfound << std::endl;
							dlay->_directory = dlay->_directory.substr(0, Textfound);
							std::cout << dlay->_directory << "Size: " << dlay->_directory.size() << std::endl;
						}
						else {
							dlay->_directory = dlay->_directory += "\\" + locChoice;
						}
						//reverting back to the normal color
						FindClose(searchHandle);
					}
				}
				else {
					dlay->getCWD();
					std::ifstream infile;
					infile.open(dlay->_directory + "\\" + search->_fileName);
					if (infile.is_open()) { locVal = true; }
					else { std::cout << "Could not open file, try again!" << std::endl; }
				}
			}
			if (_alive) {
				locVal = false;
				while (!locVal) {
					std::cout << " Please Select your container type: " << std::endl << "1: integer vector" << std::endl << "2: string vector" << std::endl << "3: integer list" << std::endl << "4: string list" << std::endl;
					std::cin >> search->_conChoice;
					conType = static_cast<dataLayer::_container_type>(search->_conChoice);
					for (int i = 0; i < dataLayer::enumTypeEnd; i++) {
						if (conType == i) { locVal = true; break; }
					}
					if (!locVal) {
						std::cout << "Invalid container selection, try again" << std::endl;
					}
				}
				locVal = false;
				while (!locVal) {
					std::cout << " Please Select your search type:" << "1: linear" << std::endl << "2: element find" << std::endl << "3: binary search" << std::endl;
					int search_type;
					// Doesnt work with matching to ENUM!!
					std::cin >> search_type;
					if (search_type >= 1 && search_type < 5) {
						locVal = true;
						srchType = static_cast<searchTools::_searchType>(search_type); // static casting the int fed in to match the enums of search types.
					}
					else { std::cout << "Invalid container selection, try again" << std::endl; }
				}
				std::string tempFileName = dlay->_directory + "\\" + search->_fileName;
				std::cout << "Checking file name: " << tempFileName << std::endl;
				if (tempFileName.length() == 0) {
					throw std::exception("FileName is empty!");
				}
				search->functionRouting(*dlay, srchType, conType, tempFileName);
				std::string tempChoice;
				std::cout << "If you wish to exit the searching operation:" << std::endl << "Enter 1" << std::endl << "Or enter search to start again" << std::endl;
				std::cin >> tempChoice;
				if (tempChoice == "1") {
					_alive = false;
				}
			}
		}
		catch (std::string err) {
			errorToScreen(err, "Search Menu");
		}
		catch (std::exception& excep)
		{
			errorToScreen(excep, "Search Menu");
		}
	}
	return ret_err;
}
ret Menu::timeMenu()
{
	error_type ret_err = func_passed;

	return ret_err;
}
ret Menu::dataMenu()
{
	error_type ret_err = func_passed;

	return ret_err;
}