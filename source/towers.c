void drawTower(Tower s){
    oamSet(s.screen == MAIN_SCREEN ? &oamMain : &oamSub, // which display
            s.drawId, // the oam entry to set
            f32toint(s.pos.x), f32toint(s.pos.y), // x & y location
            2, // priority
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

void deleteTower(World *w, u8 id) {
    Tower o = w->towers[id];

    freeDrawId(w, o.screen, o.drawId);

    oamFreeGfx(o.screen == MAIN_SCREEN ? &oamMain : &oamSub, o.gfxPtr);

    w->towerNumber--;
    for (int i = id; i < w->towerNumber; i++) {
        w->towers[i] = w->towers[i+1];
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (w->towerGrid[i][j] == id) {
                w->towerGrid[i][j] = -1;
            }
            else if (w->towerGrid[i][j] > id) {
                w->towerGrid[i][j]--;
            }
        }
    }
}

u8 newTower(World *w, Tower s){
    sassert(w->towerNumber < TOWER_COUNT, "Too many sprites!");
    // TODO: assert all fields are being filled correctly (whenever possible)
    /*
    s.pos.x = inttof32(x);
    s.pos.y = inttof32(y);
    s.screen = screen;
    s.size = size;
    s.color = format;
    s.speed = speed;
    s.gfxData = data;
    s.palId = palId;
    */

    s.drawId = getDrawId(w, s.screen);
    s.gfxPtr = oamAllocateGfx(s.screen == MAIN_SCREEN ? &oamMain : &oamSub, s.size, s.color);

    w->towers[w->towerNumber] = s;

    if (s.screen == MAIN_SCREEN) {
        w->towerGrid[f32togrid(s.pos.x)][f32togrid(s.pos.y)] = w->towerNumber;
    } else {
        w->towerGrid[f32togrid(s.pos.x)][f32togrid(s.pos.y) + 12] = w->towerNumber;
    }

    w->towerNumber++;

    return w->towerNumber-1;
}

void updateTower(World *w, u8 i) {
    Tower *cur = &w->towers[i];

    if (cur->timer == 10) {
        s16 candidate = -1;
        u8 candidate_path_size = 255;
        u8 grid_x = f32togrid(cur->pos.x);
        u8 grid_y = f32togrid(cur->pos.y) + (cur->screen == MAIN_SCREEN ? 0 : 12);
        for (int j = -cur->range; j <= cur->range; j++) {
            for (int k = -cur->range; k <= cur->range; k++) {
                s8 test_candidate_x = grid_x + j;
                s8 test_candidate_y = grid_y + k;
                if (test_candidate_x >= 0 && test_candidate_y >= 12 && test_candidate_x < 16 && test_candidate_y < 24) {
                    s16 index = w->monsterGrid[test_candidate_x][test_candidate_y];
                    if (index != -1) {
                        Monster monster = w->monsters[index];
                        if (monster.player != cur->player) {
                            if (candidate == -1) {
                                candidate = index;
                                candidate_path_size = monster.path_size - monster.cur_path_index;
                            } else {
                                if (candidate_path_size > monster.path_size - monster.cur_path_index) {
                                    candidate = index;
                                    candidate_path_size = monster.path_size - monster.cur_path_index;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (candidate != -1) { // has a target in range
            if (w->monsters[candidate].screen == SUB_SCREEN) {
                newProjectile(w, f32toint(cur->pos.x) + 4, f32toint(cur->pos.y) + 4, candidate, 5 << 12, SUB_SCREEN, SpriteSize_8x8, SpriteColorFormat_16Color, &w->gfx[SHOT], 2);
            }
        }

        cur->timer = 0;
    }
}
