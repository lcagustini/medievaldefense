//#define GRIDX(x) ((x) >> 4)
//#define GRIDY(y) ((y) >> 4)
//#define GRID_POS(x, y) (y + ((x) >> 4))
#define GRID_POS(x, y) (((y) << 4) + (x))
#define GRID_XPOS(coord) ((coord) % 16)
#define GRID_YPOS(coord) ((coord) >> 4)

#define MAX_PATH_BIN_HEAP_SIZE 400

void dijkstra(World *, u16);

void updateObject(Object s){
    bool hflip = false;
    if(s.direction == DIR_RIGHT){
        hflip = true;
        s.direction = DIR_LEFT;
    }

    oamSet(s.screen, // which display
            s.id, // the oam entry to set
            s.x, s.y, // x & y location
            1, // priority
            s.palId, // palette for 16 color sprite or alpha for bmp sprite
            s.size, // size
            s.color, // color type
            s.gfx, // the oam gfx
            -1, //affine index
            true, //double the size of rotated sprites
            false, //don't hide the sprite
            hflip, false, //vflip, hflip
            false //apply mosaic
          );
    DC_FlushAll();
    if(s.screen == &oamMain)
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE[16*s.palId], s.gfxData->palLen);
    else
        dmaCopy(s.gfxData->pal, &SPRITE_PALETTE_SUB[16*s.palId], s.gfxData->palLen);

    dmaCopy(s.gfxData->tiles, s.gfx, 128);
}

void updateScreens(World *w){
    oamClear(&oamMain, 0, 0);
    oamClear(&oamSub, 0, 0);

    //fprintf(stderr, "%d\n", w->objectNumber);
    for(int i = 0; i < w->objectNumber; i++){
        updateObject(w->objects[i]);
    }
}

u8 newObject(World *w, int x, int y, u8 speed, OamState* screen, SpriteSize size, SpriteColorFormat format, gfx_t *data, u8 palId){
    sassert(w->objectNumber < SPRITE_COUNT, "Too many sprites!");

    Object s;
    s.id = w->objectNumber;
    s.x = x;
    s.y = y;
    s.gfx = oamAllocateGfx(screen, size, format);
    s.screen = screen;
    s.size = size;
    s.color = format;
    s.walking = FALSE;
    s.direction = DIR_DOWN;
    s.walked = 0;
    s.speed = speed;
    s.priority = 0;
    s.gfxData = data;
    s.palId = palId;

    w->objectNumber++;
    w->objects[s.id] = s;
    if (screen == &oamMain) {
        w->grid[s.x >> 4][s.y >> 4] = s.id; 
        PRINT("s.x %d s.y %d\n", (s.x >> 4), (s.y >> 4));
    } else {
        w->grid[s.x >> 4][(s.y >> 4) + 12] = s.id; 
        PRINT("s.x %d s.y %d\n", (s.x >> 4), (s.y >> 4) + 12);
    }

    if (s.speed) {
        s.path = malloc(MAX_PATH_BIN_HEAP_SIZE * sizeof(u16));
        dijkstra(w, s.id);
        // TODO: remember to free on obj destruction
    }

    return s.id;
}

void initialize_priority_queue(bin_heap_t *h) {
    h->max_size = MAX_PATH_BIN_HEAP_SIZE;
    h->size = 0;
    memset(h->data, 0, MAX_PATH_BIN_HEAP_SIZE * 2);
}

void insert_priority_queue(bin_heap_t *h, bin_heap_elem_t elem) {
    //PRINT("h->size %d\n h->max_size %d\n", h->size, h->max_size);
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

void dijkstra(World *world, u16 id) {
    Object *obj = &world->objects[id];

    bin_heap_t queue;
    queue.data = malloc(MAX_PATH_BIN_HEAP_SIZE * sizeof(*queue.data));
    initialize_priority_queue(&queue);

    u16 starting_pos;
    if (obj->screen == &oamMain) {
        starting_pos = GRID_POS(obj->x >> 4, obj->y >> 4);
    } else {
        starting_pos = GRID_POS(obj->x >> 4, (obj->y >> 4) + 12);
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

        if (y == 23) {
            end = next_pos.id;
            //PRINT("Reached bottom.\n");
            break;
        }

        u16 pos;
        u8 isfree;

        pos = GRID_POS(x + 1, y);
        isfree = TRUE;
        if (world->grid[x+1][y] != -1) {
            Object o = world->objects[world->grid[x+1][y]];
            if (!o.speed) {
                isfree = FALSE;
            }
        }
        if (x + 1 < 16 && visited[pos] != 2 && isfree) {
            if (cost[pos] == -1 || cost[pos] > next_pos.value + 1) {
                bin_heap_elem_t el = {pos, next_pos.value + 1};
                cost[pos] = next_pos.value + 1;
                visited[pos] = 1;
                predecessor[pos] = next_pos.id;
                insert_priority_queue(&queue, el);
            }
        }

        isfree = TRUE;
        if (world->grid[x-1][y] != -1) {
            Object o = world->objects[world->grid[x+1][y]];
            if (!o.speed) {
                isfree = FALSE;
            }
        }
        pos = GRID_POS(x - 1, y);
        if (x - 1 >= 0 && visited[pos] != 2 && isfree) {
            if (cost[pos] == -1 || cost[pos] > next_pos.value + 1) {
                bin_heap_elem_t el = {pos, next_pos.value + 1};
                cost[pos] = next_pos.value + 1;
                visited[pos] = 1;
                predecessor[pos] = next_pos.id;
                insert_priority_queue(&queue, el);
            }
        }

        isfree = TRUE;
        if (world->grid[x][y+1] != -1) {
            Object o = world->objects[world->grid[x+1][y]];
            if (!o.speed) {
                isfree = FALSE;
            }
        }
        pos = GRID_POS(x, y + 1);
        if (y + 1 < 24 && visited[pos] != 2 && isfree) {
            if (cost[pos] == -1 || cost[pos] > next_pos.value + 1) {
                bin_heap_elem_t el = {pos, next_pos.value + 1};
                cost[pos] = next_pos.value + 1;
                visited[pos] = 1;
                predecessor[pos] = next_pos.id;
                insert_priority_queue(&queue, el);
            }
        }

        isfree = TRUE;
        if (world->grid[x][y-1] != -1) {
            Object o = world->objects[world->grid[x+1][y]];
            if (!o.speed) {
                isfree = FALSE;
            }
        }
        pos = GRID_POS(x, y - 1);
        if (y - 1 >= 0 && visited[pos] != 2 && isfree) {
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

    obj->cur_path_index = 0;

    u16 pos = end;
    {
        u16 i = 0;
        while (pos != starting_pos) {
            obj->path[i++] = pos;
            pos = predecessor[pos];
        }
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

#if 1
    PRINT("path: [");
    for (int i = 0; i < obj->path_size; i++) {
        PRINT("%d ", obj->path[i]);
    }
    PRINT("]\n");
#endif

    free(queue.data);
    free(visited);
    free(predecessor);
}

