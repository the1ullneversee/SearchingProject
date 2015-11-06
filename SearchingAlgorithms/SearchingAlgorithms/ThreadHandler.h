#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H
#include "stdafx.h"

class thread_handler
{
	std::thread &t;
public:
	explicit thread_handler(std::thread& t_) :
		t(t_)
	{}
	~thread_handler()
	{
		if (t.joinable())
		{
			std::cout << "Joining thread" << std::endl;
			t.join();
		}
	}
	thread_handler(thread_handler const&) = delete;
	thread_handler& operator=(thread_handler const&) = delete;
private:
	std::thread _t1;
};


#endif THREAD_HANDLER_H
