#ifndef TYPES
#define TYPES

#include <stdio.h>

#define WORLD_SIZE_TILES 32
#define GRID_UNIT_SIZE 16
#define WORLD_SIZE WORLD_SIZE_TILES*GRID_UNIT_SIZE
#define TRUE 1
#define FALSE 0

#define TILES(a) a##Tiles
#define TILES_LEN(a) a##TilesLen
#define PAL(a) a##Pal
#define PAL_LEN(a) a##PalLen
#define MAP(a) a##Map
#define MAP_LEN(a) a##MapLen
#define CREATE_OBJECT_GFX(a) gfx_t (a) = {TILES(a), TILES_LEN(a), PAL(a), PAL_LEN(a)};
#define CREATE_BG_GFX(a) gfx_t (a) = {TILES(a), TILES_LEN(a), PAL(a), PAL_LEN(a), MAP(a), MAP_LEN(a)};

enum Directions{DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT};

typedef struct {
    u16 id;
    u16 value;
} bin_heap_elem_t;

typedef struct {
    u16 max_size;
    u16 size;
    bin_heap_elem_t *data;
} bin_heap_t;

typedef struct
{
    const uint *tiles;
    u32 tilesLen;
    const u16 *pal;
    u32 palLen;
    const u16 *map;
    u32 mapLen;
} gfx_t;

typedef struct{
    u8 id;
    u16 x, y;
    u16* gfx;
    u8 walking;
    u8 direction;
    u8 walked;
    u8 speed;
    OamState* screen;
    SpriteSize size;
    SpriteColorFormat color;
    gfx_t *gfxData;
    u8 priority;
    u8 palId;
    u16 *path;
    u16 cur_path_index;
} Object;

typedef struct{
    int id;
    gfx_t *data;
    u8 layer;
} Background;

typedef struct{
    Object objects[100];
    Background bgs[4];
    u8 objectNumber;
    s16 grid[16][24];
    int camera_x;
    int camera_y;
} World;

typedef enum{
    MAIN_SCREEN,
    SUB_SCREEN
} Screen;

#endif
