#include <nds.h>
#include <time.h>

#include <all_gfx.h>
#include "types.h"

#include "world.c"
#include "projectiles.c"
#include "towers.c"
#include "monsters.c"
#include "background.c"
#include "input.c"

#include "gameplay.c"
#include "title.c"

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

    oamInit(&oamMain, SpriteMapping_1D_128, false);
    oamInit(&oamSub, SpriteMapping_1D_128, false);
}

int main(void){
    powerOn(POWER_ALL);

    consoleDebugInit(DebugDevice_NOCASH);

    setUpScreens();

    Gamestate gamestate = TITLE_SCREEN;

    while (1) {
        setUpScreens();

        switch (gamestate) {
            case TITLE_SCREEN:
                PRINT("Going to Title Screen\n");
                gamestate = runTitle();
                break;
            case GAMEPLAY:
                PRINT("Going to Gameplay\n");
                gamestate = runGame();
                break;
        }
    }

    return 0;
}
