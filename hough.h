#ifndef __HOUGH_H_
#define __HOUGH_H_

#include "utils.h"

u8_int initHough(IRISCONFIG* h);
u8_int runHough (IRISCONFIG* h);
u8_int freeHough(IRISCONFIG* h);
#endif //__HOUGH_H_
