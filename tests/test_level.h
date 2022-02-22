#define CLOVE_ENABLE_MANUAL
#include "clove.h"
#include "../inc/bomberman.h"

CLOVE_TEST(LevelInitializationNULL)
{
    CLOVE_INT_EQ(level_init(NULL, 0, 0, 0, NULL), -1);
}

CLOVE_TEST(LevelInitializationZeroCols)
{
    level_t level;
    CLOVE_INT_EQ(level_init(&level, 0, 100, 100, NULL), -1);
}

CLOVE_TEST(LevelInitializationZeroRows)
{
    level_t level;
    CLOVE_INT_EQ(level_init(&level, 100, 0, 100, NULL), -1);
}

CLOVE_TEST(LevelInitializationZeroSize)
{
    level_t level;
    CLOVE_INT_EQ(level_init(&level, 100, 100, 0, NULL), -1);
}


CLOVE_TEST(LevelInitializationZerocells)
{
    level_t level;
    CLOVE_INT_EQ(level_init(&level, 100, 100, 10, NULL), 0);
}

CLOVE_SUITE(LevelSuite) {
    CLOVE_SUITE_TESTS(
        LevelInitializationNULL, 
        LevelInitializationZeroCols,
        LevelInitializationZeroRows,
        LevelInitializationZeroSize,
        LevelInitializationZerocells
    );
}

