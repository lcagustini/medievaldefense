
@{{BLOCK(tower)

@=======================================================================
@
@	tower, 16x16@4, 
@	Transparent color : FF,00,FF
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2018-07-27, 17:18:48
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.14
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global towerTiles		@ 128 unsigned chars
	.hidden towerTiles
towerTiles:
	.word 0x33333300,0x41146630,0x47766663,0x17711563,0x22222143,0x22222143,0x77777143,0x77777143
	.word 0x00333333,0x03664114,0x36666774,0x36511771,0x34122222,0x34122222,0x34177777,0x34177777
	.word 0x77777143,0x22222143,0x22221443,0x22216643,0x78766663,0x78766663,0x11146630,0x33333300
	.word 0x34177777,0x34122222,0x34412222,0x34661222,0x36666787,0x36666787,0x03664111,0x00333333

	.section .rodata
	.align	2
	.global towerPal		@ 32 unsigned chars
	.hidden towerPal
towerPal:
	.hword 0x7C1F,0x39CE,0x4E73,0x462E,0x5AD2,0x4A50,0x6314,0x4A52
	.hword 0x4631,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(tower)
