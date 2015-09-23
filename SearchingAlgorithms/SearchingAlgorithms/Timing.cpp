#include "stdafx.h"

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
void Time::capture(dataLayer& dlayer, std::size_t element, std::size_t postion, std::chrono::duration<long long, std::nano> duration)
{

}