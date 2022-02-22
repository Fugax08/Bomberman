#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include <stdint.h>

#define BLOCK_MASK_UNWALKABLE 0X0100
#define BLOCK_MASK_TELEPORT 0X0200
#define BLOCK_MASK_EXIT 0X0400
#define BLOCK_GROUND 0
#define BLOCK_WALL_BLOCK MASK_UNWALKABLE | 1
#define BLOCK_DESTROYABLE BLOCK_MASK_UNWALKABLE | 2

typedef struct level
{
    uint32_t cols; //numer of cols
    uint32_t rows; // numerb of rows
    uint32_t cell_size; // size in pixel of single cell
    int32_t *cells; // content of the level
} level_t;

//initialize a level
int level_init(level_t *level, const uint32_t cols, const uint32_t rows, const uint32_t cell_size, int32_t *cells);

int32_t level_cell(level_t *level, const uint32_t col, const uint32_t row);

#endif