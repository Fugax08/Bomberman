#include <SDL.h>

int bmp_parser_to_texture(Uint8* content, SDL_Renderer* renderer, SDL_Texture** texture)
{
	Uint8 alignment = 4;
    Uint8 channels = 3;
	
	Uint8* pixels_head = content + (*(content + 10));
	
	Uint32 width, height;
	SDL_memcpy(&width, content + 18, 4);
	SDL_memcpy(&height, content + 22, 4);

	Uint32 row_size = width * channels;
	Uint32 padded_row_size = (row_size / alignment) * alignment;
	if(row_size % alignment != 0)
	{
		padded_row_size += alignment;
	}

	*texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STATIC, width, height);
	if (!*texture)
		return -1;

	Uint8* pixels = SDL_malloc(width * height * channels);
	if (!pixels)
	{
		SDL_free(*texture);
		return -1;
	}

	for (Uint32 i = 0; i < height; i++)
	{
		Uint8 *texture_row = pixels + (i * row_size);
        Uint8 *bmp_row = pixels_head + ((height - 1) - i) * padded_row_size;
        SDL_memcpy(texture_row, bmp_row, row_size);
	}
	SDL_UpdateTexture(*texture, NULL, pixels, row_size);
	SDL_free(pixels);
	return 0;
}

int bmp_open_file(const char* fileName, char** content)
{
	SDL_RWops* rw = SDL_RWFromFile(fileName, "rb");
	if (!rw)
	{
		return -1;
	}

	Sint64 file_size = SDL_RWsize(rw);
	*content = (char*)SDL_malloc(file_size);
	if (!(*content))
	{
		SDL_RWclose(rw);
		return -1;
	}

	SDL_RWread(rw, *content, file_size, 1);
	SDL_RWclose(rw);
	return 0;
}
