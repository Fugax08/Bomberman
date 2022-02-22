#include <SDL.h>

int bmp_parser(Uint8* content, SDL_Renderer* renderer, SDL_Texture** texture)
{
	Uint8 alignment = 4;
    Uint8 channels = 3;
	
	Uint32 width, height;
	SDL_memcpy(&width, content + 18, 4);
	SDL_memcpy(&height, content + 22, 4);

	*texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STATIC, width, height);
	if (!*texture)
		return -1;

	Uint8* pixels = SDL_malloc(width * height * channels);
	if (!pixels)
	{
		SDL_free(*texture);
		return -1;
	}

	Uint8* pixelsHead = content + (*(content + 10));

	Uint32 rowSize = width * channels;
	Uint32 paddedRowSize = (rowSize / alignment) * alignment;
	if(rowSize % alignment != 0)
	{
		paddedRowSize += alignment;
	}


	Uint32 x = 0;
	for (Uint32 y = height - 1; y > -1; --y)
	{
		SDL_memcpy(pixels + x * rowSize, pixelsHead + y * paddedRowSize, rowSize);
		++x;
	}
	SDL_UpdateTexture(*texture, NULL, pixels, rowSize);
	SDL_free(pixels);
	return 0;
}