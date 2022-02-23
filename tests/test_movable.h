#define CLOVE_ENABLE_MANUAL
#include "clove.h"
#include "../inc/bomberman.h"

CLOVE_TEST(MovableFixPositionX)
{
    level_t level;
    int32_t map[] = {0, 0, 0, 0};
    level_init(&level, 4, 4, 8, map);
    movable_t movable = {1, 0, 4, 4};
    move_on_level(&level, &movable, -10, 0);
    CLOVE_FLOAT_EQ(movable.x, 0);
}

CLOVE_TEST(MovableFixPositionY)
{
    level_t level;
    int32_t map[] = {0, 0, 0, 0};
    level_init(&level, 4, 4, 8, map);
    movable_t movable = {1, 0, 4, 4};
    move_on_level(&level, &movable, -10, -30);
    CLOVE_FLOAT_EQ(movable.y, 0);
}

CLOVE_TEST(MovableFixPositionWidth)
{
    level_t level;
    int32_t map[] = {0, 0, 0, 0};
    level_init(&level, 4, 4, 8, map);
    movable_t movable = {1, 0, 4, 4};
    move_on_level(&level, &movable, 50, 0);
    CLOVE_FLOAT_EQ(movable.x, 28);
}

CLOVE_TEST(MovableFixPositionHeight)
{
    level_t level;
    int32_t map[] = {0, 0, 0, 0};
    level_init(&level, 4, 4, 8, map);
    movable_t movable = {1, 0, 4, 4};
    move_on_level(&level, &movable, 0, 100);
    CLOVE_FLOAT_EQ(movable.y, 28);
}

CLOVE_SUITE(MovableSuite) {
    CLOVE_SUITE_TESTS(
        MovableFixPositionX,
        MovableFixPositionY,
        MovableFixPositionWidth,
        MovableFixPositionHeight

    );
}
