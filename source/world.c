u8 getDrawId(World *w, Screen screen) {
    for (int i = 0; i < 128; i++) {
        if (!w->freeDrawId[screen][i]) {
            w->freeDrawId[screen][i] = 1;
            return i;
        }
    }
    sassert(false, "Out of sprites");
    return 128;
}

void freeDrawId(World *w, Screen screen, u8 id) {
    w->freeDrawId[screen][id] = 0;
}
