#include <nds.h>
#include "types.h"

#include "world.c"
#include "projectiles.c"
#include "monsters.c"
#include "towers.c"
#include "background.c"
#include "input.c"

#include <all_gfx.h>
#include <time.h>

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
    videoSetMode(MODE_2_2D);
    videoSetModeSub(MODE_2_2D);

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
    {
        w.random[3] = time(NULL);
        //memset(&w.towerGrid, -1, 2*16*24);
        memset(&w.monsterGrid, -1, 2*16*24);

        s16 map[16][24] = {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, 255, 255, 255, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, 255, 255, 255, 255, 255, 255, -1, -1, -1, -1, -1, -1, -1, -1, -1, 255, 255, -1, -1, -1, -1, -1, -1},
            {-1, 255, 255, 255, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 255, 255, 255, -1, -1, -1, -1, -1, -1},
            {-1, -1, 255, 255, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 255, 255, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 255, 255, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, 255, 255, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, 255, 255, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 255, 255, -1, -1},
            {-1, -1, -1, -1, -1, -1, 255, 255, 255, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 255, 255, 255, -1},
            {-1, -1, -1, -1, -1, -1, 255, 255, -1, -1, -1, -1, -1, -1, -1, -1, -1, 255, 255, 255, 255, 255, 255, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 255, 255, 255, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

        memcpy(&w.towerGrid, &map, 2*16*24);
    }

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

    {
        newBackground(&w, 3, &w.gfx[GRASS], BgType_Rotation, BgSize_R_256x256, 0, 1, MAIN_SCREEN, true);
        newBackground(&w, 3, &w.gfx[GRASS], BgType_Rotation, BgSize_R_256x256, 0, 1, SUB_SCREEN, true);

        newBackground(&w, 2, &w.gfx[HUD_BAR], BgType_Rotation, BgSize_R_256x256, 1, 3, MAIN_SCREEN, true);
        newBackground(&w, 2, &w.gfx[HUD_BAR], BgType_Rotation, BgSize_R_256x256, 1, 3, SUB_SCREEN, true);

        newBackground(&w, 0, &w.gfx[HUD], BgType_Text8bpp, BgSize_T_256x256, 2, 4, SUB_SCREEN, false);

        bgSetCenter(w.bgs[MAIN_SCREEN][3].id, 128, 96);
        bgSetScroll(w.bgs[MAIN_SCREEN][3].id, 127, 96);
        bgRotate(w.bgs[MAIN_SCREEN][3].id, 16384);
    }

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
                u8 x = t.px >> 4;
                u8 y = t.py >> 4;

                buyTower(&w, x, y, PLAYER_2);
            }
            pressed = TRUE;
        }
        else {
            pressed = FALSE;
        }

        if (pressedKeys) {
            if (pressedKeys & KEY_A) {
                buyMonster(&w, PLAYER_2);
            }
        }

        if (!w.players[PLAYER_1].health || !w.players[PLAYER_2].health) {
            PRINT("Game Over\n");
        }

        drawHUD(&w, w.players[PLAYER_2].money, w.players[PLAYER_2].health);

        if (ticker > 3282) {
            for(int i = 0; i < w.towerNumber; i++){
                w.towers[i].timer++;
            }

            if (getRandomNumber(&w) > 250) {
                buyTower(&w, (getRandomNumber(&w) % 16), (getRandomNumber(&w) % 10)+1, PLAYER_1);
            }
            if (getRandomNumber(&w) > 250) {
                buyMonster(&w, PLAYER_1);
            }

            ticker = 0;
        }

#if 0
        for (int i = 0; i < 16; i++) {
            for(int j = 0; j < 24; j++) {
                PRINT("%2d ", w.towerGrid[i][j]);
            }
            PRINT("\n");
        }
        PRINT("\n");
#endif

        bgUpdate();
        updateScreens(&w);

        dt = timerElapsed(0);

        swiWaitForVBlank();
        oamUpdate(&oamSub);
        oamUpdate(&oamMain);
    }

    return 0;
}
