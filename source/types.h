#include <stdio.h>

#define WORLD_SIZE_TILES 32
#define GRID_UNIT_SIZE 16
#define WORLD_SIZE WORLD_SIZE_TILES*GRID_UNIT_SIZE
#define TRUE 1
#define FALSE 0

#define PROJECTILE_COUNT 100
#define MONSTER_COUNT 25
#define TOWER_COUNT 25

#define GRID_POS(x, y) (((y) << 4) + (x))
#define GRID_XPOS(coord) ((coord) % 16)
#define GRID_YPOS(coord) ((coord) >> 4)

#define MAX_PATH_BIN_HEAP_SIZE 400

#define PRINT(...) fprintf(stderr, __VA_ARGS__)
#define f32togrid(a) ((f32toint(a)) >> (4))

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

typedef struct {
    const uint *tiles;
    u32 tilesLen;
    const u16 *pal;
    u32 palLen;
    const u16 *map;
    u32 mapLen;
} gfx_t;

typedef struct {
    s32 x;
    s32 y;
} Vector;

typedef enum {
    MAIN_SCREEN,
    SUB_SCREEN
} Screen;

typedef struct {
    u8 drawId;
    SpriteSize size;
    SpriteColorFormat color;
    u8 palId;

    u16* gfxPtr;
    gfx_t *gfxData;

    Vector pos;
    Screen screen;
    u8 range;
} Tower;

typedef struct {
    u8 drawId;
    SpriteSize size;
    SpriteColorFormat color;
    u8 palId;

    u16* gfxPtr;
    gfx_t *gfxData;

    Vector pos;
    Screen screen;
    s32 speed;

    u16 *path;
    u16 cur_path_index;
    u16 path_size;
} Monster;

typedef struct {
    u8 drawId;
    SpriteSize size;
    SpriteColorFormat color;
    u8 palId;

    u16* gfxPtr;
    gfx_t *gfxData;

    Vector pos;
    Screen screen;
    s32 speed;

    Vector dir;
} Projectile;

typedef struct {
    int id;
    gfx_t *data;
    u8 layer;
} Background;

typedef struct {
    Monster monsters[MONSTER_COUNT];
    u8 monsterNumber;

    Tower towers[TOWER_COUNT];
    u8 towerNumber;

    Projectile projectile[PROJECTILE_COUNT];
    u8 projectileNumber;

    Background bgs[4];
    u8 freeDrawId[2][128];
    s16 grid[16][24];
} World;
