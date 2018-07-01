
//{{BLOCK(center)

//======================================================================
//
//	center, 512x512@8, 
//	Transparent color : FF,00,FF
//	+ palette 256 entries, not compressed
//	+ 85 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 512 + 5440 + 8192 = 14144
//
//	Time-stamp: 2018-07-01, 15:49:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CENTER_H
#define GRIT_CENTER_H

#define centerTilesLen 5440
extern const unsigned int centerTiles[1360];

#define centerMapLen 8192
extern const unsigned short centerMap[4096];

#define centerPalLen 512
extern const unsigned short centerPal[256];

#endif // GRIT_CENTER_H

//}}BLOCK(center)
