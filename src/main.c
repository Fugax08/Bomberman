#include <SDL.h>
#include <stdio.h>
#include "parse_bmp.h"

int main(int argc, char **argv)
{
    level_t level001;
    int32_t level001_cells[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    level_init(&level001, 8, 8, 64, level001_cells);
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

    SDL_rect cell_rect = {0, 0, level001.cell_size, level001.cell_size}; 

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

        SDL_SetRenderDrawColor (renderer , 0, 0, 0, 0);
        SDL_RenderClear (renderer );

        for(uint32_t row = 0; row < level001.rows ;row++)
        {
            for(uint32_t col = 0; col < level001.cols ;col++)
            {
                int32_t cell = level_cell(&level001, col, row);
                int32_t cell_texture = cell & 0xff;
                if(cell_texture == BLOCK_GROUND)
                {
                    SDL_SetRenderDrawColor (renderer , 0, 255, 0, 255);
                    cell_rect.x = col * level001.cell_size;
                    cell_rect.y = row * level001.cell_size;
                    SDL_RenderFillRect(renderer, &cell_rect);
                }
            }
        }
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