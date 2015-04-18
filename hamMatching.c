#include "utils.h"

u8_int runMatching(IRISCONFIG* m)
{

    u16_int ones = 0;
    u16_int tempOnes = HD_THR;
    u16_int i;
    u8_int j;
    u8_int width  = R_WIDTH  >> 5;
    u8_int height = R_HEIGHT >> 1;
    u16_int size = width * height;
    u8_int oneByte;
    u8_int irisID;


    for(j = 0; j < (m->users_cnt << 2); j++)
    {
        for(i = 0; i < size; i++)
        {
            oneByte = m->haar_st->hHaar2[i] ^ m->users_db[j * 256 + i];
            ones += __builtin_popcount(oneByte);
        }
        if(ones < tempOnes)
        {
            irisID = j >> 2;
            tempOnes = ones;
            printf("User identified as %s\n HD: %d ID: %d J: %d\n", m->users[irisID], tempOnes, irisID, j);
        }
        ones = 0;
    }
    return 1;
}
