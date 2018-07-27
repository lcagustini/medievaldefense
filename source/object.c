#define GRIDX(x) ((x) >> 4)
#define GRIDY(y) ((y) >> 4)
#define GRID_POS(x, y) (y + ((x) >> 4))
#define GRID_XPOS(coord) ((coord) % 16)
#define GRID_YPOS(coord) ((coord) >> 4)

#define MAX_PATH_BIN_HEAP_SIZE 400

void dijkstra(Object *obj);

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
    } else {
        w->grid[s.x >> 4][(s.y >> 4) + 12] = s.id; 
    }

    /*
    if (s.speed) {
        s.path = malloc(MAX_PATH_BIN_HEAP_SIZE * sizeof(u16));
        dijkstra(&s);
        // TODO: remember to free on obj destruction
    }
    */

    return s.id;
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
    while (p <= h->size) {
        bin_heap_elem_t left = h->data[p * 2 + 1];
        bin_heap_elem_t right = h->data[p * 2 + 2];

        s8 swap = 0;
        if (p < left.value && p * 2 + 1 < h->size) {
            swap = -1;
        } else if (p > right.value && p * 2 + 2 < h->size) {
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

void dijkstra(Object *obj) {

    bin_heap_t queue;
    queue.data = malloc(MAX_PATH_BIN_HEAP_SIZE * sizeof(*queue.data));
    initialize_priority_queue(&queue);

    u16 starting_pos = GRID_POS(obj->x, obj->y);

    bin_heap_elem_t start = {starting_pos, 0};
    insert_priority_queue(&queue, start);

    u16 *visited = calloc(MAX_PATH_BIN_HEAP_SIZE, sizeof(u16));
    visited[starting_pos] = 1;

    while (queue.size) {
        bin_heap_elem_t next_pos = pop_priority_queue(&queue);

        u16 x = GRIDX(next_pos.id);
        u16 y = GRIDY(next_pos.id);

        if (x + 1 < 24 && !visited[GRID_POS(x + 1, y)]) {
            bin_heap_elem_t el = {GRID_POS(x + 1, y), next_pos.value + 1};
            insert_priority_queue(&queue, el);
            visited[GRID_POS(x + 1, y)] = 1;
        }
        if (x - 1 >= 0 && !visited[GRID_POS(x - 1, y)]) {
            bin_heap_elem_t el = {GRID_POS(x - 1, y), next_pos.value + 1};
            insert_priority_queue(&queue, el);
            visited[GRID_POS(x - 1, y)] = 1;
        }
        if (y + 1 < 16 && !visited[GRID_POS(x, y + 1)]) {
            bin_heap_elem_t el = {GRID_POS(x, y + 1), next_pos.value + 1};
            insert_priority_queue(&queue, el);
            visited[GRID_POS(x, y + 1)] = 1;
        }
        if (y - 1 >= 0 && !visited[GRID_POS(x, y - 1)]) {
            bin_heap_elem_t el = {GRID_POS(x, y - 1), next_pos.value + 1};
            insert_priority_queue(&queue, el);
            visited[GRID_POS(x, y - 1)] = 1;
        }

        //fprintf(stderr, "queue: [");
        //fprintf(stderr, "");
        PRINT("ABC\n");

        // TODO: stop and reconstruct path when desired Y is reached
    }

    free(queue.data);
    free(visited);
}

