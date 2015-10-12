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
	return dlayerMain.get();
}
void Menu::mainMenu()
{
	std::unique_ptr<dataLayer> dataMainLayer(new dataLayer);
	std::unique_ptr<Menu> menu(new Menu);
	/*std::unique_ptr<ContainerPro> conPro(new ContainerPro);
	conPro->ID = "1";
	conPro->metaDataName = "This is the test";
	dataMainLayer->_filename = "Tom";
	menu->dlayerMain = std::move(dataMainLayer);
	std::cout << menu->dlayerMain->_filename << std::endl;
	menu->containerMaster.push_back(std::move(conPro));
	std::unique_ptr<ContainerPro> conProTest(new ContainerPro);
	conProTest = std::move(menu->containerMaster[0]);
	std::cout << conProTest->ID << conProTest->metaDataName << std::endl;
*/

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
	changeColourScreen("red", "black");
	std::cout << std::endl << "The function " << functionName << "has failed with the following exception: " << std::endl << e.what() << std::endl;
}
void Menu::errorToScreen(std::invalid_argument& invArg, std::string functionName) {
	std::cout << std::endl << "The function " << functionName << "has failed with the following invalid argument: " << std::endl << invArg.what() << std::endl;
}
void Menu::errorToScreen(std::string strErr, std::string functionName) {
	std::cout << std::endl << "The function " << functionName << "has failed with the following error message: " << std::endl << strErr << std::endl;
}
ret Menu::searchMenu(Menu& menu)
{
	bool _alive = true;
	bool locVal = false;
	error_type ret_err = func_passed;
	std::unique_ptr<searchTools> search(new searchTools);
	std::unique_ptr<dataLayer> dlay(new dataLayer);
	std::unique_ptr<Time> time(new Time);
	
	searchTools::_searchType srch = searchTools::linear;
	searchTools::_searchType srchType = searchTools::linear;
	dataLayer::_container_type conType = dataLayer::vectorInt;
	std::string tempChoice;
	std::string tempFileName;
	LPCTSTR errorText = NULL;
	bool functionAlive = new (bool);
	//dlay.reset(menu.dlayerMain);
	//std::unique_ptr<dataLayer> dlay(new dataLayer);
	while (_alive) {
		try {
			//std::wstring stemp = s2ws("C:\\Users\\thomaskn\\Downloads\\*");
			ret_err = dlay->getFile(functionAlive);
			if (!functionAlive) { _alive = false; break; }
			if (ret_err != func_passed) { throw std::exception("function failed", ret_err); }
			conType = dlay->getUserConType();
			if (ret_err != func_passed) { throw std::exception("function failed", ret_err); }

			srchType = search->searchSelect();

			tempFileName = dlay->_directory + "\\" + dlay->_filename;
			std::cout << "Checking file name: " << tempFileName << std::endl;
			if (tempFileName.length() == 0) {
				throw std::exception("FileName is empty!");
			}
			std::thread t1(&dataLayer::containerFiller,dlay.get(), tempFileName, conType);
			
			//ret_err = dlay->containerFiller(tempFileName, conType);
			std::cout << "Waiting for File to finish reading" << std::endl;
			
			if (ret_err != func_passed)
			{
				throw std::exception("container filler failed!");
			}
			t1.join();
			//throws in the containers. what search they want, container type, and the filename? why the filename.
			search->searchFunctionRouting(*dlay, srchType, conType, tempFileName);
			
			std::cout << "If you wish to exit the searching operation:" << std::endl << "Enter 'exit'" << std::endl << "Or enter 'search' to start file finding again." << std::endl
				<< "If you wish to save this container for later use enter 'save'" << std::endl;
			std::cin >> tempChoice;
			if (tempChoice == "exit" || tempChoice == "Exit") {
				_alive = false;
			}
			else if (tempChoice == "save" || tempChoice == "Save")
			{
				std::unique_ptr<ContainerPro> conPro(new ContainerPro);
				size_t idToUse;
				idToUse = conPro->IDWorked(menu.containerMaster.size(), menu.IDsInUse);
				conPro->metaDataName = conPro->fillMetaData(srchType, conType, time->currTime(), idToUse);
				conPro->saveContainer(*dlay, conType);
				menu.containerMaster.push_back(std::move(conPro));
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
	
	
	
	//menu.containerMaster
	std::cout << "MenuDLayer Address: " << &menu.dlayerMain << "Local dlay pointer: " << &dlay << std::endl;
	menu.functionReRouting = true; 
	menu.dlayerMain = std::move(dlay);
	
	//menu.dlayerMain = dlay._Myptr(); 
	std::cout << "MenuDLayer Address: " << &menu.dlayerMain << "Local dlay pointer: " << &dlay << std::endl;
	
	//dlay.reset(menu.getDataLayer());
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
	std::size_t userChoice;
	dataMenuItems dMenuItems;
	/*if (menuReRouting)
	{
		dataLayer &dataLayer = dataLayerMaster;
		}
	else { 
		dataLayer dataLayer;
	}*/
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
				<< "5. Select 5 to exit. " << std::endl;
			std::cin >> userChoice;
			if (userChoice == 5) { alive = false; break; }
			//dataMenuItems
			while (!valid) {
				for (int i = 0; i < ENDOFMenuEnum; i++)
				{
					if (userChoice == i)
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
			dMenuItems = static_cast<dataMenuItems>(userChoice);

			switch (dMenuItems)
			{
			case 1:

				break;
			case 2:
				//Let them select the container they want to print out. 
				// have to of filled a container first. or Loaded one. 
				dataLayer::_container_type conType;

				while (!locVal)
				{
					std::cout << " Please Select your container type: " << std::endl << "1: integer vector" << std::endl << "2: string vector" << std::endl << "3: integer list" << std::endl << "4: string list" << std::endl;
					std::cin >> choice;
					conType = static_cast<dataLayer::_container_type>(choice);
					for (int i = 0; i < dataLayer::enumTypeEnd; i++) {
						if (conType == i) { locVal = true; break; }
					}
					if (!locVal) {
						std::cout << "Invalid container selection, try again" << std::endl;
					}
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
			default:
				throw std::exception("Invalid menu item choice!");
				break;
			}
		}
	}
	catch (std::exception& e)
	{
		errorToScreen(e, "Data Menu");
	}
	return ret_err;
}
