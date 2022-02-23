#include "..\inc\bomberman.h"

int32_t move_on_level(level_t *level, movable_t *movable, const float delta_x, const float delta_y)
{
    float new_x = movable->x + delta_x;
    float new_y = movable->y + delta_y;

    if(new_x < 0)
        new_x = 0;
    else if(new_x + movable->width >= level->cols * level->cell_size)
        new_x = (level->cols * level->cell_size) - movable->width;

    if(new_y < 0)
        new_y = 0;
    else if(new_y + movable->height >= level->rows * level->cell_size)
        new_y = (level->rows * level->cell_size) - movable->height;

    movable->x=new_x;
    movable->y=new_y;

    return -1;
    
}