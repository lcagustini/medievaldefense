#ifndef NDS
#define NDS
#include <nds.h>
#include "types.h"
#endif

Background *newBackground(World *w, int layer, gfx_t *data, BgType type, BgSize size, int mapBase, int tileBase, Screen screen);

void startBgDraw();

void endBgDraw();
