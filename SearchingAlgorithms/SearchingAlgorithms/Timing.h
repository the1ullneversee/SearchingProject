#ifndef TIMING_H
#define TIMING_H
#include "stdafx.h"

#define chrono_type std::chrono::time_point<std::chrono::high_resolution_clock>
#define chrono_type_duration std::chrono::duration<long long, std::nano>

class Time {
public:
	Time();
	~Time();
	//void clock_start();
	//void clock_end();
	//void duration();
	void clock_start();
	void clock_end();
	void duration();
	chrono_type_duration _duration;
	void capture(dataLayer& dlayer, std::size_t element, std::size_t position, chrono_type_duration duration, std::string typeOfSearch, bool vec_list);
private:
	chrono_type _phase_start;
	chrono_type _phase_end;
	
};
#endif TIMING_H