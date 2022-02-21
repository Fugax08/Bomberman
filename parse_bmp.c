#include <SDL.h>

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_RWops *rw = SDL_RWFromFile("Capture.bmp", "rb");
    Sint64 file_size = SDL_RWsize(rw);

    SDL_Log("the file size is %lld",file_size);

    Uint8 *content = SDL_malloc(file_size);
    
    SDL_RWread(rw, content, file_size, 1);
    SDL_RWclose(rw);

    SDL_Log("First two chars %c %c",content[0],content[1]);
    Uint32 bmp_file_size;
    SDL_memcpy(&bmp_file_size, content + 2 , 4); 

    SDL_Log("the bmp file size %llu",bmp_file_size);
    
    Uint32 bmp_pixels_offset;
    SDL_memcpy(&bmp_pixels_offset, content + 10 , 4); 

    SDL_Log("the bmp pixels are at offset %llu", bmp_pixels_offset);

    Uint32 image_size[2];
    SDL_memcpy(image_size, content + 18 , 8); 
    
    SDL_Log("the bmp size is %llux%llu", image_size[0], image_size[1]);
    
    Uint32 pixel_data_size;
    SDL_memcpy(&pixel_data_size, content + 34 , 4); 
    
    SDL_Log("the bmp pixel data size is %llu", pixel_data_size);
    
    const Uint32 alignment = 4;
    Uint32 row_size = image_size[0] *3;
    SDL_Log("the bmp row size is %llu", row_size);
    Uint32 padded_row_size = (row_size / alignment) * alignment;
    if(row_size % alignment != 0)
    {
        padded_row_size += alignment;
    }
    SDL_Log("the bmp padded row size is %llu", padded_row_size);

    Uint32 full_padded_size = padded_row_size * image_size[1];
    SDL_Log("the bmp padded pixel data size is %llu", full_padded_size);

    return 0;
}