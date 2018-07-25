
//{{BLOCK(teste)

//======================================================================
//
//	teste, 512x512@4, 
//	Transparent color : FF,00,FF
//	+ palette 16 entries, not compressed
//	+ 5 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 32 + 160 + 8192 = 8384
//
//	Time-stamp: 2018-07-25, 16:35:29
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TESTE_H
#define GRIT_TESTE_H

#define testeTilesLen 160
extern const unsigned int testeTiles[40];

#define testeMapLen 8192
extern const unsigned short testeMap[4096];

#define testePalLen 32
extern const unsigned short testePal[16];

#endif // GRIT_TESTE_H

//}}BLOCK(teste)
