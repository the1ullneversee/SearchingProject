// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _AFXDLL
#define NOMINMAX
const enum error_type : int { func_passed = 0, function_fail = 1, null_value = 2, bad_input = 3, killApplication = 4, ENDOFENUM = 5 };
enum _searchType : int { linear = 1, findElement = 2, binary = 3, bubbleSort = 4, EndOfSearchEnum = 5 };

enum _container_type : int { default = 0, vectorInt = 1, vectorString = 2, listInt = 3, listString = 4, enumTypeEnd = 5 };
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
#include "DataWrapper.h"
#include "MainMenu.h"
#include "classHolder.h"
#include "SearchTools.h"
#include "ContainerPro.h"

#include "ThreadHandler.h"
#include "Timing.h"




// TODO: reference additional headers your program requires here
