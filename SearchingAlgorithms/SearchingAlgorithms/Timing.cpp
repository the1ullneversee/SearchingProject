#include "stdafx.h"

Time::Time() {
	_phase_start = std::chrono::steady_clock::now();
	_phase_end = std::chrono::steady_clock::now();
}
Time::~Time() {

}
chrono_type Time::clock_start(){

	return std::chrono::steady_clock::now();
}
chrono_type Time::clock_end(){

	return std::chrono::steady_clock::now();
}
void Time::duration(chrono_type &phase_start, chrono_type &phase_end){

}