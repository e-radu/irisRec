#include "utils.h"

u8_int initDisplay(IRISCONFIG* d)
{
    u16_int i;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }
    d->sdl_st->dispWnd = SDL_CreateWindow("Iris Recognition",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, d->width, d->height, SDL_WINDOW_SHOWN);
    if(d->sdl_st->dispWnd == NULL)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }
    d->sdl_st->dispSurf = SDL_GetWindowSurface(d->sdl_st->dispWnd);
    if(d->sdl_st->dispSurf == NULL)
    {
        printf( "Window Surface not returned! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }

    for(i = 0; i < 256; i++)
    {
        d->sdl_st->colors[i].r = i;
        d->sdl_st->colors[i].g = i;
        d->sdl_st->colors[i].b = i;
    }
    return 1;
}

u8_int runDisplay(IRISCONFIG* d, u8_int* frame)
{
    //SDL_PixelFormat *fmt;
    d->sdl_st->dispImg = SDL_CreateRGBSurfaceFrom(frame, d->width, d->height, 8, d->width, 0, 0, 0, 0);
    if(d->sdl_st->dispImg == NULL)
    {
        printf( "Image could not be loaded! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }
    SDL_SetPaletteColors(d->sdl_st->dispImg->format->palette, d->sdl_st->colors, 0, 256);
    SDL_BlitSurface(d->sdl_st->dispImg, 0, d->sdl_st->dispSurf, 0);
    SDL_UpdateWindowSurface(d->sdl_st->dispWnd);
    return 1;
}


u8_int freeDisplay(IRISCONFIG* d)
{
    SDL_FreeSurface(d->sdl_st->dispImg);
    d->sdl_st->dispImg = NULL;

    SDL_DestroyWindow(d->sdl_st->dispWnd);
    d->sdl_st->dispWnd = NULL;

    SDL_Quit();
    return 1;
}
