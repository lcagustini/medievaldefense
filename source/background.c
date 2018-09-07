#define infoMapLen 128
extern unsigned short infoMap[64];

void newBackground(World *w, u8 layer, gfx_t *data, BgType type, BgSize size, u16 mapBase, u16 tileBase, Screen screen, bool defaultMap){
    Background b;

    b.id = screen == MAIN_SCREEN ? bgInit(layer, type, size, mapBase, tileBase) : bgInitSub(layer, type, size, mapBase, tileBase);
    bgSetPriority(b.id, layer);
    b.data = data;

    w->bgs[screen][layer] = b;

    //DC_FlushAll();
    dmaCopyHalfWordsAsynch(0, b.data->tiles, bgGetGfxPtr(b.id), b.data->tilesLen);
    if (defaultMap) {
        dmaCopyHalfWordsAsynch(1, b.data->map, bgGetMapPtr(b.id), b.data->mapLen);
    }
    dmaCopyHalfWordsAsynch(2, b.data->pal, screen == MAIN_SCREEN ? BG_PALETTE : BG_PALETTE_SUB, b.data->palLen);
}

void drawHUD(World *w, u16 money, u8 health) {
    //Coin
    infoMap[0] = 0x0001;
    infoMap[32] = 0x000C;

    //Money number
    u16 first = money / 1000;
    infoMap[1] = 0x0002 + first;
    infoMap[33] = 0x000D + first;

    u16 second = (money % 1000) / 100;
    infoMap[2] = 0x0002 + second;
    infoMap[34] = 0x000D + second;

    u16 third = (money % 100) / 10;
    infoMap[3] = 0x0002 + third;
    infoMap[35] = 0x000D + third;

    u16 fourth = money % 10;
    infoMap[4] = 0x0002 + fourth;
    infoMap[36] = 0x000D + fourth;

    //Hearth
    infoMap[27] = 0x0017;
    infoMap[28] = 0x0018;
    infoMap[59] = 0x0019;
    infoMap[60] = 0x001A;

    //Health number
    first = health / 100;
    infoMap[29] = 0x0002 + first;
    infoMap[61] = 0x000D + first;

    second = (health % 100) / 10;
    infoMap[30] = 0x0002 + second;
    infoMap[62] = 0x000D + second;

    third = health % 10;
    infoMap[31] = 0x0002 + third;
    infoMap[63] = 0x000D + third;

    dmaCopyHalfWordsAsynch(3, infoMap, bgGetMapPtr(w->bgs[SUB_SCREEN][0].id), infoMapLen);
}
