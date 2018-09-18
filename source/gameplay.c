void updateScreens(World *w){
    oamClear(&oamMain, 0, 0);
    oamClear(&oamSub, 0, 0);

    for(int i = 0; i < w->effectNumber; i++){
        updateEffect(w, i);
        drawEffect(w->effects[i]);
    }

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

Gamestate runGame(int socketfd, struct sockaddr_in sain) {
    World w = {0};

    consoleDebugInit(DebugDevice_NOCASH);

    {
        w.random[3] = 128;
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
        CREATE_OBJECT_GFX(tower2);

        CREATE_OBJECT_GFX(troll);
        CREATE_OBJECT_GFX(wolf);
        CREATE_OBJECT_GFX(bomber);
        CREATE_OBJECT_GFX(shot);

        CREATE_OBJECT_GFX(explosion);

        w.gfx[GRASS] = teste;
        w.gfx[TOWER] = tower;
        w.gfx[TOWER2] = tower2;
        w.gfx[TROLL] = troll;
        w.gfx[WOLF] = wolf;
        w.gfx[BOMBER] = bomber;
        w.gfx[SHOT] = shot;
        w.gfx[HUD] = hud;
        w.gfx[HUD_BAR] = hud_bar;
        w.gfx[EXPLOSION] = explosion;
    }

    {
        newBackground(&w, 3, &w.gfx[GRASS], BgType_Rotation, BgSize_R_256x256, 0, 1, MAIN_SCREEN, true);
        newBackground(&w, 3, &w.gfx[GRASS], BgType_Rotation, BgSize_R_256x256, 0, 1, SUB_SCREEN, true);

        newBackground(&w, 2, &w.gfx[HUD_BAR], BgType_Rotation, BgSize_R_256x256, 1, 3, MAIN_SCREEN, true);
        newBackground(&w, 2, &w.gfx[HUD_BAR], BgType_Rotation, BgSize_R_256x256, 1, 3, SUB_SCREEN, true);

        newBackground(&w, 0, &w.gfx[HUD], BgType_Text8bpp, BgSize_T_256x256, 2, 4, SUB_SCREEN, false);

        bgSetCenter(w.bgs[MAIN_SCREEN][3].id, 128, 96);
        bgSetScroll(w.bgs[MAIN_SCREEN][3].id, 127, 96);
        bgRotate(w.bgs[MAIN_SCREEN][3].id, degreesToAngle(180));
    }

    {
        w.players[PLAYER_1].money = 10;
        w.players[PLAYER_1].health = 20;

        w.players[PLAYER_2].money = 10;
        w.players[PLAYER_2].health = 20;
    }

    {
        oamRotateScale(&oamMain, 0, degreesToAngle(90), intToFixed(1, 8), intToFixed(1, 8));
        oamRotateScale(&oamSub, 0, degreesToAngle(90), intToFixed(1, 8), intToFixed(1, 8));

        oamRotateScale(&oamMain, 1, degreesToAngle(180), intToFixed(1, 8), intToFixed(1, 8));
        oamRotateScale(&oamSub, 1, degreesToAngle(180), intToFixed(1, 8), intToFixed(1, 8));

        oamRotateScale(&oamMain, 2, degreesToAngle(270), intToFixed(1, 8), intToFixed(1, 8));
        oamRotateScale(&oamSub, 2, degreesToAngle(270), intToFixed(1, 8), intToFixed(1, 8));

        oamRotateScale(&oamMain, 3, degreesToAngle(0), 1 << 7, 1 << 7);
        oamRotateScale(&oamSub, 3, degreesToAngle(0), 1 << 7, 1 << 7);
    }

    timerStart(0, ClockDivider_1024, 0, NULL);

    u16 pressedKeys;
    u16 heldKeys;
    touchPosition t;

    u16 dt = 0;
    u16 ticker = 0;
    u16 frame = 0;

    while (1) {
        scanKeys();
        pressedKeys = keysDown();
        heldKeys = keysHeld();
        touchRead(&t);

        ticker += dt;

        if (pressedKeys) {
            if (socketfd != -1) {
                Packet p = {.pressedKeys = pressedKeys, .tx = t.px, .ty = t.py, .frame = frame};
                sendto(socketfd, &p, sizeof(p), 0, (struct sockaddr *) &sain, sizeof(sain));
            }

            if (pressedKeys & KEY_A) {
                buyMonster(&w, PLAYER_2, TANK);
            }
            if (pressedKeys & KEY_B) {
                buyMonster(&w, PLAYER_2, SCOUT);
            }
            if (pressedKeys & KEY_X) {
                buyMonster(&w, PLAYER_2, KAMIKAZE);
            }
            if (pressedKeys & KEY_TOUCH) {
                u8 x = t.px >> 4;
                u8 y = t.py >> 4;

                buyTower(&w, x, y, PLAYER_2);
            }
        }

        if (!w.players[PLAYER_1].health || !w.players[PLAYER_2].health) {
            PRINT("Game Over\n");
            return TITLE_SCREEN;
        }

        drawHUD(&w, w.players[PLAYER_2].money, w.players[PLAYER_2].health);

        if (socketfd != -1) {
            Packet p;
            int len = sizeof(sain);

            fd_set readfds;
            struct timeval timeout = {0};

            FD_ZERO(&readfds);
            FD_SET(socketfd, &readfds);
            u8 read = select(socketfd+1, &readfds, NULL, NULL, &timeout);

            if (read == 1) {
                u8 n = recvfrom(socketfd, &p, sizeof(p), 0, (struct sockaddr *) &sain, &len);

                if (n > 0) {
                    if (p.pressedKeys & KEY_A) {
                        buyMonster(&w, PLAYER_1, TANK);
                    }
                    if (p.pressedKeys & KEY_B) {
                        buyMonster(&w, PLAYER_1, SCOUT);
                    }
                    if (p.pressedKeys & KEY_X) {
                        buyMonster(&w, PLAYER_1, KAMIKAZE);
                    }
                    if (p.pressedKeys & KEY_TOUCH) {
                        u8 x = 15 - (p.tx >> 4);
                        u8 y = 11 - (p.ty >> 4);

                        buyTower(&w, x, y, PLAYER_1);
                    }

                    PRINT("%d %d\n", frame, p.frame);
                }
            }
        }

        if (ticker > 656) {
            for (int i = 0; i < w.towerNumber; i++) {
                w.towers[i].timer++;
            }
            for (int i = 0; i < w.monsterNumber; i++) {
                w.monsters[i].timer++;
            }
            for (int i = 0; i < w.effectNumber; i++) {
                w.effects[i].timer++;
            }

            if (socketfd == -1) {
                if (getRandomNumber(&w) > 252) {
                    buyTower(&w, (getRandomNumber(&w) % 16), (getRandomNumber(&w) % 10)+1, PLAYER_1);
                }
                if (getRandomNumber(&w) > 250) {
                    u8 rand = getRandomNumber(&w);
                    if (rand < 86) {
                        buyMonster(&w, PLAYER_1, TANK);
                    }
                    else if (rand < 171){
                        buyMonster(&w, PLAYER_1, SCOUT);
                    }
                    else {
                        buyMonster(&w, PLAYER_1, KAMIKAZE);
                    }
                }
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
        frame++;

        swiWaitForVBlank();
        oamUpdate(&oamSub);
        oamUpdate(&oamMain);
    }
}
