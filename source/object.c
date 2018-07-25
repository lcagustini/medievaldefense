void updateObject(Object s){
    bool hflip = false;
    if(s.direction == DIR_RIGHT){
        hflip = true;
        s.direction = DIR_LEFT;
    }

    oamSet(s.screen, // which display
           s.id, // the oam entry to set
           s.x, s.y, // x & y location
           1, // priority
           s.palId, // palette for 16 color sprite or alpha for bmp sprite
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
    if(s.screen == &oamMain)
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE[16*s.palId], s.gfxData->palLen);
    else
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE_SUB[16*s.palId], s.gfxData->palLen);
    
    dmaCopy(s.gfxData->tiles, s.gfx, 128);
}

void updateScreens(World *w){
    oamClear(&oamMain, 0, 0);
    oamClear(&oamSub, 0, 0);

    //fprintf(stderr, "%d\n", w->objectNumber);
    for(int i = 0; i < w->objectNumber; i++){
        updateObject(w->objects[i]);
    }
}

u8 newObject(World *w, int x, int y, u8 speed, OamState* screen, SpriteSize size, SpriteColorFormat format, gfx_t *data, u8 palId){
    sassert(w->objectNumber < SPRITE_COUNT, "Too many sprites!");

    Object s;
    s.id = w->objectNumber;
    s.x = x;
    s.y = y;
    s.gfx = oamAllocateGfx(screen, size, format);
    s.screen = screen;
    s.size = size;
    s.color = format;
    s.walking = FALSE;
    s.direction = DIR_DOWN;
    s.walked = 0;
    s.speed = speed;
    s.priority = 0;
    s.gfxData = data;
    s.palId = palId;

    w->objectNumber++;
    w->objects[s.id] = s;
    w->grid[s.x >> 4][s.y >> 4] = s.id; 

    return s.id;
}

