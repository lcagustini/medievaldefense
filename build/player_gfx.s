
@{{BLOCK(player_gfx)

@=======================================================================
@
@	player_gfx, 112x32@4, 
@	Transparent color : A0,B0,80
@	+ palette 16 entries, not compressed
@	+ 56 tiles Metatiled by 2x4 not compressed
@	Total size: 32 + 1792 = 1824
@
@	Time-stamp: 2018-07-27, 17:18:49
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.14
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global player_gfxTiles		@ 1792 unsigned chars
	.hidden player_gfxTiles
player_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00090000,0x99959000,0x52529900,0x55222290,0x55522900
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000099,0x00009955,0x00092555,0x00925555
	.word 0x55252300,0x22522930,0x22229930,0x22929910,0x29999E10,0x99991100,0x9911E100,0xEEEE6000
	.word 0x00325555,0x03922555,0x03992222,0x01992922,0x01E99992,0x00119999,0x001E1199,0x0006EEEE
	.word 0x88614100,0x99799760,0xAA917760,0xAA811600,0x88793000,0x77911000,0x11FF1000,0x00110000
	.word 0x00141688,0x06799799,0x067719AA,0x006118AA,0x00039788,0x00011977,0x0001FF11,0x00001100

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x90000000,0x29900000,0x55599000,0x55555900
	.word 0x00000000,0x00000000,0x00000000,0x00000090,0x00000959,0x00000955,0x00009222,0x00092255
	.word 0x55555510,0x55555C10,0x255499F0,0x99994410,0x99999910,0x99999A60,0x3EE1AA60,0xEEB6B600
	.word 0x00092255,0x00922525,0x09222252,0x009C222C,0x00032299,0x00019999,0x000199EB,0x000019EB
	.word 0xEEEE6000,0x11661000,0x44D41000,0xFFD91000,0x77110000,0x11930000,0x7FF10000,0x11100000
	.word 0x00001733,0x0001AA7D,0x00018A71,0x00017881,0x00001771,0x00000119,0x00000001,0x00000000

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x99000000,0x55990000,0x55529000,0x55552900
	.word 0x00000000,0x00000000,0x00000000,0x00009000,0x00095999,0x00992525,0x09222255,0x00922555
	.word 0x55552300,0x55522930,0x22229930,0x94999910,0x49991E10,0x99916100,0xA1BEE100,0xB6EE6000
	.word 0x00325255,0x03922522,0x03992222,0x01999949,0x01E19994,0x00161999,0x001EEB1A,0x0006EE6B
	.word 0xEE614100,0x11199760,0x49917760,0x99411600,0x44F93000,0xD9911000,0x01FF1000,0x00110000
	.word 0x001416EE,0x06799111,0x06771994,0x00611499,0x00039F44,0x0001199D,0x0001FF10,0x00001100

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x90000000,0x59900000,0x55290000,0x55529000
	.word 0x00000000,0x00000000,0x00000000,0x00090000,0x00959999,0x09925255,0x92222555,0x09225555
	.word 0x55523000,0x55229300,0x22299300,0x49999100,0x9991E100,0x99161000,0x1BEE1600,0x6EE69760
	.word 0x03252555,0x39225225,0x39922222,0x19999499,0x1E199944,0x01619999,0x01EEB1AA,0x006EE6BB
	.word 0xE6149760,0x11991100,0x99910000,0x94110000,0x4F930000,0x99100000,0xFF100000,0x11000000
	.word 0x01416EEE,0x06991111,0x06BB9944,0x06779999,0x00669444,0x00000119,0x00000001,0x00000000

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00090000,0x99959000,0x52529900,0x55222290,0x55522900
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000099,0x00009955,0x00092555,0x00925555
	.word 0x55252300,0x22522930,0x22229930,0x22929910,0x29999E10,0x99991100,0x9911E160,0xEEEE6760
	.word 0x00325555,0x03922555,0x03992222,0x01992922,0x01E99992,0x00119999,0x001E1199,0x0006EEEE
	.word 0x886F4760,0x99799100,0xAA999000,0xAA891000,0x88791000,0x77990000,0x1FF10000,0x01100000
	.word 0x0001F688,0x00149799,0x067999AA,0x067798AA,0x00669788,0x00001977,0x00000011,0x00000000

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x90000000,0x29900000,0x55599000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000090,0x00000959,0x00000955,0x00009222
	.word 0x55555900,0x55555510,0x55555C10,0x255499F0,0x99994410,0x99999910,0x99999A60,0x3EE1AA60
	.word 0x00092255,0x00092255,0x00922525,0x09222252,0x009C222C,0x00032299,0x00019999,0x000199EB
	.word 0xEEB6B600,0xEEEE6000,0x11661000,0x94AA1000,0x19771000,0x91191000,0x11110000,0x00000000
	.word 0x000019EB,0x00001733,0x0001AA7D,0x00018A71,0x00017881,0x00001791,0x00001FFF,0x00000111

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x90000000,0x29900000,0x55599000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000090,0x00000959,0x00000955,0x00009222
	.word 0x55555900,0x55555510,0x55555C10,0x255499F0,0x99994410,0x99999910,0x99999A60,0x3EE1AA60
	.word 0x00092255,0x00092255,0x00922525,0x09222252,0x009C222C,0x00032299,0x00019999,0x000199EB
	.word 0xEEB6B600,0xEEEE6000,0x11661000,0x94D41000,0x91991000,0x19114100,0x1144F100,0x00111000
	.word 0x000019EB,0x00001733,0x0001AA8D,0x000188AA,0x00017877,0x00001881,0x00000111,0x00000000

	.section .rodata
	.align	2
	.global player_gfxPal		@ 32 unsigned chars
	.hidden player_gfxPal
player_gfxPal:
	.hword 0x42D4,0x0000,0x6F38,0x0CE7,0x29DC,0x7FFF,0x210F,0x36D9
	.hword 0x21CF,0x2D29,0x5F7F,0x4F1E,0x4A51,0x004A,0x3A7B,0x1512

@}}BLOCK(player_gfx)
