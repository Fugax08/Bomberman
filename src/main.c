#include <SDL.h>
#include <stdio.h>
#include "parse_bmp.h"

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow ("SDL is active!" , 100, 100, 1024, 1024, 0);
    if (!window)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        goto quit;
    }

    SDL_Texture *texture = SDL_CreateTexture (renderer, SDL_PIXELFORMAT_RGBA32 , SDL_TEXTUREACCESS_STATIC , 128, 128);
    if(!texture)
    {
        SDL_Log("Unable to create texture: %s", SDL_GetError());
        goto quit;
    }

    unsigned int *pixels = SDL_malloc(128 * 128 * 4);
    if(!pixels)
    {
        SDL_Log("Unable to alloctae texture moemory: %s", SDL_GetError());
        goto quit;
    }
    /*for(int y=0; y<128; y++)
    {
        for(int x=0; x<128; x++)
        {
            size_t offset = y * 128 + x;
            pixels[offset] = 0xFF000000;
            pixels[offset] |= (rand() % 256) << 16; 
            pixels[offset] |= (rand() % 256) << 8;
            pixels[offset] |= (rand() % 256);  
        }

    }
    SDL_Rect full = {0, 0, 128, 128};
    SDL_UpdateTexture (texture, &full , pixels, 128 * 4);*/

    const char* fileName = "Capture.bmp";
	SDL_RWops* rw = SDL_RWFromFile(fileName, "rb");
	if (!rw)
	{
		return -1;
	}

	Sint64 file_size = SDL_RWsize(rw);
	char *content = (char*)SDL_malloc(file_size);
	if (!content)
	{
		SDL_RWclose(rw);
		return -1;
	}

	SDL_RWread(rw, content, file_size, 1);
	SDL_RWclose(rw);
    bmp_parser(content, renderer, &texture);

    SDL_SetTextureAlphaMod (texture, 255);
    SDL_SetTextureBlendMode (texture, SDL_BLENDMODE_BLEND );

    int running = 1;
    int x=0;
    while (running )
    {
        SDL_Event event;
        while(SDL_PollEvent (&event))
        {
            if (event .type == SDL_QUIT )
            {
                running = 0;
            }
        }
        SDL_SetRenderDrawBlendMode (renderer , SDL_BLENDMODE_NONE );
        SDL_SetRenderDrawColor (renderer , 100, 0, 0, 255);
        SDL_RenderClear (renderer );

        SDL_SetRenderDrawColor (renderer , 255, 255, 255, 255);
        SDL_Rect rect = {x, 100, 300, 300};
        SDL_RenderDrawRect (renderer , &rect);

        SDL_SetRenderDrawBlendMode (renderer , SDL_BLENDMODE_BLEND );
        SDL_SetRenderDrawColor (renderer , 255, 0, 255, 255);
        rect.x = 20;
        rect.y = 120;
        rect.w=200;
        rect.h =200;
        SDL_RenderFillRect(renderer, &rect);
        x++;

        SDL_Rect source = {0, 0, 128, 128};
        SDL_Rect target = {400, 400, 128, 128};
        SDL_RenderCopy (renderer, texture, &source , &target );

        SDL_RenderPresent (renderer);
    }


    quit:
        if(pixels)
        {
            SDL_free(pixels);
        }
        if(texture)
        {
            SDL_DestroyTexture(texture);
        }
        if(renderer)
        {
            SDL_DestroyRenderer(renderer);
        }
        if(window)
        {
            SDL_DestroyWindow(window);
        }

        SDL_Quit();
        return 0;
}