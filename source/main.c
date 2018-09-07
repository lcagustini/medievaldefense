#include <nds.h>
#include "types.h"

#include "world.c"
#include "projectiles.c"
#include "monsters.c"
#include "towers.c"
#include "background.c"

#include <all_gfx.h>

void updateScreens(World *w){
    oamClear(&oamMain, 0, 0);
    oamClear(&oamSub, 0, 0);

    for(int i = 0; i < w->monsterNumber; i++){
        updateMonster(w, i);
        drawMonster(w->monsters[i]);
    }

    for(int i = 0; i < w->towerNumber; i++){
        updateTower(w, i);
        drawTower(w->towers[i]);
    }

    for(int i = 0; i < w->projectileNumber; i++){
        updateProjectile(w, i);
        drawProjectile(w->projectiles[i]);
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
    w.random = 128;

    {
        CREATE_BG_GFX(teste);
        CREATE_BG_GFX(hud);
        CREATE_BG_GFX(hud_bar);

        CREATE_OBJECT_GFX(tower);
        CREATE_OBJECT_GFX(troll);
        CREATE_OBJECT_GFX(shot);

        w.gfx[GRASS] = teste;
        w.gfx[TOWER] = tower;
        w.gfx[TROLL] = troll;
        w.gfx[SHOT] = shot;
        w.gfx[HUD] = hud;
        w.gfx[HUD_BAR] = hud_bar;
    }

    newBackground(&w, 2, &w.gfx[GRASS], BgType_Text8bpp, BgSize_T_256x256, 3, 0, MAIN_SCREEN, true);
    newBackground(&w, 2, &w.gfx[GRASS], BgType_Text8bpp, BgSize_T_256x256, 3, 0, SUB_SCREEN, true);

    newBackground(&w, 1, &w.gfx[HUD_BAR], BgType_Text8bpp, BgSize_T_256x256, 2, 2, MAIN_SCREEN, true);
    newBackground(&w, 1, &w.gfx[HUD_BAR], BgType_Text8bpp, BgSize_T_256x256, 2, 2, SUB_SCREEN, true);

    newBackground(&w, 0, &w.gfx[HUD], BgType_Text8bpp, BgSize_T_256x256, 1, 1, SUB_SCREEN, false);

    {
        w.players[PLAYER_1].money = 10;
        w.players[PLAYER_1].health = 20;

        w.players[PLAYER_2].money = 10;
        w.players[PLAYER_2].health = 20;
    }

    timerStart(0, ClockDivider_1024, 0, NULL);

    u16 pressedKeys;
    u16 heldKeys;
    touchPosition t;

    u16 dt = 0;
    u16 ticker = 0;

    u8 pressed = FALSE;
    while(1){
        scanKeys();
        pressedKeys = keysDown();
        heldKeys = keysHeld();

        touchRead(&t);

        ticker += dt;

        if (t.px != 0 && t.py != 0) {
            if (!pressed) {
                u8 x = (t.px >> 4) << 4;
                u8 y = (t.py >> 4) << 4;

                if (y != 0 && (y >> 4) != 11 && w.towerGrid[x >> 4][(y >> 4) + 12] == -1) {
                    if (w.players[PLAYER_2].money) {
                        w.players[PLAYER_2].money--;

                        Tower o = {0};
                        o.size = SpriteSize_16x16;
                        o.color = SpriteColorFormat_16Color;
                        o.palId = 0;

                        o.gfxData = &w.gfx[TOWER];

                        o.pos.x = inttof32(x);
                        o.pos.y = inttof32(y);
                        o.screen = SUB_SCREEN;
                        o.player = PLAYER_2;
                        o.range = 2;
                        newTower(&w, o);

                        for (int i = 0; i < w.monsterNumber; i++) {
                            w.needsDijkstra[i] = TRUE;
                        }
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

                o.gfxData = &w.gfx[TROLL];

                o.pos.x = inttof32((getRandomNumber(&w) % 16) << 4);
                o.pos.y = inttof32(0);
                o.screen = MAIN_SCREEN;
                o.player = PLAYER_1;
                o.health = 5;
                o.speed = 1 << 11;
                newMonster(&w, o);
            }

            if (pressedKeys & KEY_B) {
                if (w.players[PLAYER_2].money) {
                    w.players[PLAYER_2].money--;

                    Monster o = {0};
                    o.size = SpriteSize_16x16;
                    o.color = SpriteColorFormat_16Color;
                    o.palId = 1;

                    o.gfxData = &w.gfx[TROLL];

                    o.pos.x = inttof32((getRandomNumber(&w) % 16) << 4);
                    o.pos.y = inttof32(176);
                    o.screen = SUB_SCREEN;
                    o.player = PLAYER_2;
                    o.health = 5;
                    o.speed = 1 << 11;
                    newMonster(&w, o);
                }
            }
        }

        drawHUD(&w, w.players[PLAYER_2].money, w.players[PLAYER_2].health);

        if (ticker > 3282) {
            for(int i = 0; i < w.towerNumber; i++){
                w.towers[i].timer++;
            }
            ticker = 0;
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
