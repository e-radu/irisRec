#ifndef __IRISTOP_H_
#define __IRISTOP_H_

#include "utils.h"

typedef struct _ARGS
{
    char*   dev_name;
    char*   usr_name;
    u8_int  mode    ;
} ARGS;

typedef struct _SOBEL
{
    u8_int minThreshold;
    u8_int maxThreshold;
    s8_int yMask[3][3] ;
    s8_int xMask[3][3] ;
    u8_int*    edgeMap ;
    u8_int*    aveMap  ;
    s32_float* angleMap;

} SOBEL;

typedef struct _MAXRAD
{
    u32_int maxVal;
    u16_int x;
    u16_int y;
    u8_int  rad;
} MAXRAD;

typedef struct _HOUGH
{
    u32_int*    cumMatrix;
    MAXRAD maxRad[2*RADIINO];
    MAXRAD maxCoord[2];
} HOUGH;

typedef struct _SEG
{
    u8_int radNo;
    u8_int* outPattern;
}SEG;

typedef struct _RESIZE
{
    u8_int*  resPattern;
    u16_int  resWidth;
    u8_int   resHeight;
} RESIZE;

typedef struct _SDL
{
    SDL_Window*  dispWnd;
    SDL_Surface* dispSurf;
    SDL_Surface* dispImg;
    SDL_Color colors[256];
} SDL;

typedef struct _HAAR
{
    u8_int* hHaar1;
    u8_int* vHaar1;
    u8_int* hHaar2;
    u16_int width;
    u16_int height;
} HAAR;

typedef struct _PATT
{
    char* name[100];
    u8_int* pattern;
}PATT;


typedef struct _IRISCONFIG
{
    u8_int* frame    ;
    u16_int width, height;
    u8_int  mode     ;
    char*   user_name;
    char    users[16][64];
    u8_int* users_db ;
    u8_int  users_cnt;
    u8_int  frame_cnt;
    HOUGH*  hough_st ;
    SOBEL*  sobel_st ;
    SEG*    seg_st   ;
    RESIZE* res_st   ;
    SDL*    sdl_st   ;
    HAAR*   haar_st  ;
    PATT*   patt_st  ;
    int     fd       ; //video device id
    char*   dev_name ;
    u8_int  camActive;
} IRISCONFIG;

u8_int initIris(IRISCONFIG* icfg);
u8_int runIris (IRISCONFIG* icfg);
u8_int freeIris(IRISCONFIG* icfg);

#endif // __IRISTOP_H_
