#include <nds.h>
#include "types.h"

#include "object.c"
#include "background.c"

#include <teste.h>
#include <tower.h>
#include <troll.h>

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
    u16 Pressed;
    u16 Held;

    powerOn(POWER_ALL);

    consoleDebugInit(DebugDevice_NOCASH);

    setUpScreens();

    World w = {0};
    memset(&w.grid, -1, 2*16*24);

    CREATE_BG_GFX(teste);
    newBackground(&w, 1, &teste, BgType_Text4bpp, BgSize_T_256x256, 1, 1, MAIN_SCREEN);
    newBackground(&w, 2, &teste, BgType_Text4bpp, BgSize_T_256x256, 1, 1, SUB_SCREEN);

    CREATE_OBJECT_GFX(tower);
    CREATE_OBJECT_GFX(troll);
    u8 troll_id = newObject(&w, 32, 48, 0, &oamMain, SpriteSize_16x16, SpriteColorFormat_16Color, &troll, 1);

    timerStart(0, ClockDivider_1024, 0, NULL);

    

    touchPosition t;
    u16 dt;
    u8 pressed;
    while(1){
        scanKeys();
        touchRead(&t);

        if(t.z1 != 0 && t.z2 != 0) {
            if(!pressed) {
                u8 x = (t.px >> 4) << 4;
                u8 y = (t.py >> 4) << 4;

                if(w.grid[x >> 4][(y >> 4) + 12] == -1)
                    newObject(&w, x, y, 0, &oamSub, SpriteSize_16x16, SpriteColorFormat_16Color, &tower, 0);
            }
            pressed = TRUE;
        }
        else {
            pressed = FALSE;
        }



        //fprintf(stderr, "x: %d, y: %d, rx: %d, ry: %d, z1: %d, z2: %d\n", t.px, t.py, t.rawx, t.rawy, t.z1, t.z2);

        Pressed = keysDown();
        Held = keysHeld();
        dt = timerElapsed(0);

        bgUpdate();
        updateScreens(&w);

        swiWaitForVBlank();
        oamUpdate(&oamSub);
        oamUpdate(&oamMain);
    }

    return 0;
}
