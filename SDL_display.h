#ifndef __SDL_DISPLAY_H_
#define __SDL_DISPLAY_H_

#include "utils.h"

u8_int initDisplay(IRISCONFIG* cfg);
u8_int runDisplay (IRISCONFIG* cfg, u8_int* frame);
u8_int freeDisplay(IRISCONFIG* cfg);
#endif //__SDL_DISPLAY_H_
