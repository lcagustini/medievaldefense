void drawProjectile(Projectile s){
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

    //DC_FlushAll();
    if (s.screen == MAIN_SCREEN)
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE[16*s.palId], s.gfxData->palLen);
    else
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE_SUB[16*s.palId], s.gfxData->palLen);

    dmaCopy(s.gfxData->tiles, s.gfxPtr, 128);
}

void deleteProjectile(World *w, u8 id) {
    Projectile o = w->projectiles[id];

    freeDrawId(w, o.screen, o.drawId);

    oamFreeGfx(o.screen == MAIN_SCREEN ? &oamMain : &oamSub, o.gfxPtr);

    w->projectileNumber--;
    for (int i = id; i < w->projectileNumber; i++) {
        w->projectiles[i] = w->projectiles[i+1];
    }
}

u8 newProjectile(World *w, int x, int y, u8 obj, s32 speed, Screen screen, SpriteSize size, SpriteColorFormat format, gfx_t *data, u8 palId){
    sassert(w->projectileNumber < PROJECTILE_COUNT, "Too many sprites!");

    Projectile s = {0};
    s.drawId = getDrawId(w, screen);
    s.pos.x = inttof32(x);
    s.pos.y = inttof32(y);
    s.gfxPtr = oamAllocateGfx(screen == MAIN_SCREEN ? &oamMain : &oamSub, size, format);
    s.player = w->monsters[obj].player == PLAYER_1 ? PLAYER_2 : PLAYER_1;
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

    w->projectiles[w->projectileNumber] = s;

    w->projectileNumber++;

    return w->projectileNumber-1;
}

void updateProjectile(World *w, u8 i) {
    Projectile *cur = &w->projectiles[i];

    cur->pos.y += mulf32(cur->speed, cur->dir.y);
    cur->pos.x += mulf32(cur->speed, cur->dir.x);

    s16 index = w->monsterGrid[f32togrid(cur->pos.x)][f32togrid(cur->pos.y)+12];
    if (index != -1) {
        if (cur->player != w->monsters[index].player) {
            w->monsters[index].health--;
            deleteProjectile(w, i);
        }
    }
    else if (f32toint(cur->pos.y) < 0 ||
            f32toint(cur->pos.x) < 0 ||
            f32toint(cur->pos.y) > 192 ||
            f32toint(cur->pos.x) > 256) {
        deleteProjectile(w, i);
    }
}
