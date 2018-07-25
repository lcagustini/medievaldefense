Background *newBackground(World *w, int layer, gfx_t *data, BgType type, BgSize size, int mapBase, int tileBase, Screen screen){
    Background *b = malloc(sizeof(Background));
    b->id = screen == MAIN_SCREEN ? bgInit(layer, type, size, mapBase, tileBase) : bgInitSub(layer, type, size, mapBase, tileBase);
    bgSetPriority(b->id, layer);
    b->data = data;

    w->bgs[layer] = b;

    DC_FlushAll();
    dmaCopyHalfWordsAsynch(0, b->data->tiles, bgGetGfxPtr(b->id), b->data->tilesLen);
    dmaCopyHalfWordsAsynch(1, b->data->map, bgGetMapPtr(b->id), b->data->mapLen);
    dmaCopyHalfWordsAsynch(2, b->data->pal, screen == MAIN_SCREEN ? BG_PALETTE : BG_PALETTE_SUB, b->data->palLen);
    return b;
}

void startBgDraw(){
    //bgExtPaletteEnableSub();
    //vramSetBankH(VRAM_H_LCD);
}

void endBgDraw(){
    //vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
}
