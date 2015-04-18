#include "utils.h"

u8_int initHaar(IRISCONFIG* h)
{
    h->haar_st->width  = R_WIDTH ;
    h->haar_st->height = R_HEIGHT;
    h->haar_st->hHaar1 = (u8_int*)malloc((h->haar_st->width >> 1)*h->haar_st->height);
    h->haar_st->vHaar1 = (u8_int*)malloc((h->haar_st->width >> 1)*(h->haar_st->height >> 1));
    h->haar_st->hHaar2 = (u8_int*)malloc((h->haar_st->width >> 5)*(h->haar_st->height >> 1));
    return 1;
}

u8_int runHaar(IRISCONFIG* h)
{
    u16_int i,j,k;
    u16_int halfWidth, halfHeight, qWidth;
    u8_int encByte, dataByte;
    halfWidth = h->haar_st->width >> 1;
    halfHeight = h->haar_st->height >> 1;
    qWidth = h->haar_st->width >> 5;

    for(i = 0; i < h->haar_st->height; i++)
    {
        for(j = 0; j < halfWidth; j++)
        {
            h->haar_st->hHaar1[halfWidth * i + j] = (h->res_st->resPattern[h->haar_st->width * i + 2*j] +  h->res_st->resPattern[h->haar_st->width * i + 2*j + 1]) >> 1;
        }
    }

    for(i = 0; i < halfHeight; i++)
    {
        for(j = 0; j < halfWidth; j++)
        {
            h->haar_st->vHaar1[halfWidth * i + j] = (h->haar_st->hHaar1[halfWidth * 2 * i + j] +  h->haar_st->hHaar1[halfWidth * (2 * i + 1) + j]) >> 1;
        }
    }

    for(i = 0; i < halfHeight; i++)
    {
        for(j = 0; j < qWidth; j++)
        {
            encByte = 0;
            for(k = 0; k < 8;k++)
            {
                dataByte = (((h->haar_st->vHaar1[halfWidth * i + 2 * (8 * j + k)] - h->haar_st->vHaar1[halfWidth * i + 2 *(8 * j + k) + 1]) >> 1) < 0)?1:0;
                encByte = encByte | (dataByte << k);
            }
            h->haar_st->hHaar2[qWidth * i + j] = encByte;
        }
    }


        #if DEBUG
        sprintf(sir, "haarH_%04d_%04d_%04d.raw", ++c1, halfWidth, h->haar_st->height);
        f = fopen(sir, "wb");
        fwrite(h->haar_st->hHaar1, 1, halfWidth * h->haar_st->height, f);
        fclose(f);
        sprintf(sir, "haarV_%04d_%04d_%04d.raw", ++c2, halfWidth, halfHeight);
        f = fopen(sir, "wb");
        fwrite(h->haar_st->vHaar1, 1, halfWidth * halfHeight, f);
        fclose(f);
        #endif // DEBUG
        #if OUT_PATT
        sprintf(sir, "database/enc_%04d.raw", c3++);
        f = fopen(sir, "wb");
        fwrite(h->haar_st->hHaar2, 1, (qWidth * halfHeight), f);
        fclose(f);
        #endif
    return 1;
}


u8_int freeHaar(IRISCONFIG* h)
{
    free(h->haar_st->hHaar1);
    free(h->haar_st->vHaar1);
    free(h->haar_st->hHaar2);

    return 1;
}
