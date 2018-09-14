void drawEffect(Effect s){
    oamSet(s.screen == MAIN_SCREEN ? &oamMain : &oamSub, // which display
            s.drawId, // the oam entry to set
            s.x, s.y, // x & y location
            3, // priority
            s.palId, // palette for 16 color sprite or alpha for bmp sprite
            s.size, // size
            s.color, // color type
            s.gfxPtr, // the oam gfx
            3, //affine index
            true, //double the size of rotated sprites
            false, //don't hide the sprite
            false, false, //vflip, hflip
            false //apply mosaic
          );

    //DC_FlushAll();
    if (s.screen == MAIN_SCREEN)
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE[16*s.palId], s.gfxData->palLen);
    else
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE_SUB[16*s.palId], s.gfxData->palLen);

    dmaCopy(s.gfxData->tiles + 128*s.animationFrame, s.gfxPtr, 512);
}

void deleteEffect(World *w, u8 id) {
    Effect o = w->effects[id];

    freeDrawId(w, o.screen, o.drawId);

    oamFreeGfx(o.screen == MAIN_SCREEN ? &oamMain : &oamSub, o.gfxPtr);

    w->effectNumber--;
    for (int i = id; i < w->effectNumber; i++) {
        w->effects[i] = w->effects[i+1];
    }
}

u8 newEffect(World *w, int x, int y, Screen screen, SpriteSize size, SpriteColorFormat format, gfx_t *data, u8 palId){
    sassert(w->effectNumber < EFFECT_COUNT, "Too many sprites!");

    Effect s = {0};
    s.drawId = getDrawId(w, screen);
    s.x = x;
    s.y = y;
    s.gfxPtr = oamAllocateGfx(screen == MAIN_SCREEN ? &oamMain : &oamSub, size, format);
    s.screen = screen;
    s.size = size;
    s.color = format;
    s.gfxData = data;
    s.palId = palId;
    s.animationFrame = -1;

    w->effects[w->effectNumber] = s;

    w->effectNumber++;

    return w->effectNumber-1;
}

void updateEffect(World *w, u8 i) {
    Effect *cur = &w->effects[i];
    
    if (cur->timer == 5) {
        cur->timer = 0;
        if (cur->animationFrame == 3) {
            deleteEffect(w, i);
        }
        else {
            cur->animationFrame++;
        }
    }
}
