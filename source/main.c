#ifndef NDS
#define NDS
#include <nds.h>
#include "types.h"
#endif

#include <stdio.h>

#include "object.h"
#include "background.h"

#include <teste.h>

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
}

int main(void){
    u16 Pressed;
    u16 Held;

    powerOn(POWER_ALL);

    consoleDebugInit(DebugDevice_NOCASH);
    
    setUpScreens();

    World w = {0};

    CREATE_BG_GFX(teste);
    newBackground(&w, 1, &teste, BgType_Text4bpp, BgSize_T_512x512, 1, 1, MAIN_SCREEN);
    newBackground(&w, 2, &teste, BgType_Text4bpp, BgSize_T_512x512, 1, 1, SUB_SCREEN);

    timerStart(0, ClockDivider_1024, 0, NULL);

    touchPosition* t = (touchPosition*) malloc(sizeof(touchPosition*));
    u16 dt;
    while(1){
        //fprintf(stderr, "debug message in no$gba window\n");

        scanKeys();
        touchRead(t);

        Pressed = keysDown();
        Held = keysHeld();
        dt = timerElapsed(0);

        bgUpdate();

        swiWaitForVBlank();
        oamUpdate(&oamSub);
        oamUpdate(&oamMain);
    }

    return 0;
}
