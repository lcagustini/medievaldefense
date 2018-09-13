u8 dijkstra(World *world, u16 id, u8 testing);

void drawMonster(Monster s){
    oamSet(s.screen == MAIN_SCREEN ? &oamMain : &oamSub, // which display
            s.drawId, // the oam entry to set
            f32toint(s.pos.x), f32toint(s.pos.y), // x & y location
            3, // priority
            s.palId, // palette for 16 color sprite or alpha for bmp sprite
            s.size, // size
            s.color, // color type
            s.gfxPtr, // the oam gfx
            s.dir - 1, //affine index
            false, //double the size of rotated sprites
            false, //don't hide the sprite
            false, false, //vflip, hflip
            false //apply mosaic
          );

    //DC_FlushAll();
    if (s.screen == MAIN_SCREEN)
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE[16*s.palId], s.gfxData->palLen);
    else
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE_SUB[16*s.palId], s.gfxData->palLen);

    dmaCopy(s.gfxData->tiles, s.gfxPtr, 128);
}

void deleteMonster(World *w, u8 id) {
    Monster o = w->monsters[id];

    freeDrawId(w, o.screen, o.drawId);

    oamFreeGfx(o.screen == MAIN_SCREEN ? &oamMain : &oamSub, o.gfxPtr);
    free(o.path);

    w->monsterNumber--;
    for (int i = id; i < w->monsterNumber; i++) {
        w->monsters[i] = w->monsters[i+1];
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (w->monsterGrid[i][j] == id) {
                w->monsterGrid[i][j] = -1;
            }
            else if (w->monsterGrid[i][j] > id) {
                w->monsterGrid[i][j]--;
            }
        }
    }
}

u8 newMonster(World *w, Monster s){
    sassert(w->monsterNumber < MONSTER_COUNT, "Too many sprites!");
    // TODO: assert all fields are being filled correctly (whenever possible)
    /*
    s.pos.x = inttof32(x);
    s.pos.y = inttof32(y);
    s.screen = screen;
    s.size = size;
    s.color = format;
    s.speed = speed;
    s.gfxData = data;
    s.palId = palId;
    */

    s.drawId = getDrawId(w, s.screen);
    s.gfxPtr = oamAllocateGfx(s.screen == MAIN_SCREEN ? &oamMain : &oamSub, s.size, s.color);

    w->monsters[w->monsterNumber] = s;

    if (s.screen == MAIN_SCREEN) {
        w->monsterGrid[f32togrid(s.pos.x)][f32togrid(s.pos.y)] = w->monsterNumber;
    } else {
        w->monsterGrid[f32togrid(s.pos.x)][f32togrid(s.pos.y) + 12] = w->monsterNumber;
    }

    w->monsters[w->monsterNumber].path = malloc(MAX_PATH_BIN_HEAP_SIZE * sizeof(u16));
    dijkstra(w, w->monsterNumber, FALSE);

    w->monsterNumber++;

    return w->monsterNumber-1;
}

u8 switchMonsterScreen(World *w, u8 obj) {
    Monster o = w->monsters[obj];

    deleteMonster(w, obj);

    o.screen = o.screen == MAIN_SCREEN ? SUB_SCREEN : MAIN_SCREEN;
    o.pos.y = o.screen == SUB_SCREEN ? 0 : inttof32(176);
    return newMonster(w, o);
}

void updateMonster(World *w, u8 i) {
    Monster *cur = &w->monsters[i];

    u8 x0 = GRID_XPOS(cur->path[cur->cur_path_index]);
    u8 y0 = GRID_YPOS(cur->path[cur->cur_path_index]);

    u8 x = GRID_XPOS(cur->path[cur->cur_path_index +1]);
    u8 y = GRID_YPOS(cur->path[cur->cur_path_index +1]);

    s8 dx = x - x0;
    s8 dy = y - y0;

    if (dx) {
        sassert(dx == -1 || dx == 1, "Invalid path");
        cur->pos.x += mulf32(cur->speed, inttof32(dx));
        cur->dir = dx > 0 ? RIGHT : LEFT;
    }
    if (dy) {
        sassert(dy == -1 || dy == 1, "Invalid path");
        cur->pos.y += mulf32(cur->speed, inttof32(dy));
        cur->dir = dy > 0 ? DOWN : UP;
    }

    if (f32toint(cur->pos.y) % 16 == 0 && f32toint(cur->pos.x) % 16 == 0 &&
            f32togrid(cur->pos.y) + (cur->screen == MAIN_SCREEN ? 0 : 12) == y && f32togrid(cur->pos.x) == x) {
        cur->cur_path_index++;

        if (w->monsterGrid[x0][y0] == i) w->monsterGrid[x0][y0] = -1;
        w->monsterGrid[x][y] = i;

        if (cur->cur_path_index >= cur->path_size -1) {
            w->players[!cur->player].health--;
            w->players[!cur->player].money++;
            w->players[cur->player].money += 2;

            deleteMonster(w, i);
        }
        else if (dy == 1 && y == 12) {
            switchMonsterScreen(w, i);
        }
        else if (dy == -1 && y == 11) {
            switchMonsterScreen(w, i);
        }
        else if (w->needsDijkstra[i]) {
            dijkstra(w, i, FALSE);
            w->needsDijkstra[i] = FALSE;
        }
    }

    if (cur->type == KAMIKAZE) {
        u8 grid_x = f32togrid(cur->pos.x);
        u8 grid_y = f32togrid(cur->pos.y) + (cur->screen == MAIN_SCREEN ? 0 : 12);
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                s8 test_candidate_x = grid_x + j;
                s8 test_candidate_y = grid_y + k;
                if (test_candidate_x >= 0 && test_candidate_y >= 0 && test_candidate_x < 16 && test_candidate_y < 24) {
                    s16 index = w->towerGrid[test_candidate_x][test_candidate_y];
                    if (index != -1 && index != 255) {
                        Tower tower = w->towers[index];
                        if (tower.player != cur->player) {
                            cur->health = 0;
                        }
                    }
                }
            }
        }
    }

    if (cur->health <= 0) {
        w->players[!cur->player].money += cur->reward;

        if (cur->type == KAMIKAZE) {
            for (int j = 0; j < w->towerNumber; j++) {
                if ((MAX(abs(f32togrid(w->towers[j].pos.x) - f32togrid(cur->pos.x)), abs(f32togrid(w->towers[j].pos.y) - f32togrid(cur->pos.y)))) <= 1) {
                    deleteTower(w, j);
                    j--;
                }
            }
        }

        deleteMonster(w, i);
    }
}

void initialize_priority_queue(bin_heap_t *h) {
    h->max_size = MAX_PATH_BIN_HEAP_SIZE;
    h->size = 0;
    memset(h->data, 0, MAX_PATH_BIN_HEAP_SIZE * 2);
}

void insert_priority_queue(bin_heap_t *h, bin_heap_elem_t elem) {
    sassert(h->size < h->max_size, "Priority queue overflow.\n");

    h->data[h->size++] = elem;

    int p = h->size - 1;
    while (p && h->data[p].value < h->data[p >> 1].value) {
        bin_heap_elem_t aux = h->data[p];
        h->data[p] = h->data[p >> 1];
        h->data[p >> 1] = aux;

        p >>= 1;
    }
}

bin_heap_elem_t pop_priority_queue(bin_heap_t *h) {
    sassert(h->size, "Priority queue underflow.\n");

    bin_heap_elem_t result = h->data[0];

    h->size--;
    h->data[0] = h->data[h->size];

    int p = 0;
    while (p < h->size) {
        bin_heap_elem_t left = h->data[p * 2 + 1];
        bin_heap_elem_t right = h->data[p * 2 + 2];

        s8 swap = 0;
        if (h->data[p].value > left.value && p * 2 + 1 < h->size) {
            swap = -1;
        } else if (h->data[p].value > right.value && p * 2 + 2 < h->size) {
            swap = 1;
        }

        if (swap == -1) {
            bin_heap_elem_t aux = h->data[p];
            h->data[p] = h->data[p * 2 + 1];
            h->data[p * 2 + 1] = aux;
            p = p * 2 + 1;
        } else if (swap == 1) {
            bin_heap_elem_t aux = h->data[p];
            h->data[p] = h->data[p * 2 + 2];
            h->data[p * 2 + 2] = aux;
            p = p * 2 + 2;
        } else {
            break;
        }
    }

    return result;
}

u8 dijkstra(World *world, u16 id, u8 testing) {
    Monster *obj = &world->monsters[id];

    bin_heap_t queue;
    queue.data = malloc(MAX_PATH_BIN_HEAP_SIZE * sizeof(*queue.data));
    initialize_priority_queue(&queue);

    u16 starting_pos;
    if (testing) {
        starting_pos = 0;
    }
    else {
        starting_pos = GRID_POS(f32togrid(obj->pos.x), obj->screen == MAIN_SCREEN ? f32togrid(obj->pos.y) : f32togrid(obj->pos.y) + 12);
    }

    bin_heap_elem_t start = {starting_pos, 0};
    insert_priority_queue(&queue, start);

    u16 *visited = calloc(MAX_PATH_BIN_HEAP_SIZE, sizeof(u16));
    visited[starting_pos] = 1;

    u16 *predecessor = malloc(MAX_PATH_BIN_HEAP_SIZE * sizeof(u16));
    s16 *cost = malloc(MAX_PATH_BIN_HEAP_SIZE * sizeof(s16));
    memset(cost, -1, MAX_PATH_BIN_HEAP_SIZE * sizeof(s16));

#if 0
    PRINT("queue: [");
    for (int i = 0; i < queue.size; i++) {
        PRINT("(%d,%d) ", queue.data[i].value, queue.data[i].id);
    }
    PRINT("]\n");
#endif

    u16 end = 10000;
    while (queue.size) {
        bin_heap_elem_t next_pos = pop_priority_queue(&queue);

        if (visited[next_pos.id] == 2) {
            continue;
        }

        visited[next_pos.id] = 2;

        u16 x = GRID_XPOS(next_pos.id);
        u16 y = GRID_YPOS(next_pos.id);

        if (y == (testing ? 23 : (obj->player == PLAYER_1 ? 23 : 0))) {
            end = next_pos.id;
            //PRINT("Reached bottom.\n");
            break;
        }

        u16 pos;
        u8 test;

        pos = GRID_POS(x + 1, y);
        test = obj->type == KAMIKAZE ?
            (world->towerGrid[x+1][y] == -1 || (world->towerGrid[x+1][y] != 255 && world->towers[world->towerGrid[x+1][y]].player != obj->player)) :
            (world->towerGrid[x+1][y] == -1);
        if (x + 1 < 16 && visited[pos] != 2 && test) {
            if (cost[pos] == -1 || cost[pos] > next_pos.value + 1) {
                bin_heap_elem_t el = {pos, next_pos.value + 1};
                cost[pos] = next_pos.value + 1;
                visited[pos] = 1;
                predecessor[pos] = next_pos.id;
                insert_priority_queue(&queue, el);
            }
        }

        pos = GRID_POS(x - 1, y);
        test = obj->type == KAMIKAZE ?
            (world->towerGrid[x-1][y] == -1 || (world->towerGrid[x-1][y] != 255 && world->towers[world->towerGrid[x-1][y]].player != obj->player)) :
            (world->towerGrid[x-1][y] == -1);
        if (x - 1 >= 0 && visited[pos] != 2 && test) {
            if (cost[pos] == -1 || cost[pos] > next_pos.value + 1) {
                bin_heap_elem_t el = {pos, next_pos.value + 1};
                cost[pos] = next_pos.value + 1;
                visited[pos] = 1;
                predecessor[pos] = next_pos.id;
                insert_priority_queue(&queue, el);
            }
        }

        pos = GRID_POS(x, y + 1);
        test = obj->type == KAMIKAZE ?
            (world->towerGrid[x][y+1] == -1 || (world->towerGrid[x][y+1] != 255 && world->towers[world->towerGrid[x][y+1]].player != obj->player)) :
            (world->towerGrid[x][y+1] == -1);
        if (y + 1 < 24 && visited[pos] != 2 && test) {
            if (cost[pos] == -1 || cost[pos] > next_pos.value + 1) {
                bin_heap_elem_t el = {pos, next_pos.value + 1};
                cost[pos] = next_pos.value + 1;
                visited[pos] = 1;
                predecessor[pos] = next_pos.id;
                insert_priority_queue(&queue, el);
            }
        }

        pos = GRID_POS(x, y - 1);
        test = obj->type == KAMIKAZE ?
            (world->towerGrid[x][y-1] == -1 || (world->towerGrid[x][y-1] != 255 && world->towers[world->towerGrid[x][y-1]].player != obj->player)) :
            (world->towerGrid[x][y-1] == -1);
        if (y - 1 >= 0 && visited[pos] != 2 && test) {
            if (cost[pos] == -1 || cost[pos] > next_pos.value + 1) {
                bin_heap_elem_t el = {pos, next_pos.value + 1};
                cost[pos] = next_pos.value + 1;
                visited[pos] = 1;
                predecessor[pos] = next_pos.id;
                insert_priority_queue(&queue, el);
            }
        }

#if 0
        //PRINT("queue: [");
        for (int i = 0; i < queue.size; i++) {
            //PRINT("(%d,%d) ", queue.data[i].value, queue.data[i].id);
            fprintf(stderr, "(%d,%d) ", queue.data[i].value, queue.data[i].id);
        }
        //PRINT("]\n");

        PRINT("queue size: %d\n", queue.size);
#endif
    }

    if (!testing) {
        obj->cur_path_index = 0;

        u16 pos = end;
        {
            u16 i = 0;
            while (pos != starting_pos) {
                obj->path[i++] = pos;
                pos = predecessor[pos];
            }
            obj->path[i++] = starting_pos;
            obj->path_size = i;
        }

        // reverse
        {
            for (u16 i = 0; i < obj->path_size / 2; i++) {
                u16 aux = obj->path[i];
                obj->path[i] = obj->path[obj->path_size - i - 1];
                obj->path[obj->path_size - i - 1] = aux;
            }
        }
    }

#if 0
    PRINT("path: [");
    for (int i = 0; i < obj->path_size; i++) {
        PRINT("%d ", obj->path[i]);
    }
    PRINT("]\n");
#endif

    free(queue.data);
    free(visited);
    free(predecessor);

    return end != 10000;
}

