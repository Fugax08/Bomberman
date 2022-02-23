#include <SDL.h>
#include "bomberman.h"
#include "level001.h"
#include "parse_bmp.h"

int main(int argc, char **argv)
{
    level_t level001;
    level_init(&level001, 8, 8, 64, level001_cells);

    bomberman_t player0;
    player0.movable.x = 100;
    player0.movable.y = 100;
    player0.movable.width = 32;
    player0.movable.height = 32;
    player0.movable.speed = 48;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow ("Bomberman" , 100, 100, level001.cols * level001.cell_size, level001.rows * level001.cell_size, 0);
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

    SDL_Rect cell_rect = {0, 0, level001.cell_size, level001.cell_size}; 
    SDL_Rect player0_rect = {0, 0, player0.movable.width, player0.movable.height}; 

    float delta_right = 0;
    float delta_left = 0;
    float delta_up = 0;
    float delta_down = 0;

    int running = 1;
    while (running )
    {
        SDL_Event event;
        while(SDL_PollEvent (&event))
        {
            if (event .type == SDL_QUIT )
            {
                running = 0;
            }
            if(event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    delta_right = player0.movable.speed * (1.0 / 60);
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    delta_left = -player0.movable.speed * (1.0 / 60);
                }
                if (event.key.keysym.sym == SDLK_UP)
                {
                    delta_up = -player0.movable.speed * (1.0 / 60);
                }
                
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    delta_down = player0.movable.speed * (1.0 / 60);
                }
            }
            if(event.type == SDL_KEYUP)
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    delta_right = 0;
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    delta_left = 0;
                }
                if (event.key.keysym.sym == SDLK_UP)
                {
                    delta_up = 0;
                }
                
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    delta_down = 0;
                }
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
                cell_rect.x = col * level001.cell_size;
                cell_rect.y = row * level001.cell_size;
                if(cell_texture == BLOCK_GROUND)
                {
                    SDL_SetRenderDrawColor (renderer , 0, 255, 0, 255);
                    SDL_RenderFillRect(renderer, &cell_rect);
                }
                else if(cell_texture == BLOCK_WALL)
                {
                    SDL_SetRenderDrawColor (renderer , 100, 50, 0, 255);
                    SDL_RenderFillRect(renderer, &cell_rect);
                }
                else if(cell_texture == BLOCK_DESTROYABLE)
                {
                    SDL_SetRenderDrawColor (renderer , 0, 50, 50, 255);
                    SDL_RenderFillRect(renderer, &cell_rect);
                }
            }
        }

        move_on_level(&level001, &player0.movable, delta_right + delta_left, delta_down + delta_up);
        player0_rect.x = player0.movable.x;
        player0_rect.y = player0.movable.y;
        SDL_SetRenderDrawColor (renderer , 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player0_rect);

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