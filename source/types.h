#include <stdio.h>

#define WORLD_SIZE_TILES 32
#define GRID_UNIT_SIZE 16
#define WORLD_SIZE WORLD_SIZE_TILES*GRID_UNIT_SIZE
#define TRUE 1
#define FALSE 0

#define PROJECTILE_COUNT 100
#define MONSTER_COUNT 50
#define TOWER_COUNT 50
#define EFFECT_COUNT 16

#define GRID_POS(x, y) (((y) << 4) + (x))
#define GRID_XPOS(coord) ((coord) % 16)
#define GRID_YPOS(coord) ((coord) >> 4)

#define MAX_PATH_BIN_HEAP_SIZE 400

#define PRINT(...) fprintf(stderr, __VA_ARGS__)
#define f32togrid(a) ((f32toint(a)) >> (4))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define TILES(a) a##Tiles
#define TILES_LEN(a) a##TilesLen
#define PAL(a) a##Pal
#define PAL_LEN(a) a##PalLen
#define MAP(a) a##Map
#define MAP_LEN(a) a##MapLen

#define CREATE_OBJECT_GFX(a) gfx_t (a) = {TILES(a), TILES_LEN(a), PAL(a), PAL_LEN(a)};
#define CREATE_BG_GFX(a) gfx_t (a) = {TILES(a), TILES_LEN(a), backgroundPal_sPal, backgroundPal_sPalLen, MAP(a), MAP_LEN(a)};
#define CREATE_BG_NS_GFX(a) gfx_t (a) = {TILES(a), TILES_LEN(a), PAL(a), PAL_LEN(a), MAP(a), MAP_LEN(a)};

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
} Team;

typedef enum {
    SMALL,
    BIG,
} TowerType;

typedef struct {
    u8 drawId;
    SpriteSize size;
    SpriteColorFormat color;
    u8 palId;

    u16* gfxPtr;
    gfx_t *gfxData;

    Vector pos;
    Screen screen;
    Team player;

    TowerType type;
    u8 damage;
    u8 range;

    u8 animationFrame;
    u8 timer;
} Tower;

typedef enum {
    TANK,
    SCOUT,
    KAMIKAZE,
} MonsterType;

typedef enum {
    UP,
    LEFT,
    DOWN,
    RIGHT,
} Direction;

typedef struct {
    u8 drawId;
    SpriteSize size;
    SpriteColorFormat color;
    u8 palId;

    u16* gfxPtr;
    gfx_t *gfxData;

    Screen screen;
    Team player;
    s8 health;

    Vector pos;
    Direction dir;
    s32 speed;

    MonsterType type;
    u8 cost;
    u8 reward;

    u16 *path;
    u16 cur_path_index;
    u16 path_size;

    u8 animationFrame;
    u8 timer;
} Monster;

typedef struct {
    u16 money;
    u8 health;
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
    Team player;
    s32 speed;
    u8 damage;

    Vector dir;
} Projectile;

typedef struct {
    u8 drawId;
    SpriteSize size;
    SpriteColorFormat color;
    u8 palId;

    u16* gfxPtr;
    gfx_t *gfxData;

    s16 x;
    s16 y;
    Screen screen;

    u8 timer;
    u8 animationFrame;
} Effect;

typedef struct {
    u8 id;
    gfx_t *data;
    u8 layer;
} Background;

typedef enum {
    GRASS,

    TOWER,
    TOWER2,
    SHOT,

    TROLL,
    WOLF,
    BOMBER,

    HUD,
    HUD_BAR,

    TOP_TITLE,
    BOTTOM_TITLE,

    EXPLOSION,
} Graphics;

typedef struct {
    Monster monsters[MONSTER_COUNT];
    u8 needsDijkstra[MONSTER_COUNT];
    u8 monsterNumber;

    Tower towers[TOWER_COUNT];
    u8 towerNumber;

    Projectile projectiles[PROJECTILE_COUNT];
    u8 projectileNumber;

    Effect effects[EFFECT_COUNT];
    u8 effectNumber;

    //Access with enum Player
    Player players[2];

    u8 random[4];

    //Access with enum Graphics
    gfx_t gfx[20];
    //Access with enum Screen
    u8 freeDrawId[2][128];

    //Access with enum Screen
    Background bgs[2][4];

    s16 monsterGrid[16][24];
    s16 towerGrid[16][24];
} World;

typedef enum {
    TITLE_SCREEN,
    GAMEPLAY,
    WIFI,
} Gamestate;

typedef struct {
    u16 pressedKeys;
    u8 tx;
    u8 ty;
    u16 frame;
} Packet;
