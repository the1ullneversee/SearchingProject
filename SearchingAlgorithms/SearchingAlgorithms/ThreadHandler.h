#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H
#include "stdafx.h"

class threadHandler
{
public:
	threadHandler();
	~threadHandler();
	//std::thread createThread(void *func);
private:
	std::thread _t1;
};


#endif THREAD_HANDLER_H
