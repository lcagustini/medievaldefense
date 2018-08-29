void updateProjectile(Projectile s){
    oamSet(s.screen == MAIN_SCREEN ? &oamMain : &oamSub, // which display
            s.drawId, // the oam entry to set
            f32toint(s.pos.x), f32toint(s.pos.y), // x & y location
            1, // priority
            s.palId, // palette for 16 color sprite or alpha for bmp sprite
            s.size, // size
            s.color, // color type
            s.gfxPtr, // the oam gfx
            -1, //affine index
            true, //double the size of rotated sprites
            false, //don't hide the sprite
            false, false, //vflip, hflip
            false //apply mosaic
          );

    DC_FlushAll();
    if (s.screen == MAIN_SCREEN)
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE[16*s.palId], s.gfxData->palLen);
    else
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE_SUB[16*s.palId], s.gfxData->palLen);

    dmaCopy(s.gfxData->tiles, s.gfxPtr, 128);
}

void deleteProjectile(World *w, u8 id) {
    Projectile o = w->projectile[id];

    freeDrawId(w, o.screen, o.drawId);

    oamFreeGfx(o.screen == MAIN_SCREEN ? &oamMain : &oamSub, o.gfxPtr);

    w->projectileNumber--;
    for (int i = id; i < w->projectileNumber; i++) {
        w->projectile[i] = w->projectile[i+1];
    }
}

u8 newProjectile(World *w, int x, int y, u8 obj, s32 speed, Screen screen, SpriteSize size, SpriteColorFormat format, gfx_t *data, u8 palId){
    sassert(w->projectileNumber < PROJECTILE_COUNT && w->projectileNumber + w->monsterNumber + w->towerNumber < SPRITE_COUNT, "Too many sprites!");

    Projectile s = {0};
    s.drawId = getDrawId(w, screen);
    s.pos.x = inttof32(x);
    s.pos.y = inttof32(y);
    s.gfxPtr = oamAllocateGfx(screen == MAIN_SCREEN ? &oamMain : &oamSub, size, format);
    s.screen = screen;
    s.size = size;
    s.color = format;
    s.speed = speed;
    s.gfxData = data;
    s.palId = palId;

    s.dir.x = w->monsters[obj].pos.x - s.pos.x;
    s.dir.y = w->monsters[obj].pos.y - s.pos.y;

    s32 norm = sqrtf32(mulf32(s.dir.x, s.dir.x) + mulf32(s.dir.y, s.dir.y));
    sassert(norm != 0, "Invalid projectile target");

    s.dir.x = divf32(s.dir.x, norm);
    s.dir.y = divf32(s.dir.y, norm);

    w->projectile[w->projectileNumber] = s;

    w->projectileNumber++;

    return w->projectileNumber-1;
}
