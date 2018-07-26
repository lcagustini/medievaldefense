
@{{BLOCK(troll)

@=======================================================================
@
@	troll, 16x16@4, 
@	Transparent color : FF,00,FF
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2018-07-25, 19:01:56
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global trollTiles		@ 128 unsigned chars
	.hidden trollTiles
trollTiles:
	.word 0x00000000,0x11120000,0x11111000,0x11111100,0x11111120,0x11111110,0x11111110,0x11111110
	.word 0x00000000,0x00002111,0x00011111,0x00111111,0x02111111,0x01111111,0x01111111,0x01111111
	.word 0x11111110,0x11111110,0x11111110,0x11111120,0x11111100,0x11111000,0x11120000,0x00000000
	.word 0x01111111,0x01111111,0x01111111,0x02111111,0x00111111,0x00011111,0x00002111,0x00000000

	.section .rodata
	.align	2
	.global trollPal		@ 32 unsigned chars
	.hidden trollPal
trollPal:
	.hword 0x7C1F,0x0869,0x086A,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(troll)
