#ifndef TIMING_H
#define TIMING_H
#include "stdafx.h"

//#define chrono_type std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration>
//#define chrono_type_duration std::chrono::duration<long long, std::micro>

class Time {
public:
	Time();
	~Time();
	void clock_start();
	void clock_end();
	void duration();
	
	/*chrono_type clock_start();
	chrono_type clock_end();
	void duration(chrono_type &phase_start, chrono_type &phase_end);*/
private:
	/*chrono_type _phase_start;
	chrono_type _phase_end;
	chrono_type_duration _duration; */
};
#endif TIMING_H