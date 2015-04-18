#include "utils.h"

u8_int initHough(IRISCONFIG* h)
{
    u8_int i;
    for (i = 0; i < RADIINO; i++)
    {
        h->hough_st->maxRad[2*i    ].rad = i + SMALL_RAD;
        h->hough_st->maxRad[2*i + 1].rad = i + SMALL_RAD;
    }
    h->hough_st->cumMatrix = (u32_int*)malloc(h->width*h->height*sizeof(u32_int)); //check for overflow
    return 1;
}

u8_int runHough(IRISCONFIG* h)
{
    u16_int i,j;
    u8_int  k  ;
    u16_int xm1, xm2, ym1, ym2;
    u32_int maxVal1, maxVal2;
    //memset(h->hough_st->maxRad, 0, 2*RADIINO*sizeof(MAXRAD));
    for(k = 0; k < RADIINO; k++)
    {
        memset(h->hough_st->cumMatrix, 0, h->width*h->height*sizeof(u32_int));
        maxVal1 = 0;
        maxVal2 = 0;
        h->hough_st->maxRad[2*k].maxVal = 0;
        h->hough_st->maxRad[2*k + 1].maxVal = 0;
        for (i = 0; i < h->height; i++)
        {
            for (j = 0; j < h->width; j++)
            {
                if (h->sobel_st->edgeMap[h->width * i + j] > 0)
                {
                    xm1 = i + h->hough_st->maxRad[2*k].rad * cos(h->sobel_st->angleMap[h->width * i + j]);
                    xm2 = i - h->hough_st->maxRad[2*k].rad * cos(h->sobel_st->angleMap[h->width * i + j]);
                    ym1 = j + h->hough_st->maxRad[2*k].rad * sin(h->sobel_st->angleMap[h->width * i + j]);
                    ym2 = j - h->hough_st->maxRad[2*k].rad * sin(h->sobel_st->angleMap[h->width * i + j]);

                    if(xm1 >= 0 && xm1 < h->height && ym1 >= 0 && ym1 < h->width)
                    {
                        h->hough_st->cumMatrix[h->width * xm1 + ym1]++;
                        if(h->hough_st->cumMatrix[h->width * xm1 + ym1] > maxVal1)
                        {
                            maxVal1 = h->hough_st->cumMatrix[h->width * xm1 + ym1];
                            h->hough_st->maxRad[2*k].x = xm1;
                            h->hough_st->maxRad[2*k].y = ym1;
                            h->hough_st->maxRad[2*k].maxVal = maxVal1;
                        }
                    }
                    if(xm2 >= 0 && xm2 < h->height && ym2 >= 0 && ym2 < h->width)
                    {
                        h->hough_st->cumMatrix[h->width * xm2 + ym2]++;
                        if(h->hough_st->cumMatrix[h->width * xm2 + ym2] > maxVal2)
                        {
                            maxVal2 = h->hough_st->cumMatrix[h->width * xm2 + ym2];
                            h->hough_st->maxRad[2*k + 1].x = xm2;
                            h->hough_st->maxRad[2*k + 1].y = ym2;
                            h->hough_st->maxRad[2*k + 1].maxVal = maxVal2;
                        }

                    }
                }
            }
        }
        #if DEBUG
        printf("Rad: %3d, max: %4d, pos:(%4d, %4d)\n",
                h->hough_st->maxRad[2*k].rad,
                h->hough_st->maxRad[2*k].maxVal,
                h->hough_st->maxRad[2*k].x,
                h->hough_st->maxRad[2*k].y
        );
        printf("Rad: %3d, max: %4d, pos:(%4d, %4d)\n",
                h->hough_st->maxRad[2*k+1].rad,
                h->hough_st->maxRad[2*k+1].maxVal,
                h->hough_st->maxRad[2*k+1].x,
                h->hough_st->maxRad[2*k+1].y
        );
        #endif // DEBUG
    }
    h->hough_st->maxCoord[0].maxVal = 0;
    h->hough_st->maxCoord[1].maxVal = 0;
    //search for the maximum value for small radii
    for(i = 0; i < (RADIINO); i++)
        if (h->hough_st->maxCoord[0].maxVal < h->hough_st->maxRad[i].maxVal)
            h->hough_st->maxCoord[0] = h->hough_st->maxRad[i];
    //search for the maximum value for large radii
    for(i = RADIINO; i < (RADIINO<<1); i++)
        if (h->hough_st->maxCoord[1].maxVal < h->hough_st->maxRad[i].maxVal)
            h->hough_st->maxCoord[1] = h->hough_st->maxRad[i];

 //   #if DEBUG
    printf("RadS: %3d, max: %4d, pos:(%4d, %4d)\n",
                h->hough_st->maxCoord[0].rad,
                h->hough_st->maxCoord[0].maxVal,
                h->hough_st->maxCoord[0].x,
                h->hough_st->maxCoord[0].y
                );
    printf("RadB: %3d, max: %4d, pos:(%4d, %4d)\n",
                h->hough_st->maxCoord[1].rad,
                h->hough_st->maxCoord[1].maxVal,
                h->hough_st->maxCoord[1].x,
                h->hough_st->maxCoord[1].y
                );


 //   #endif // DEBUG
    return 1;
}

u8_int freeHough(IRISCONFIG* h)
{
    free(h->hough_st->cumMatrix);
    return 1;
}
