#include "utils.h"

u8_int initSeg(IRISCONFIG* s)
{
    s->seg_st->outPattern = (u8_int*)malloc(s->seg_st->radNo * P_WIDTH);
    return 1;
}

u8_int runSeg(IRISCONFIG* s)
{
    u8_int  i;
    u16_int j;
    u16_int x,y;
    u16_int xCenter, yCenter;
    s32_float theta[P_WIDTH];


    theta[0] = 0;
    for(j = 1; j < P_WIDTH; j++)
    {
        theta[j] = theta[j - 1] + PI/(P_WIDTH>>1);
    }

    //check for center alignment
    if(abs(s->hough_st->maxCoord[0].x - s->hough_st->maxCoord[1].x) > 10)
        return -1;
    if(abs(s->hough_st->maxCoord[0].y - s->hough_st->maxCoord[1].y) > 10)
        return -1;

    xCenter = (s->hough_st->maxCoord[0].x + s->hough_st->maxCoord[1].x)>>1;
    yCenter = (s->hough_st->maxCoord[0].y + s->hough_st->maxCoord[1].y)>>1;
    //check for out of bounds
    if(!lim(xCenter, s->seg_st->radNo + 1, s->width - s->seg_st->radNo - 1))
        return -1;
    if(!lim(yCenter, s->seg_st->radNo + 1, s->height - s->seg_st->radNo -1))
        return -1;
    for(i = 0; i < s->seg_st->radNo; i++)
    {
        for(j = 0; j < P_WIDTH; j++)
        {
            x = ((s->hough_st->maxCoord[0].rad + i)*cos(theta[j])) + yCenter;
            y = ((s->hough_st->maxCoord[0].rad + i)*sin(theta[j])) + xCenter;

            s->seg_st->outPattern[P_WIDTH * i + j] = s->frame[s->width * y + x];
        }
    }
    return 1;
}

u8_int freeSeg(IRISCONFIG* s)
{
    free(s->seg_st->outPattern);
    return 1;
}
