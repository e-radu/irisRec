#include "utils.h"

u8_int initDatabase(IRISCONFIG* cfg)
{
//databse is formed of 2 files
// 1. txt file with saved user names
// 2. raw file with encoded iris pattern (3 per user)
int user_count = 0;
u8_int i = 0;
FILE *ft, *fr;
char buf[256];
ft = fopen(DB_TXT, "r");
if(ft == NULL) {printf("Could not open user name file\n"); return -1;}
fgets(buf, sizeof(buf), ft);
sscanf(buf, "%d", &user_count);
cfg->users_cnt = user_count;
printf("Users in database: %d\n", cfg->users_cnt);
for(i = 0; i < cfg->users_cnt; i++)
{
fgets(buf, sizeof(buf), ft);
sscanf(buf, "%s", cfg->users[i]);
}
fclose(ft);
fr = fopen(DB_RAW, "rb");
if(fr == NULL) {printf("Could not open user database file\n"); return -1;}
cfg->users_db = (u8_int*)malloc(256*cfg->users_cnt);
fread(cfg->users_db, 1, 256*cfg->users_cnt, fr);
fclose(fr);
return 1;
}

u8_int initIris(IRISCONFIG* cfg)
{
    cfg->sobel_st = (SOBEL*) malloc(sizeof(SOBEL));
    cfg->hough_st = (HOUGH*) malloc(sizeof(HOUGH));
    cfg->seg_st   = (SEG*  ) malloc(sizeof(SEG  ));
    cfg->res_st   = (RESIZE*)malloc(sizeof(RESIZE));
    cfg->sdl_st   = (SDL*)   malloc(sizeof(SDL));
    cfg->haar_st  = (HAAR*)  malloc(sizeof(HAAR));
    cfg->patt_st  = (PATT*)  malloc(sizeof(PATT));

    memset(cfg->sobel_st, 0, sizeof(SOBEL ));
    memset(cfg->hough_st, 0, sizeof(HOUGH ));
    memset(cfg->seg_st  , 0, sizeof(SEG   ));
    memset(cfg->res_st  , 0, sizeof(RESIZE));
    memset(cfg->sdl_st  , 0, sizeof(SDL   ));
    memset(cfg->haar_st , 0, sizeof(HAAR  ));
    memset(cfg->patt_st , 0, sizeof(PATT  ));

    initDatabase(cfg);
    initSobel(cfg);
    initHough(cfg);
    initResize(cfg);
    initHaar(cfg);
    cfg->fd = open_device(cfg->dev_name);
    if(cfg->fd == -1)
        return -1;
    initDisplay(cfg);
    return 1;
}

u8_int drawCircles(IRISCONFIG* d)
{
    u8_int  i;
    u16_int x1,y1,x2,y2;
    s32_float theta[DP];
    theta[0] = 0;
    for (i = 1; i < DP; i++)
    {
        theta[i] = theta[i - 1] + PI/(DP>>1);
        x1 = d->hough_st->maxCoord[0].rad*cos(theta[i]) + d->hough_st->maxCoord[0].y;
        y1 = d->hough_st->maxCoord[0].rad*sin(theta[i]) + d->hough_st->maxCoord[0].x;
        d->frame[d->width * y1 + x1] = 255;
        x2 = d->hough_st->maxCoord[1].rad*cos(theta[i]) + d->hough_st->maxCoord[1].y;
        y2 = d->hough_st->maxCoord[1].rad*sin(theta[i]) + d->hough_st->maxCoord[1].x;
        d->frame[d->width * y2 + x2] = 255;
    }
    return 1;
}

u8_int addToDatabase(IRISCONFIG* cfg)
{
FILE *ft, *fr;
u8_int i;
static u8_int patt_cnt = 0;
if(++cfg->frame_cnt > 5)
{
fr = fopen(DB_RAW, "ab");
if(fr == NULL) {printf("Could not open user database file\n"); return -1;}
fwrite(cfg->haar_st->hHaar2, 1, 256, fr);
if(++patt_cnt > 3)
{
 ft = fopen(DB_TXT, "w");
 if(ft == NULL) {printf("Could not open user name file\n"); return -1;}
 fprintf(ft, "%d\n", (cfg->users_cnt + 1));
 for(i = 0; i < cfg->users_cnt; i++)
    fprintf(ft, "%s\n", cfg->users[i]);

 fprintf(ft, "%s\n", cfg->user_name);
 fclose(ft);
 printf("Added %d images to database for user %s\n", patt_cnt, cfg->user_name);
 return 2;
}
fclose(fr);

cfg->frame_cnt = 0;
}
return 1;
}

u8_int runIris(IRISCONFIG* cfg)
{
    SDL_Event event;
    //FILE* fn;
    u8_int loop;
    u8_int warm;
    //static int c = 0;
    u8_int count = 0;
    //char sir[128];
    //u8_int i;
    loop = 1;

    if(print_caps(cfg->fd))
        return 1;

    if(init_mmap(cfg->fd))
        return 1;

    while(loop)
    {
        count++;
        if(count > 10) {warm = 1;}
	else {printf("Warming %d \n", (10-count));}
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                loop = 0;
            }
        }
        if(capture_image(cfg))
            return 1;

        if(warm)
        {
            runSobel(cfg);
            //printf("Sobel");
            runHough(cfg);
            cfg->seg_st->radNo = cfg->hough_st->maxCoord[1].rad - cfg->hough_st->maxCoord[0].rad;
            if (lim(cfg->seg_st->radNo, 20, 40))
            {
                initSeg(cfg);
                if(runSeg(cfg) == 1)
                {
		    printf("Segmentation done!\n");
                    runResize(cfg);
printf("Segmentation done!\n");
                    drawCircles(cfg);
printf("Drawing done!\n");
                    runHaar(cfg);
printf("Encoding done!\n");
                    if(cfg->mode == IRIS_ADD)
                    {
                        //check for best iris case
                        if(addToDatabase(cfg) == 2)
                            return 1;
                    }
                    else
                    {
                    runMatching(cfg);
printf("Matching done!\n");
                    }
                }
                else
                {
                cfg->frame_cnt = 0;
                }
                freeSeg(cfg);
            }
        }
        runDisplay(cfg, cfg->frame);
    }
    return 1;
}

u8_int freeIris(IRISCONFIG* cfg)
{
    freeDisplay(cfg);
    close_device(cfg->fd);
    freeSobel (cfg);
    freeHough (cfg);
    freeHaar  (cfg);
    freeResize(cfg);

    return 1;
}
