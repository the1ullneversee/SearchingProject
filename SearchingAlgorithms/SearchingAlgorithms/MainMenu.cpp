#include "stdafx.h"
#include "MainMenu.h"
Menu::Menu()
{
	containerMaster;
}
Menu::~Menu()
{
	std::cout << "Menu destructing" << std::endl;
}
dataLayer * Menu::getDataLayer()
{
	return dlayerMain;
}
void Menu::mainMenu()
{
	std::unique_ptr<dataLayer> dataMainLayer(new dataLayer);
	std::unique_ptr<Menu> menu(new Menu);
	error_type err = func_passed;
	bool Alive = true;
	int choice = 0;
	bool valid = false;
	changeColourScreen("Blue", "Black");
	std::cout << "Welcome to the Searching Utility Application." << std::endl << "Use this application to perform different se1arches on different C++ container types!" << std::endl;
	while (Alive) {
		std::cout << "Here is the Menu enter the corresponding function number to proceed!" << std::endl;
		changeColourScreen("Red", "Black");
		while (!valid) {
			if (menu->containerMaster.size() != 0)
			{
				for (int i = 0; i <= menu->containerMaster.size() - 1; i++) {
					std::unique_ptr<ContainerPro> conProMain(new ContainerPro);
					std::swap(conProMain, menu->containerMaster[i]);
					//conProMain = std::move(menu->containerMaster[i]);
					std::cout << conProMain->ContainerID << conProMain->metaDataName << std::endl;
					std::swap(menu->containerMaster[i], conProMain);
					//std::cout << conProMain->intVect << std::endl;
					//std::cout << conProMain->stringVect << std::endl;
				}

			}
			std::cout << "1. Searching Functions" << std::endl
				<< "2. Data Functions" << std::endl
				<< "3. Time Functions" << std::endl;
			std::cin >> choice;
			for (int i = 0; i < ENDOFMenuEnum; i++)
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
			err = searchMenu(*menu);
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
	Menu::changeColourScreen("red", "black");
	std::cout << std::endl << "The function " << functionName << "has failed with the following exception: " << std::endl << e.what() << std::endl;
}
void Menu::errorToScreen(std::invalid_argument& invArg, std::string functionName) {
	std::cout << std::endl << "The function " << functionName << "has failed with the following invalid argument: " << std::endl << invArg.what() << std::endl;
}
void Menu::errorToScreen(std::string strErr, std::string functionName) {
	std::cout << std::endl << "The function " << functionName << "has failed with the following error message: " << std::endl << strErr << std::endl;
}
void fill(std::string tom, std::shared_ptr<dataLayer> dl) {
	
}
ret Menu::multiContainersJoin(std::vector<std::thread>& threadVec, std::vector<DataWrapper>& vecDWrapper)
{
	error_type err = func_passed;
	for (auto thread = 0; thread != threadVec.size(); thread++) {
		std::cout << "Waiting for threads to finish\n";
		threadVec[thread].join();
	}
	return err;
}
ret Menu::multiContainersJoin(std::vector<std::thread>& threadVec)
{
	error_type err = func_passed;
	for (auto thread = 0; thread != threadVec.size(); thread++) {
		std::cout << "Waiting for threads to finish\n";
		threadVec[thread].join();
	}
	return err;
}
void Menu::invokeDataWrapper(std::vector<std::thread>& threadVec, DataWrapper*& dwrap)
{
	dataLayer dlayNorm;
	dataLayer* dlayPtr = new(dataLayer);
	error_type ret_err = func_passed;
	_searchType srchType = linear;
	_container_type conType = vectorInt;
	bool functionAlive = new (bool);
	std::unique_ptr<searchTools> search(new searchTools);
	//dataLayer dlay;
	std::unique_ptr<Time> time(new Time);
	std::string tempFileName;
	try {
		std::cout << "Setting up container for searching \n";
		ret_err = dlayPtr->getFile(functionAlive);
		if (!functionAlive) {}//dwrap = nullptr; }
		if (ret_err != func_passed) { throw std::exception("function failed", ret_err); }
		conType = dlayPtr->getUserConType();
		if (ret_err != func_passed) { throw std::exception("function failed", ret_err); }

		srchType = search->searchSelect();
		dwrap->setUserChoices(srchType, conType);

		tempFileName = dlayPtr->_directory + "\\" + dlayPtr->_filename;
		std::cout << "Checking file name: " << tempFileName << std::endl;
		if (tempFileName.length() == 0) {
			throw std::exception("FileName is empty!");
		}

		//We care gonna have to let them input multiple containers.
		dwrap->_directory = dlayPtr->_directory;
		dwrap->_filename = dlayPtr->_filename;
		threadVec.push_back(std::thread(&dataLayer::containerFiller, &dlayNorm, std::ref(dwrap)));
	}
	catch (std::exception& e)
	{
		Menu::errorToScreen(e,"invoke data wrapper");
	}
}
ret Menu::searchMenu(Menu& menu)
{
	bool _alive = true;
	bool locVal = false;
	std::unique_ptr<Time> time(new Time);
	error_type ret_err = func_passed;
	std::vector<DataWrapper*> vecDWrap;
	searchTools search;
	std::string tempChoice;
	DataWrapper mDwrap;
	LPCTSTR errorText = NULL;
	bool functionAlive = new (bool);
	std::vector<std::thread>* threadVec(new std::vector<std::thread>);
	while (_alive) {
		try {
			for (;;) {
				DataWrapper* dwrapMain = new (DataWrapper);
				invokeDataWrapper(*threadVec, dwrapMain);
				vecDWrap.push_back(dwrapMain);
				std::cout << "Would you like to create another container? y/n";
				std::cin >> tempChoice;
				if (tempChoice == "n")
					break;
			}

			multiContainersJoin(*threadVec);
			if (ret_err != func_passed)
			{
				throw std::exception("container filler failed!");
			}
			Menu::clearScreen();
			std::cout << "We have found " << vecDWrap.size() << " Containers, using first one" << std::endl;
			for (int i = 0; i < vecDWrap.size(); i++) {
				std::cout << "This is Container " << i+1 << " it is a " << mDwrap.returnConType(vecDWrap[i]->conType) << std::endl;
				search.searchFunctionRouting(*vecDWrap[i]);
				std::cout << "Finished searching" << std::endl
					<< "Enter 'exit' to stop searching operation" << std::endl
					<< "Enter 'save' to save this containter for further use" << std::endl;
				std::cin >> tempChoice;
				if (tempChoice == "exit" || tempChoice == "Exit") {
					_alive = false;
				}
				else if (tempChoice == "save" || tempChoice == "Save")
				{
					std::unique_ptr<ContainerPro> conPro(new ContainerPro);
					size_t idToUse;
					idToUse = conPro->IDWorked(menu.containerMaster.size(), menu.IDsInUse);
					conPro->metaDataName = conPro->fillMetaData(vecDWrap[i]->srchType, vecDWrap[i]->conType, time->currTime(), idToUse);

					conPro->saveContainer(*vecDWrap[i], vecDWrap[i]->conType);
					menu.containerMaster.push_back(std::move(conPro));
				}
			}
			std::cout << "We have finished filling and searching containers, your containers have been saved if specified" << std::endl
				<< "Do you wish to go again? y/n" << std::endl;
			std::cin >> tempChoice;
			if (tempChoice == "n" || tempChoice == "N")
			{
				_alive = false;
			}
		}
		catch (std::string err) {
			errorToScreen(err, "Search Menu");
		}
		catch (std::exception& excep)
		{
			errorToScreen(excep, "Search Menu");
		}
		catch (...)
		{
			std::cout << "Caught an exception in catch(...)." << std::endl;
		}
	}
	return ret_err;
}
ret Menu::timeMenu()
{
	error_type ret_err = func_passed;

	return ret_err;
}
ret Menu::dataMenu() //Change the functionality of this to use the new values.
{
	error_type ret_err = func_passed;
	std::size_t userChoice;
	dataMenuItems dMenuItems;
	std::unique_ptr<dataLayer> unqDlay (new dataLayer);
	bool valid = false;
	int choice = 0;
	bool locVal = false;
	bool alive = true;
	try {
		while (alive)
		{
			clearScreen();
			std::cout << "Welcome to the Data menu!" << std::endl
				<< "Here are the menu options:" << std::endl
				<< "1. Create Container" << std::endl
				<< "2. Print Container" << std::endl
				<< "3. Save a Container to File" << std::endl
				<< "4. Load a Container from a File" << std::endl
				<< "5. Save linear data to File" << std::endl
				<< "6. Select 5 to exit. " << std::endl;
			std::cin >> userChoice;
			if (userChoice == 6) { alive = false; break; }
			//dataMenuItems
			for (int i = 0; i < ENDOFDataMenuEnum; i++)
			{
				if (userChoice == i)
				{
					valid = true;
					alive = false;
					break;
				}
			}
			if (!valid)
			{
				errorToScreen("Bad Input, Please choose again. Loading Menu...", "Menu");
			}
		}
		dMenuItems = static_cast<dataMenuItems>(userChoice);
		std::size_t amount = 0;
		std::string fileName = "";
		switch (dMenuItems)
		{
		case 1:

			break;
		case 2:
			//Let them select the container they want to print out. 
			// have to of filled a container first. or Loaded one. 
			_container_type conType;

			while (!locVal)
			{
				conType = unqDlay->getUserConType();
			}
			if (menuReRouting)
			{
				//dataLayer->printContainer(dataLayerMaster, conType);
			}
			else {
				//Must have been prefilled by the user. 
				//dataLayer->printContainer(*dataLayer, conType);
			}
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			std::cout << "Data file creation started" << std::endl;
			std::cout << "How many numbers do you want to write to file?";
			std::cin >> amount;
			std::cout << "Name the file: " << std::endl;
			std::cin >> fileName;
			unqDlay->_directory += "\\";
			unqDlay->linearNumbers(amount, unqDlay->_directory += fileName);
			break;
		default:
			throw std::exception("Invalid menu item choice!");
			break;
		}
	}
	catch (std::exception& e)
	{
		errorToScreen(e, "Data Menu");
	}
	return ret_err;
}
