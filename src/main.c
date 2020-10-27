////////////////////////////////////////////////////////////////////
// SurvivalCE Map Creator Version DEV_0.00
// Author: TimmyTurner62
// License: Gnu GPLv2?
// Description: SurvivalCE Map Creator Tool. Thanks to Michael0x18.
////////////////////////////////////////////////////////////////////
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gfx/gfx.h"
void main(void);
void createVars(void);
void LoadMapChunk(void);



void main(void) {

	uint16_t CursorX;
	uint16_t CursorY;
	char screenMap[20*15];
	uint16_t x;
	uint16_t y;
	uint16_t xa;
	gfx_sprite_t* sprites[12] = {dirt, grass, stone, wood, wood2, water, lava, netherrack, fireball, traptile1, traptile2, sailcloth};
	loadVars();
	for (y = 1; y < 15; y++) {
		for (x = 1; x < 20; x++) {
			screenMap[x * y] = 0;
		}
	}
	/* Draw the screen */
	gfx_Begin();
	gfx_SetPalette(mypalette, sizeof_mypalette, 0);
	gfx_FillScreen(255);
	xa = 0;
	for (y = 1; y < 15; y++) {
		for (x = 1; x < 20; x++) {
			if (screenMap[xa] != 0) gfx_Sprite(sprites[screenMap[xa]], x * 16, y * 16);
			xa = xa + 1;
		}
	}

		while (!kb_Data[1] & kb_Clear) {

	}
		gfx_End();
}


/* loading appvars… */
void loadVars(void) {
	typedef struct {
  		char name[15];
   		uint8_t var1;
   		uint8_t var2;
} data_t;
data_t data;
   strcpy(data.name, "My Data");
	ti_var_t appvar;
	appvar = ti_Open(“SrvCEss”, “r”);
	if (!appvar)goto write;
	write:
ti_Write(&data, sizeof(data_t), 1, appvar);
	return;
}

void input(void) {
	const char* chars = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	uint8_t key, i = 0;
	char buffer[50];
	gfx_Begin();
	while ((key = os_GetCSC()) != sk_Enter) {
		if (chars[key]) {
			buffer[i++] = chars[key];
			gfx_PrintStringXY(buffer, 1, 1);
		}
	}
	
	Xrooms = 20;
	Yrooms = 20;
	XsizeL = (Xrooms / 2) * 20;
	XsizeR = (Xrooms - XsizeL) * 20;
	Xsize = Xrooms * 20;
	Ysize = Yrooms * 15;

	delay(1000);

	createVars();

	gfx_End();
	return;
}
