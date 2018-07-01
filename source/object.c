#include "object.h"

int detectWalkable(World *w, int x, int  y){
    for(int i = 0; i < w->objectNumber; i++){
        Object obj = *(w->objects[i]);
        if(obj.x == x && obj.y == y)
            return FALSE;
    }
    if(w->grid[y/GRID_UNIT_SIZE][x/GRID_UNIT_SIZE])
        return FALSE;
    return TRUE;
}

// input is a bitfield of keys
void walk(World *w, Object *s, u16 input) {
    //iprintf("x: %d y: %d\n", s->x, s->y);
    if(!s->walking){
        if(KEY_DOWN & input){
            if(detectWalkable(w, s->x, s->y + GRID_UNIT_SIZE)){
                s->walking = TRUE;
            }
            s->direction = DIR_DOWN;
        }
        else if(KEY_UP & input){
            if(detectWalkable(w, s->x, s->y - GRID_UNIT_SIZE)){
                s->walking = TRUE;
            }
            s->direction = DIR_UP;
        }
        else if(KEY_LEFT & input){
            if(detectWalkable(w, s->x - GRID_UNIT_SIZE, s->y)){
                s->walking = TRUE;
            }
            s->direction = DIR_LEFT;
        }
        else if(KEY_RIGHT & input){
            if(detectWalkable(w, s->x + GRID_UNIT_SIZE, s->y)){
                s->walking = TRUE;
            }
            s->direction = DIR_RIGHT;
        }
    }

    if(s->walking){
        s->walked += s->speed;
        switch(s->direction){
            case DIR_UP:
                s->y -= s->speed;
                if (s->walked > 16) {
                    s->y += s->walked - 16;
                }
                break;
            case DIR_DOWN:
                s->y += s->speed;
                if (s->walked > 16) {
                    s->y -= s->walked - 16;
                }
                break;
            case DIR_LEFT:
                s->x -= s->speed;
                if (s->walked > 16) {
                    s->x += s->walked - 16;
                }
                break;
            case DIR_RIGHT:
                s->x += s->speed;
                if (s->walked > 16) {
                    s->x -= s->walked - 16;
                }
                break;
            default:
                sassert(0, "Error walking");
                break;
        }
        if(s->walked >= 16){
            s->walked = 0;
            s->walking = FALSE;
        }
    }
}

void updateObject(Object s){
    bool hflip = false;
    if(s.direction == DIR_RIGHT){
        hflip = true;
        s.direction = DIR_LEFT;
    }

    int x, y;
    if(s.x <= 112)
        x = s.x +8;
    else if(s.x >= 384)
        x = s.x -264;
    else
        x = 120;

    if(s.y <= 80)
        y = s.y;
    else if(s.y >= 416)
        y = s.y -336;
    else
        y = 80;

    oamSet(s.screen, // which display
           s.priority, // the oam entry to set
           x, y, // x & y location
           1, // priority
           s.id, // palette for 16 color sprite or alpha for bmp sprite
           s.size, // size
           s.color, // color type
           s.gfx, // the oam gfx
           -1, //affine index
           true, //double the size of rotated sprites
           false, //don't hide the sprite
           hflip, false, //vflip, hflip
           false //apply mosaic
          );
    DC_FlushAll();
    dmaCopy(s.gfxData->pal, &SPRITE_PALETTE[16*s.id], s.gfxData->palLen);
    if(s.size == SpriteSize_32x32)
        dmaCopy(s.gfxData->tiles + s.direction*16*8, s.gfx, 512);
    else if(s.size == SpriteSize_16x32)
        dmaCopy(s.gfxData->tiles + s.direction*8*8, s.gfx, 256);
}

void updateScreens(World *w){
    Object *levels[12][16] = {0};
    for(int i = 0; i < w->objectNumber; i++) {
        int y = w->objects[i]->y - w->camera_y;
        int x = w->objects[i]->x - w->camera_x;

        // if sprite is out of screen, set its priority to 3
        if (y >= 192 || y < 0)
        {
            w->objects[i]->priority = 3;
            continue;
        }

        // otherwise, store its position on the screen
        u8 level = y/GRID_UNIT_SIZE;
        for(int j = 0; j < 16; j++) {
            if(!levels[level][j]) {
                levels[level][j] = w->objects[i];
                break;
            }
        }
    }

    // set right priority for every sprite on the screen
    u8 c = 127;
    for(int i = 0; i < 12; i++) {
        for (int j = 0; j < 16; j++) {
            if (!levels[i][j]) break;
            levels[i][j]->priority = c--;
        }
    }

    oamClear(&oamMain, 0, 0);
    oamClear(&oamSub, 0, 0);
    for(int i = 0; i < w->objectNumber; i++){
        updateObject(*(w->objects[i]));
    }
}

Object *newObject(World *w, int x, int y, u8 speed, OamState* screen, SpriteSize size, SpriteColorFormat format, gfx_t *data){
    Object *s = malloc(sizeof(Object));
    if(w->objectNumber <= SPRITE_COUNT){
        s->id = w->objectNumber;
        s->x = x;
        s->y = y;
        s->gfx = oamAllocateGfx(screen, size, format);
        s->screen = screen;
        s->size = size;
        s->color = format;
        s->walking = FALSE;
        s->direction = DIR_DOWN;
        s->walked = 0;
        s->speed = speed;
        s->priority = 0;
        s->gfxData = data;
        w->objectNumber++;

        w->objects[s->id] = s;
    }
    return s;
}

