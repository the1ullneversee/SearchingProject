#include "stdafx.h"
std::unique_ptr<Menu> tMenu(new Menu);
Time::Time() {
	_phase_start = std::chrono::high_resolution_clock::now();
	_phase_end = std::chrono::high_resolution_clock::now();
	this->_filename = "";
	this->_typeOfSearch = "";
	this->_typeOfContainer = "";
	this->_elementFind = "";
	this->_found = "";
	this->_posInContainer = "";
	this->_timeTaken = "";
}
Time::~Time() {

}
void Time::clock_start(){
	std::cout << "Starting timer" << std::endl;
	Time::_phase_start = std::chrono::high_resolution_clock::now();
}
void Time::clock_end(){
	std::cout << "Timer ended" << std::endl;
	Time::_phase_end = std::chrono::high_resolution_clock::now();
}
void Time::duration() {
	Time::_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(Time::_phase_end - Time::_phase_start);
	std::cout << "The execution duration was: " << float(Time::_duration.count() / 1E6) << "(ns)" << "In seconds: " << float((Time::_duration.count() / 1E6)/1000) << std::endl;
}
std::string Time::currTime() {
	Time::_time = std::chrono::system_clock::now();
	Time::end_time = std::chrono::system_clock::to_time_t(_time);
	return ctime(&end_time);
}
void Time::capture(std::string filename, std::string element, std::size_t position, chrono_type_duration duration, std::string typeOfSearch, bool vec_list, bool found)
{
	try {
		bool fileFound = false;
		std::ifstream inStream;
		std::ofstream ofStream;
		std::string _stringTemp;
		std::vector<std::string> stringInVect;
		//Need to check if file is empty or has contents
		//if there are contents then we need to read all of the values into a vector, and write that out before writing new values. 
		//Shall we do a directory look up.
		std::string conType = "List";
		inStream.open("TimeArchive.txt");
		if (inStream.is_open())
		{
			fileFound = true;

			while (!inStream.eof()) {
				std::getline(inStream, _stringTemp);
				//std::cout << _stringTemp;
				stringInVect.push_back(_stringTemp);
			}
			inStream.close();
			// Need to reading in
		}
		ofStream.open("TimeArchive.txt");
		if (ofStream)
		{
			if (fileFound)
			{
				for (unsigned int i = 0; i < stringInVect.size(); i++)
					ofStream << stringInVect[i] << std::endl;
			}
			if (vec_list) { conType = "Vector"; }
			ofStream << "File Searched: " << filename << std::endl << "Type of Search: " << typeOfSearch << std::endl << "Type of Container: " << conType
				<< std::endl << "Element Trying to find: " << element << std::endl << "Found = ";
			if (found) {
				ofStream << "true" << std::endl << "Position in container: " << position
					<< std::endl << "Time Taken: " << float(duration.count() / 1E6) << "(seconds)" << std::endl;
			}
			else
			{
				ofStream << "False" << std::endl;
			}
		}
		else {
			throw std::exception("Could not create file!");
		}
		ofStream.close();
	}
	catch (std::exception& e)
	{
		tMenu->errorToScreen(e, "Time Capture");
	}

}
void Time::readArchive()
{
	try
	{
		int i = 0;
		bool more = true;
		std::string temp = "";
		std::ifstream inFile("TimeArchive.txt");
		if (!inFile)
			throw std::exception("Could not open file");
		while (inFile >> temp)
		{
			if (more)
			{
				switch (i)
				{
				case 0:
					this->_filename = temp;
					break;
				case 1:
					this->_typeOfSearch = temp;
					break;
				case 2:
					this->_typeOfContainer = temp;
					break;
				case 3:
					this->_elementFind = temp;
					break;
				case 4:
					this->_found = temp;
					if (temp.find("0"))
					{
						this->archiveDetails.push_back(this->_filename);
						this->archiveDetails.push_back(this->_typeOfSearch);
						this->archiveDetails.push_back(this->_typeOfContainer);
						this->archiveDetails.push_back(this->_elementFind);
						this->archiveDetails.push_back(this->_found);
						more = false;
					}
					else {
						more = true;
					}
					break;
				case 5: 
					this->_posInContainer = temp;
					break;
				case 6:
					this->_timeTaken = temp;
					break;
				}
			}
			if (i == 6) {
				i = 0;
				more = true;
				this->archiveDetails.push_back(this->_filename);
				this->archiveDetails.push_back(this->_typeOfSearch);
				this->archiveDetails.push_back(this->_typeOfContainer);
				this->archiveDetails.push_back(this->_elementFind);
				this->archiveDetails.push_back(this->_found);
				this->archiveDetails.push_back(this->_posInContainer);
				this->archiveDetails.push_back(this->_timeTaken);
			}

			i++;
		}
	}
	catch (std::exception& e)
	{
		Menu::errorToScreen(e, "Read Archive");
	}
}

void Time::editArchive()
{

}

void Time::displayArchive()
{
	try {
		readArchive();
		for (auto it = this->archiveDetails.begin(); it != this->archiveDetails.end(); it++)
			std::cout << *it << std::endl;
	}
	catch (std::exception& e)
	{
		Menu::errorToScreen(e, "Display Archive");
	}
}
