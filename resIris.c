#include "utils.h"

u8_int initResize(IRISCONFIG* r)
{
    r->res_st->resWidth  = R_WIDTH;
    r->res_st->resHeight = R_HEIGHT;
    r->res_st->resPattern = (u8_int*)malloc(r->res_st->resWidth * r->res_st->resHeight);

    return 1;
}

u8_int runResize(IRISCONFIG* r)
{
    u8_int  i;
    u16_int j;
    s32_float gx,gy;
    s32_float l1,l2;
    u16_int gxi, gyi;
    u8_int tl,tr,bl,br; //corner pixels
    #if DEBUG
    static int count = 0;
    char sir[100];
    FILE* f;
    #endif // DEBUG

    for(i = 0; i < r->res_st->resHeight; i++)
    {
        for(j = 0; j < r->res_st->resWidth; j++)
        {
            gx = (j/(s32_float)(r->res_st->resWidth)) * (P_WIDTH - 1);
            gy = (i/(s32_float)(r->res_st->resHeight)) * (r->seg_st->radNo - 1);
            gxi = (u16_int)gx;
            gyi = (u16_int)gy;

            tl = r->seg_st->outPattern[(P_WIDTH * gyi) + gxi];
            tr = r->seg_st->outPattern[(P_WIDTH * gyi) + gxi + 1];
            bl = r->seg_st->outPattern[(P_WIDTH * (gyi + 1)) + gxi];
            br = r->seg_st->outPattern[(P_WIDTH * (gyi + 1)) + gxi + 1];

            l1 = tl + (tr - tl)*(gx - gxi);
            l2 = bl + (br - bl)*(gx - gxi);

            r->res_st->resPattern[r->res_st->resWidth * i + j] = (u8_int)(l1 + (l2 - l1)*(gy - gyi));
        }
    }
    #if DEBUG
        sprintf(sir, "res_%04d_%04d_%04d.raw", ++count, r->res_st->resWidth, r->res_st->resHeight);
        f = fopen(sir, "wb");
        fwrite(r->res_st->resPattern, 1, r->res_st->resWidth * r->res_st->resHeight, f);
        fclose(f);
    #endif // DEBUG


    return 1;
}


u8_int freeResize(IRISCONFIG* r)
{
    free(r->res_st->resPattern);
    return 1;
}
