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
void input(void);
void start(void);



void main(void) {
	gfx_Begin();
	gfx_SetPalette(mypalette, sizeof_mypalette, 0);
	createVars();
	start();
}

void start(void) {
	uint16_t CursorX;
	uint16_t CursorY;
	uint16_t pos;
	uint16_t Type;
	char screenMap[20 * 15];
	uint16_t x;
	uint16_t y;
	uint16_t xa;
	uint16_t xb;
	uint16_t exit;
	uint8_t appvar;
	gfx_sprite_t* sprites[12] = { dirt, grass, stone, wood, wood2, water, lava, netherrack, fireball, traptile1, traptile2, sailcloth };
	gfx_FillScreen(255);
	CursorX = 0;
	CursorY = 0;
	Type = 0;
	xa = 0;
	exit = 0;
	while (exit == 0) {
		gfx_SetColor(210);
		if (Type == 0)gfx_FillRectangle(CursorX + 6, CursorY + 6, 4, 4);
		if (Type != 0)gfx_Sprite(sprites[Type], CursorX, CursorY);
		if (kb_IsDown(kb_KeyUp) && CursorY > 0) {
			//gfx_BlitScreen();
			delay(100);
			CursorY = CursorY - 16;
			xa = xa - 20;
		}
		if (kb_IsDown(kb_KeyDown) && CursorY < 224) {
			//gfx_BlitScreen();
			delay(100);
			CursorY = CursorY + 16;
			xa = xa + 20;
		}
		if (kb_IsDown(kb_KeyLeft) && CursorX > 0) {
			//gfx_BlitScreen();
			delay(100);
			CursorX = CursorX - 16;
			xa = xa - 1;
		}
		if (kb_IsDown(kb_KeyRight) && CursorX < 304) {
			//gfx_BlitScreen();
			delay(100);
			CursorX = CursorX + 16;
			xa = xa + 1;
		}
		if (kb_IsDown(kb_Key2nd)) {
			delay(100);
			screenMap[xa] = Type;
		}
		if (kb_IsDown(kb_KeyAlpha)) {
			delay(160);
			Type = Type + 1;
		}
			if (Type > 11)Type = 0;
			if (kb_IsDown(kb_KeyClear)) {
				exit = 1;
				ti_CloseAll();
				appvar = ti_Open("SrvMap00", "w");
				ti_Write(screenMap, 300, 1, appvar);
				ti_SetArchiveStatus(1, appvar);
				ti_CloseAll();
				gfx_End();
				return;
			}

				gfx_SetColor(255);
				xb = 0;
				for (y = 0; y < 15; y++) {
					for (x = 0; x < 20; x++) {
						if (xb != xa) {
							if ((screenMap[xb] > 0))gfx_Sprite(sprites[screenMap[xb]], x * 16, y * 16);
							if ((screenMap[xb] == 0))gfx_FillRectangle(x * 16, y * 16, 16, 16);
						}
						xb = xb + 1;
					}
				}
	}
	gfx_End();

}



/* loading appvars… */
void createVars(void) {
	char screenMap[20 * 15];
	ti_var_t appvar;
	uint8_t xb;
	uint8_t x;
	uint8_t y;
	gfx_sprite_t* sprites[12] = { dirt, grass, stone, wood, wood2, water, lava, netherrack, fireball, traptile1, traptile2, sailcloth };
	ti_CloseAll();
	appvar = ti_Open("SrvMap00", "r");
	if (!appvar) {
			for (x = 0; x < 20 * 15; x++) {
				screenMap[x] = 0;
			}
		ti_CloseAll();
		appvar = ti_Open("SrvMap00", "w");
		ti_Write(screenMap, 300, 1, appvar);
		ti_SetArchiveStatus(1, appvar);
		ti_CloseAll();
	}
	
	if (appvar) {
		ti_CloseAll();
		appvar = ti_Open("SrvMap00", "r");
		ti_Read(screenMap, 300, 1, appvar);
		xb = 0;
		start();
		gfx_SetColor(255);
		for (y = 0; y < 15; y++) {
			for (x = 0; x < 20; x++) {
				if (screenMap[xb] > 0 && screenMap[xb] < 12)gfx_Sprite(sprites[screenMap[xb]], x * 16, y * 16);
				if ((screenMap[xb] == 0))gfx_FillRectangle(x * 16, y * 16, 16, 16);
				xb = xb + 1;
			}
		}
		ti_CloseAll();
	}
	
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

	delay(1000);

	createVars();

	gfx_End();
	return;
}