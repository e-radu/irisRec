#ifndef __UTILS_H__
#define __UTILS_H__

typedef unsigned char  u8_int ;
typedef unsigned short u16_int;
typedef unsigned int   u32_int;
typedef signed char    s8_int ;
typedef signed short   s16_int;
typedef signed int     s32_int;
typedef        float   s32_float;

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdint.h>


#define DEBUG 0
#define OUT_PATT 0
#define WEBCAM 1
#define DISPLAY 1
#define PI 3.14159265
#define RADIINO 58
#define SMALL_RAD 10
#define WIDTH   160
#define HEIGHT  120
#define P_WIDTH 360
#define R_WIDTH 256  //max 256
#define R_HEIGHT 64  //max 256
#define DP 32        //drawn points
#define HOR_SHIFT 5
#define VER_SHIFT 5
#define HD_THR 820   //0.4 hamming distance
#define _CRT_SECURE_NO_WARNINGS
#define limW(x) ((x >= 0) && (x < WIDTH))?1:0
#define limH(x) ((x >= 0) && (x < HEIGHT))?1:0
#define lim(x, a, b) ((x>= a) && (x <= b))?1:0
#define IRIS_ADD 1
#define IRIS_CHK 0

#define DB_TXT "users.txt"
#define DB_RAW "irisdb.raw"

#ifdef __cplusplus
extern "C"
{
#endif
#include "irisTop.h"
#include "sobel.h"
#include "hough.h"
#include "segIris.h"
#include "resIris.h"
#include "SDL_display.h"
#include "haarEncode.h"
#include "hamMatching.h"
#include "capturev4l2.h"
#ifdef __cplusplus
}
#endif

#endif //__UTILS_H_
