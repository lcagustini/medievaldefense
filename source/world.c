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
    u8 t = w->random[0] ^ (w->random[0] << 4);

    w->random[0] = w->random[1];
    w->random[1] = w->random[2];
    w->random[2] = w->random[3];
    w->random[3] = w->random[3] ^ t ^ (w->random[3] >> 1) ^ (t << 1);

    return w->random[3];
}
