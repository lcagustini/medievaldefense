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

    touchPosition t;
    u8 pressed = TRUE;
    while (1) {
        scanKeys();
        u16 pressedKeys = keysDown();
        touchRead(&t);

        if (t.px != 0 && t.py != 0) {
            if (!pressed) {
                if (t.px >= 37 && t.px <= 220 &&
                        t.py >= 53 && t.py <= 84) {
                    return GAMEPLAY;
                }
                if (t.px >= 37 && t.px <= 220 &&
                        t.py >= 109 && t.py <= 140) {
                    return WIFI;
                }
            }
            pressed = TRUE;
        }
        else {
            pressed = FALSE;
        }

        bgUpdate();

        swiWaitForVBlank();
    }
}
