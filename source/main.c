#include <nds.h>
#include "types.h"

#include "world.c"
#include "projectiles.c"
#include "monsters.c"
#include "towers.c"
#include "background.c"

#include <teste.h>
#include <tower.h>
#include <troll.h>
#include <shot.h>

void updateScreens(World *w){
    oamClear(&oamMain, 0, 0);
    oamClear(&oamSub, 0, 0);

    for(int i = 0; i < w->monsterNumber; i++){
        updateMonster(w->monsters[i]);
    }

    for(int i = 0; i < w->towerNumber; i++){
        updateTower(w->towers[i]);
    }

    for(int i = 0; i < w->projectileNumber; i++){
        updateProjectile(w->projectiles[i]);
    }
}

void setUpScreens(){
    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
    vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
    vramSetBankC(VRAM_C_SUB_BG_0x06200000);
    vramSetBankD(VRAM_D_SUB_SPRITE);
    vramSetBankE(VRAM_E_BG_EXT_PALETTE);
    vramSetBankF(VRAM_F_LCD);
    vramSetBankG(VRAM_G_SPRITE_EXT_PALETTE);
    vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
    vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);

    oamInit(&oamMain, SpriteMapping_1D_128, true);
    oamInit(&oamSub, SpriteMapping_1D_128, true);
}

int main(void){
    powerOn(POWER_ALL);

    consoleDebugInit(DebugDevice_NOCASH);

    setUpScreens();

    World w = {0};
    memset(&w.towerGrid, -1, 2*16*24);
    memset(&w.monsterGrid, -1, 2*16*24);

    CREATE_BG_GFX(teste);
    newBackground(&w, 1, &teste, BgType_Text4bpp, BgSize_T_256x256, 1, 1, MAIN_SCREEN);
    newBackground(&w, 2, &teste, BgType_Text4bpp, BgSize_T_256x256, 1, 1, SUB_SCREEN);

    CREATE_OBJECT_GFX(tower);
    CREATE_OBJECT_GFX(troll);
    CREATE_OBJECT_GFX(shot);

    timerStart(0, ClockDivider_1024, 0, NULL);

    u16 pressedKeys;
    u16 heldKeys;
    touchPosition t;

    u16 dt = 0;
    u16 secondTimer = 0;
    u8 pressed = FALSE;
    u8 needsDijkstra[MONSTER_COUNT] = {0};
    while(1){
        scanKeys();
        pressedKeys = keysDown();
        heldKeys = keysHeld();

        touchRead(&t);

        secondTimer += dt;

        if (t.z1 != 0 && t.z2 != 0) {
            if (!pressed) {
                u8 x = (t.px >> 4) << 4;
                u8 y = (t.py >> 4) << 4;

                if (y != 0 && w.towerGrid[x >> 4][(y >> 4) + 12] == -1) {
                    Tower o = {0};
                    o.size = SpriteSize_16x16;
                    o.color = SpriteColorFormat_16Color;
                    o.palId = 0;

                    o.gfxData = &tower;

                    o.pos.x = inttof32(x);
                    o.pos.y = inttof32(y);
                    o.screen = SUB_SCREEN;
                    o.range = 2;
                    newTower(&w, o);

                    for (int i = 0; i < w.monsterNumber; i++) {
                        needsDijkstra[i] = TRUE;
                    }
                }
            }
            pressed = TRUE;
        }
        else {
            pressed = FALSE;
        }

        if (pressedKeys) {
            if (pressedKeys & KEY_A) {
                Monster o = {0};
                o.size = SpriteSize_16x16;
                o.color = SpriteColorFormat_16Color;
                o.palId = 1;

                o.gfxData = &troll;

                o.pos.x = inttof32(0);
                o.pos.y = inttof32(0);
                o.screen = MAIN_SCREEN;
                o.speed = 1 << 11;
                newMonster(&w, o);
            }

            if (pressedKeys & KEY_B) {
                for (int i = 0; i < w.monsterNumber; i++) {
                    PRINT("id %d -> path=%p\n", i, w.monsters[i].path);
                }
                PRINT("\n");
            }
        }

#if 0
        PRINT("\n");
        for (int j = 0; j < 24; j++) {
            for (int i = 0; i < 16; i++) {
                PRINT("%d ", w.grid[i][j]);
            }
            PRINT("\n");
        }
        PRINT("\n");
#endif

        for (int i = 0; i < w.monsterNumber; i++) {
            Monster *cur = &w.monsters[i];

            u8 x0 = GRID_XPOS(cur->path[cur->cur_path_index]);
            u8 y0 = GRID_YPOS(cur->path[cur->cur_path_index]);

            u8 x = GRID_XPOS(cur->path[cur->cur_path_index +1]);
            u8 y = GRID_YPOS(cur->path[cur->cur_path_index +1]);

            s8 dx = x - x0;
            s8 dy = y - y0;

            if (dx) {
                sassert(dx == -1 || dx == 1, "Invalid path");
                cur->pos.x += mulf32(cur->speed, inttof32(dx));
            }
            if (dy) {
                sassert(dy == -1 || dy == 1, "Invalid path");
                cur->pos.y += mulf32(cur->speed, inttof32(dy));
            }

            if (f32toint(cur->pos.y) % 16 == 0 && f32toint(cur->pos.x) % 16 == 0 &&
                    f32togrid(cur->pos.y) + (cur->screen == MAIN_SCREEN ? 0 : 12) == y && f32togrid(cur->pos.x) == x) {
                cur->cur_path_index++;

                if (w.monsterGrid[x0][y0] == i) w.monsterGrid[x0][y0] = -1;
                w.monsterGrid[x][y] = i;

                // TESTCODE: currently looping when monster gets to bottom
                if (cur->cur_path_index >= cur->path_size -1) {
                    deleteMonster(&w, i);

#if 0
                    Object o = {0};
                    o.pos.x = inttof32(0);
                    o.pos.y = inttof32(0);
                    o.screen = MAIN_SCREEN;
                    o.size = SpriteSize_16x16;
                    o.color = SpriteColorFormat_16Color;
                    o.speed = 1 << 11;
                    o.gfxData = &troll;
                    o.palId = 1;
                    newObject(&w, o);
#endif
                }

                if (dy == 1 && y == 12) {
                    switchMonsterScreen(&w, i);
                }

                if (needsDijkstra[i]) {
                    dijkstra(&w, i);
                    needsDijkstra[i] = FALSE;
                }
            }
        }

        for (int i = 0; i < w.towerNumber; i++) {
            Tower *cur = &w.towers[i];

            if (secondTimer > 32820) {
                s16 candidate = -1;
                u8 candidate_path_size = 255;
                u8 grid_x = f32togrid(cur->pos.x);
                u8 grid_y = f32togrid(cur->pos.y) + (cur->screen == MAIN_SCREEN ? 0 : 12);
                for (int j = -cur->range; j <= cur->range; j++) {
                    for (int k = -cur->range; k <= cur->range; k++) {
                        s8 test_candidate_x = grid_x + j;
                        s8 test_candidate_y = grid_y + k;
                        if (test_candidate_x >= 0 && test_candidate_y >= 12 && test_candidate_x < 16 && test_candidate_y < 24) {
                            u8 index;
                            if ((index = w.monsterGrid[test_candidate_x][test_candidate_y]) != -1) {
                                Monster monster = w.monsters[index];
                                if (monster.speed) { // actually is a monster
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
                    if (w.monsters[candidate].screen == SUB_SCREEN) {
                        newProjectile(&w, f32toint(cur->pos.x) + 4, f32toint(cur->pos.y) + 4, candidate, 5 << 12, SUB_SCREEN, SpriteSize_8x8, SpriteColorFormat_16Color, &shot, 2);
                    }
                }
            }
        }

        for (int i = 0; i < w.projectileNumber; i++) {
            Projectile *cur = &w.projectiles[i];

            cur->pos.y += mulf32(cur->speed, cur->dir.y);
            cur->pos.x += mulf32(cur->speed, cur->dir.x);

            if (f32toint(cur->pos.y) < 0 ||
                    f32toint(cur->pos.x) < 0 ||
                    f32toint(cur->pos.y) > 192 ||
                    f32toint(cur->pos.x) > 256) {
                deleteProjectile(&w, i);
            }
        }

        if (secondTimer > 32820) {
            secondTimer = 0;
        }

        bgUpdate();
        updateScreens(&w);

        dt = timerElapsed(0);

        swiWaitForVBlank();
        oamUpdate(&oamSub);
        oamUpdate(&oamMain);
    }

    return 0;
}
