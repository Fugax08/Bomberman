#include <SDL.h>

int bmp_parser_to_texture(char* content, SDL_Renderer* renderer, SDL_Texture** texture);

int bmp_open_file(const char* fileName, char** content);