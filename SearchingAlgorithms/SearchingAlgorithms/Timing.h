#ifndef TIMING_H
#define TIMING_H
#include "stdafx.h"

#define chrono_type std::chrono::time_point<std::chrono::high_resolution_clock>
#define system_chrono_type std::chrono::time_point<std::chrono::system_clock>
#define chrono_type_duration std::chrono::duration<long long, std::nano>

class Time {
public:
	Time();
	~Time();
	void clock_start();
	void clock_end();
	void duration();
	void readArchive();
	void editArchive();
	void displayArchive();
	std::string currTime();
	chrono_type_duration _duration;
	void capture(std::string filename, std::string element, std::size_t position, chrono_type_duration duration, std::string typeOfSearch, bool vec_list, bool found);
private:
	std::string _filename;
	std::string _typeOfSearch;
	std::string _typeOfContainer;
	std::string _elementFind;
	std::string _found;
	std::string _posInContainer;
	std::string _timeTaken;
	std::list<std::string> archiveDetails;
	chrono_type _phase_start;
	chrono_type _phase_end;
	system_chrono_type _time;
	std::time_t end_time;
};
#endif TIMING_H