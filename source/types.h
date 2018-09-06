#include <stdio.h>

#define WORLD_SIZE_TILES 32
#define GRID_UNIT_SIZE 16
#define WORLD_SIZE WORLD_SIZE_TILES*GRID_UNIT_SIZE
#define TRUE 1
#define FALSE 0

#define PROJECTILE_COUNT 100
#define MONSTER_COUNT 25
#define TOWER_COUNT 50

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
#define CREATE_BG_GFX(a) gfx_t (a) = {TILES(a), TILES_LEN(a), backgroundPal_sPal, backgroundPal_sPalLen, MAP(a), MAP_LEN(a)};
//#define CREATE_BG_GFX(a) gfx_t (a) = {TILES(a), TILES_LEN(a), PAL(a), PAL_LEN(a), MAP(a), MAP_LEN(a)};

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
    SUB_SCREEN,
} Screen;

typedef enum {
    PLAYER_1,
    PLAYER_2,
} Player;

typedef struct {
    u8 drawId;
    SpriteSize size;
    SpriteColorFormat color;
    u8 palId;

    u16* gfxPtr;
    gfx_t *gfxData;

    Vector pos;
    Screen screen;
    Player player;
    u8 range;
    u8 timer;
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
    Player player;
    s8 health;
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
    Player player;
    s32 speed;

    Vector dir;
} Projectile;

typedef struct {
    u8 id;
    gfx_t *data;
    u8 layer;
} Background;

typedef enum {
    GRASS,
    TOWER,
    TROLL,
    SHOT,
    HUD,
} Graphics;

typedef struct {
    Monster monsters[MONSTER_COUNT];
    u8 needsDijkstra[MONSTER_COUNT];
    u8 monsterNumber;

    Tower towers[TOWER_COUNT];
    u8 towerNumber;

    Projectile projectiles[PROJECTILE_COUNT];
    u8 projectileNumber;

    u8 random;

    gfx_t gfx[10];
    u8 freeDrawId[2][128];

    Background bgs[4];

    s16 monsterGrid[16][24];
    s16 towerGrid[16][24];
} World;
