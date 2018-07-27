
@{{BLOCK(teste)

@=======================================================================
@
@	teste, 512x512@4, 
@	Transparent color : FF,00,FF
@	+ palette 16 entries, not compressed
@	+ 5 tiles (t|f|p reduced) not compressed
@	+ regular map (in SBBs), not compressed, 64x64 
@	Total size: 32 + 160 + 8192 = 8384
@
@	Time-stamp: 2018-07-27, 16:28:03
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.14
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global testeTiles		@ 160 unsigned chars
	.hidden testeTiles
testeTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000
	.word 0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x11111111
	.word 0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11000000,0x11111111,0x11111111

	.section .rodata
	.align	2
	.global testeMap		@ 8192 unsigned chars
	.hidden testeMap
testeMap:
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0001,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003
	.hword 0x0003,0x0003,0x0003,0x0004,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002
	.hword 0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002

	.section .rodata
	.align	2
	.global testePal		@ 32 unsigned chars
	.hidden testePal
testePal:
	.hword 0x7C80,0x07E0,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(teste)
