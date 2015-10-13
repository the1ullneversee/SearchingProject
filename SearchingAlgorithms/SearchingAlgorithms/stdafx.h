// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _AFXDLL
#define NOMINMAX
const enum error_type : int { func_passed = 0, function_fail = 1, null_value = 2, bad_input = 3, killApplication = 4, ENDOFENUM = 5 };
#define _CRT_SECURE_NO_WARNINGS 1
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include "time.h"
#include <ctime>
#include <string>
#include <direct.h>
#include <iomanip>
#include <vector>
#include <list>
#include <thread>
#include <fstream>
#include <chrono>
#include <memory>
#include <cstring>
#include "afx.h"
#include <comdef.h>
#include <limits>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "DataLayer.h"
#include "MainMenu.h"
#include "classHolder.h"
#include "SearchTools.h"
#include "ContainerPro.h"

#include "ThreadHandler.h"
#include "Timing.h"




// TODO: reference additional headers your program requires here
