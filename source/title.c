Gamestate runTitle() {
    World w = {0};

    {
        CREATE_BG_NS_GFX(title_screen);
        CREATE_BG_NS_GFX(title_screen_bottom);

        w.gfx[TOP_TITLE] = title_screen;
        w.gfx[BOTTOM_TITLE] = title_screen_bottom;
    }

    {
        newBackground(&w, 1, &w.gfx[TOP_TITLE], BgType_Text8bpp, BgSize_T_256x256, 0, 1, MAIN_SCREEN, true);
        newBackground(&w, 1, &w.gfx[BOTTOM_TITLE], BgType_Text8bpp, BgSize_T_256x256, 0, 1, SUB_SCREEN, true);
    }

    while (1) {
        scanKeys();
        u16 pressedKeys = keysDown();

        if (pressedKeys & KEY_START) {
            return GAMEPLAY;
        }

        bgUpdate();

        swiWaitForVBlank();
        oamUpdate(&oamSub);
        oamUpdate(&oamMain);
    }
}
