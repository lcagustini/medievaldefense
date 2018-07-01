#ifndef NDS
#define NDS
#include <nds.h>
#include "types.h"
#endif

enum Directions{DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT};

void walk(World *w, Object *s, u16 input);

void updateScreens();

Object *newObject(World *w, int x, int y, u8 speed, OamState* screen, SpriteSize size, SpriteColorFormat format, gfx_t *data);
