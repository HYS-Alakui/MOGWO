#ifndef _HEAD_FILE_H_
#define _HEAD_FILE_H_

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>
#include <ctime>
#include <vector>
#include <unordered_map>

using namespace std;


#define EPSILON  0.000000000000000000000001
#define INFTY    INT_MAX
#define CHAR_LEN 300

#define INF_INT_MAX numeric_limits <int>::max();
#define INF_INT_MIN -1 * numeric_limits <int>::max();
#define INF_DOUBLE_MAX numeric_limits <double>::max();
#define INF_DOUBLE_MIN -1.0 * numeric_limits <double>::max();


#define IA       16807
#define IM       2147483647
#define AM       (1.0/IM)
#define IQ       127773
#define IR       2836
#define MASK     123459876

#define PI       3.1415926


#endif



#ifdef WIN32

#pragma warning (disable: 4786)

#endif
