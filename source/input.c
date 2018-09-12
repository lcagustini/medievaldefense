void buyTower(World *w, u8 x, u8 y, Team team) {
    if (y != 0 && y != 11 && y != 12 && y != 23) {
        Screen s = team == PLAYER_2 ? SUB_SCREEN : MAIN_SCREEN;
        if (w->players[team].money && w->towerGrid[x][y + (s == MAIN_SCREEN ? 0 : 12)] == -1) {
            Tower o = {0};
            o.size = SpriteSize_16x16;
            o.color = SpriteColorFormat_16Color;
            o.palId = 0;

            o.gfxData = &w->gfx[TOWER];

            o.pos.x = inttof32(x << 4);
            o.pos.y = inttof32(y << 4);
            o.screen = s;
            o.player = team;
            o.range = 2;
            u8 id = newTower(w, o);

            if (dijkstra(w, 0, TRUE)) {
                w->players[team].money--;
            }
            else {
                deleteTower(w, id);
            }

            for (int i = 0; i < w->monsterNumber; i++) {
                w->needsDijkstra[i] = TRUE;
            }
        }
    }
}

void buyMonster(World *w, Team team, MonsterTypes type) {
    Screen s = team == PLAYER_2 ? SUB_SCREEN : MAIN_SCREEN;

    Monster o = {0};
    o.size = SpriteSize_16x16;
    o.color = SpriteColorFormat_16Color;
    o.palId = type == TANK ? 1 : 2;

    o.gfxData = type == TANK ? &w->gfx[TROLL_RED] : &w->gfx[TROLL_BLUE];

    o.pos.x = inttof32((getRandomNumber(w) % 16) << 4);
    o.pos.y = inttof32(s == MAIN_SCREEN ? 0 : 176);
    o.screen = s;
    o.player = team;
    o.health = type == TANK ? 5 : 3;
    o.speed = type == TANK ? 1 << 11 : 3 << 10;

    o.cost = 2;
    o.reward = 3;

    if (w->players[team].money >= o.cost) {
        w->players[team].money -= o.cost;

        newMonster(w, o);
    }
}
