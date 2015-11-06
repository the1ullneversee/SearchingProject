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
	searchTools srch;
	error_type err = func_passed;
	bool Alive = true;
	int choice = 0;
	bool valid = false;
	
	/*for (int i = 0; i < 10; i++)
	{
		std::cin >> choice;
		menu->IDsInUse.push_back(choice);
		std::unique_ptr<ContainerPro> conPro(new ContainerPro);
		conPro->fillMetaData(_searchType::bubbleSort, _container_type::listInt, "5PM", choice);
		menu->containerMaster.push_back(std::move(conPro));
	}
	std::cout << "Change \n";
	for (int j = 0; j < 4; j++)
	{
		std::cin >> choice;
		menu->tempIDS.push_back(choice);
	}*/
	changeColourScreen("Blue", "Black");
	std::cout << "Welcome to the Searching Utility Application." << std::endl << "Use this application to perform different se1arches on different C++ container types!" << std::endl;
	while (Alive) {
		std::cout << "Here is the Menu enter the corresponding function number to proceed!" << std::endl;
		changeColourScreen("Red", "Black");
		while (!valid) {
			if (menu->containerMaster.size() != 0)
			{
				for (std::size_t i = 0; i <= menu->containerMaster.size() - 1; i++) {
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
			err = dataMenu(*menu);
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
bool Menu::SaveContainerPerm(Menu & menu,DataWrapper& dwrap, bool temp)
{
	bool ret = true;
	try {
		std::unique_ptr<Time> time(new Time);
		std::unique_ptr<ContainerPro> conPro(new ContainerPro);
		size_t idToUse;
		idToUse = conPro->IDWorked(menu.containerMaster.size(), menu.IDsInUse);
		conPro->metaDataName = conPro->fillMetaData(dwrap.getSrchType(), dwrap.getConType(), time->currTime(), idToUse, dwrap.getFilename());
		if (temp)
			menu.tempIDS.push_back(idToUse);

		conPro->saveContainer(dwrap);
		menu.containerMaster.push_back(std::move(conPro));
	}
	catch (std::exception& e)
	{
		ret = false;
		Menu::errorToScreen(e, "Save Container Perm");
	}
	catch (...)
	{
		ret = false;
		Menu::errorToScreen("...", "Save Container Perm");
	}
	
	return true;
}
bool Menu::ClearTempContainers(Menu & menu)
{
	bool ret = true;
	int x = 0;
	std::size_t size = menu.IDsInUse.size()-1;
	try {
		std::cout << menu.IDsInUse << std::endl;
		if (menu.IDsInUse.size() != 0)
		{
			for (auto z = 0; z < size; z++) {

				for (auto i = 0; i < menu.IDsInUse.size() - 1; i++)
				{
					for (auto j = 0; j < menu.tempIDS.size(); j++)
					{
						if (menu.IDsInUse[i] == menu.tempIDS[j])
						{
							menu.IDsInUse.erase(menu.IDsInUse.begin() + (i));
							menu.tempIDS.erase(menu.tempIDS.begin() + j);
							menu.containerMaster.erase(menu.containerMaster.begin() + (i));
							menu.containerMaster[i]->ContainerID = i;
							searchTools::bubbleSort(menu.IDsInUse);
						}
					}
				}
			}
		}
		std::cout << menu.IDsInUse << std::endl;
	}
	catch (std::exception& e)
	{
		Menu::errorToScreen(e, "Clear Temp containers");
	}
	return false;
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
	int i = 0;
	for (auto iterator = threadVec.begin(); iterator != threadVec.end(); iterator++) {
		std::cout << "Checking whether threads are finished \n";
		if (threadVec[i].joinable()) {
			threadVec[i].join();
			//threadVec.erase(iterator);
			std::cout << "Joined thread: " << threadVec[i].get_id() << std::endl;
		}
		else {
			std::cout << "Still waiting for thread: " << threadVec[i].get_id() << std::endl;
		}
		i++;
	}
	return err;
}
ret Menu::invokeDataWrapper(std::vector<std::thread>& threadVec, DataWrapper*& dwrap)
{
	ret rt = function_fail;
	dataLayer dlayNorm;
	dataLayer* dlayPtr = new(dataLayer);
	error_type ret_err = func_passed;
	_searchType srchType = linear;
	_container_type conType = vectorInt;
	bool functionAlive = true;
	std::unique_ptr<searchTools> search(new searchTools);
	//dataLayer dlay;
	std::unique_ptr<Time> time(new Time);
	std::string tempFileName;
	try {
		std::cout << "Setting up container for searching \n";
		rt = dlayPtr->getFile(functionAlive);
		if (!functionAlive) {}//dwrap = nullptr; }
		if (rt != func_passed) { throw std::exception("function failed", rt); }
		conType = dlayPtr->getUserConType();
		if (rt != func_passed) { throw std::exception("function failed", rt); }

		srchType = search->searchSelect();
		dwrap->setUserChoices(srchType, conType);

		tempFileName = dlayPtr->_directory + "\\" + dlayPtr->_filename;
		std::cout << "Checking file name: " << tempFileName << std::endl;
		if (tempFileName.length() == 0) {
			throw std::exception("FileName is empty!");
		}

		//We care gonna have to let them input multiple containers.
		dwrap->setDirectory(dlayPtr->_directory);
		dwrap->setFilename(dlayPtr->_filename);
		threadVec.push_back(std::thread(&dataLayer::containerFiller, &dlayNorm, std::ref(dwrap)));
	}
	catch (std::exception& e)
	{
		Menu::errorToScreen(e,"invoke data wrapper");
	}
	return rt;
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
	bool functionAlive = true;
	std::vector<std::thread>* threadVec(new std::vector<std::thread>);
	
	while (_alive) {
		try {
			for (;;) {
				DataWrapper* dwrapMain = new (DataWrapper);
				ret_err = invokeDataWrapper(*threadVec, dwrapMain);
				if (ret_err != func_passed)
					throw std::exception("Invoke Data Wrapper Function Failed");
				vecDWrap.push_back(dwrapMain);
				std::cout << "Would you like to create another container? y/n";
				std::cin >> tempChoice;
				if (tempChoice == "n")
					break;
			}
			ret_err = multiContainersJoin(*threadVec);
			if (ret_err != func_passed)
				throw std::exception("Multi Container Join failed");
			Menu::clearScreen();
			std::cout << "We have found " << vecDWrap.size() << " Containers, using first one" << std::endl;
			for (std::size_t i = 0; i < vecDWrap.size(); i++) {
				std::cout << "This is Container " << i+1 << " it is a " << mDwrap.returnConTypeString(vecDWrap[i]->getConType()) << std::endl;
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
					SaveContainerPerm(menu, *vecDWrap[i], false);
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
ret Menu::dataMenu(Menu &menu) //Change the functionality of this to use the new values.
{
	error_type ret_err = func_passed;
	std::size_t userChoice;
	dataMenuItems dMenuItems;
	std::unique_ptr<dataLayer> unqDlay (new dataLayer);
	std::unique_ptr<searchTools> search(new searchTools);
	std::shared_ptr<DataWrapper> shDataWrapper(new DataWrapper);
	std::vector<DataWrapper> dWrapHolder;
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
				<< "6. Select 6 to exit. " << std::endl;
			std::cin >> userChoice;
			if (userChoice == 6) {

				alive = false;
				break;
			}
			//dataMenuItems
			for (int i = 0; i < ENDOFDataMenuEnum; i++)
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
			dMenuItems = static_cast<dataMenuItems>(userChoice);
			std::size_t amount = 0;
			std::string fileName = "";
			std::string choice;
			switch (dMenuItems)
			{
			case 1:

				break;
			case 2:
				
				break;
			case 3:
				break;
			case 4:
				//Load Container from File
				bool alive;
				alive = true;
				std::cout << "Preparing operation \n";
				shDataWrapper->setConType(unqDlay->getUserConType());
				unqDlay->getFile(alive);
				shDataWrapper->dataCopier(unqDlay->_directory, unqDlay->_filename);
				unqDlay->containerFillFromFile(*shDataWrapper);
				std::cout << "Do you wish to save this as a temp container? y/n" << std::endl;
				std::cin >> choice;
				if (choice == "y")
					SaveContainerPerm(menu, *shDataWrapper, true);
				else
					SaveContainerPerm(menu, *shDataWrapper, false);
				std::cout << "Operation finished \n";
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
		menu.ClearTempContainers(menu);
	}
	catch (std::exception& e)
	{
		errorToScreen(e, "Data Menu");
	}
	
	return ret_err;
}
