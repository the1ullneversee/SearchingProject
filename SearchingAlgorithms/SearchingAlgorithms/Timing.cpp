#include "stdafx.h"
//std::unique_ptr<Menu> menu(new Menu);
Time::Time() {
	
	_phase_start = std::chrono::high_resolution_clock::now();
	_phase_end = std::chrono::high_resolution_clock::now();
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
	//std::cout << "The execution duration was: " << 00 << ":" << 01 << ":" << 12 << std::endl;
	std::cout << "The execution duration was: " << float(Time::_duration.count() / 1E6) << "(seconds)" << std::endl;
}
void Time::capture(dataLayer& dlayer, std::size_t element, std::size_t position, chrono_type_duration duration, std::string typeOfSearch, bool vec_list)
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
				for (int i = 0; i < stringInVect.size(); i++)
					ofStream << stringInVect[i] << std::endl;
			}
			if (vec_list) { conType = "Vector"; }
			ofStream << "File Searched: " << dlayer._filename << std::endl << "Type of Search: " << typeOfSearch << std::endl << "Type of Container: " << conType
			<< std::endl << "Element Trying to find: " << element << std::endl << "Position in container: " << position
				<< std::endl << "Time Taken: " << float(duration.count() / 1E6) << "(seconds)" << std::endl;
		}
		else {
			throw std::exception("Could not create file!");
		}
	}
	catch (std::exception& e)
	{
	}
}