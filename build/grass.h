
//{{BLOCK(grass)

//======================================================================
//
//	grass, 512x512@4, 
//	Transparent color : FF,00,FF
//	+ palette 16 entries, not compressed
//	+ 101 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 32 + 3232 + 8192 = 11456
//
//	Time-stamp: 2018-07-01, 19:19:23
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GRASS_H
#define GRIT_GRASS_H

#define grassTilesLen 3232
extern const unsigned int grassTiles[808];

#define grassMapLen 8192
extern const unsigned short grassMap[4096];

#define grassPalLen 32
extern const unsigned short grassPal[16];

#endif // GRIT_GRASS_H

//}}BLOCK(grass)
