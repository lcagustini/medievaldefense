u8 getDrawId(World *w, Screen screen) {
    for (int i = 0; i < 128; i++) {
        if (!w->freeDrawId[screen][i]) {
            w->freeDrawId[screen][i] = 1;
            return i;
        }
    }
    sassert(false, "Out of sprites");
    return -1;
}

void freeDrawId(World *w, Screen screen, u8 id) {
    w->freeDrawId[screen][id] = 0;
}

u8 getRandomNumber(World *w) {
    w->random ^= w->random << 7;
    w->random ^= w->random >> 5;
    w->random ^= w->random << 3;
    return w->random;
}
