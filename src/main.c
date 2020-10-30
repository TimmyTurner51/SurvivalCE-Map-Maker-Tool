////////////////////////////////////////////////////////////////////
// SurvivalCE Map Creator Version DEV_0.22
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
void drawScreen();
void addRoom(void);

	static gfx_sprite_t* sprites[12] = { dirt, grass, stone, wood, wood2, water, lava, netherrack, fireball, traptile1, traptile2, sailcloth };
	static char wholeMap[(20 * 14) * (15 * 14)];
	static uint8_t screen;
	static uint32_t CursorX;
	static uint32_t CursorY;
	static uint32_t pos;
	static uint32_t Type;
	static uint32_t x;
	static uint32_t y;
	static uint32_t i;
	static uint32_t xa;
	static uint32_t xb;
	static uint32_t OldX;
	static uint32_t OldY;
	static uint32_t option;
	static uint8_t appvar;
	static uint8_t redraw;
	static uint32_t room;
	static uint32_t roomX;
	static uint32_t roomY;


void main(void) {
	gfx_Begin();
	gfx_SetPalette(mypalette, sizeof_mypalette, 0);
	for (xa = 0; xa < sizeof(wholeMap); xa++) {
		wholeMap[xa] = 0;
	}
	screen = 1;
	createVars();
	start();
}

void drawScreen(void) {
	redraw = 0;
	gfx_SetColor(255);
	xb = room - 1;
	for (y = 0; y < 15; y++) {
		for (x = 0; x < 20; x++) {
				if ((wholeMap[xb] > -1))gfx_Sprite(sprites[wholeMap[xb]], x * 16, y * 16);
			xb++;
		}
		xb += 20 * 13;
	}
}

void start(void) {
	uint8_t exit;
	uint8_t start;
	uint8_t end;
	gfx_FillScreen(255);
	CursorX = 0;
	CursorY = 0;
	Type = 0;
	xa = 0;
	exit = 0;
	redraw = 1;
	room = 1;
	roomX = 1;
	roomY = 1;
	while (exit == 0) {
		kb_Scan();

			gfx_SetColor(255);
			gfx_FillRectangle(CursorX, CursorY, 16, 16);
			gfx_SetColor(210);
			gfx_FillRectangle(CursorX + 6, CursorY + 6, 4, 4);

		if (Type != 0)gfx_Sprite(sprites[Type], CursorX, CursorY);

		if (kb_IsDown(kb_KeyUp) && CursorY > 0) {
			redraw = 1;
			delay(100);
			CursorY = CursorY - 16;
			xa -= 20 * 14;
		}
		if (kb_IsDown(kb_KeyDown) && CursorY < 224) {
			redraw = 1;
			delay(100);
			CursorY = CursorY + 16;
			xa += 20 * 14;
		}
		if (kb_IsDown(kb_KeyLeft) && CursorX > 0) {
			redraw = 1;
			delay(100);
			CursorX = CursorX - 16;
			xa--;
		}
		if (kb_IsDown(kb_KeyRight) && CursorX < 304) {
			redraw = 1;
			delay(100);
			CursorX = CursorX + 16;
			xa++;
		}
		
		if (kb_IsDown(kb_Key4) && roomX > 1) {
			redraw = 1;
			delay(100);
			roomX--;
			room -= 20;
			xa -= 20;
		}
		if (kb_IsDown(kb_Key6) && roomX < 14) {
			redraw = 1;
			delay(100);
			roomX++;
			room += 20;
			xa += 20;
		}
		if (kb_IsDown(kb_Key8) && roomY > 1) {
			redraw = 1;
			delay(100);
			roomY--;
			room -= 4200;
			xa -= 4200;
		}
		if (kb_IsDown(kb_Key2) && roomY < 14) {
			redraw = 1;
			delay(100);
			roomY++;
			room += 4200;
			xa += 4200;
		}
		
		if (kb_IsDown(kb_Key2nd)) {
			delay(100);
			wholeMap[xa] = Type;
		}
		if (kb_IsDown(kb_KeyAlpha)) {
			delay(160);
			Type = Type + 1;
		}
			if (Type > 12)Type = 0;

			if (kb_IsDown(kb_KeyClear)) {
				exit = 1;
				ti_CloseAll();
				//start = ((totalRooms - 1) * 300); 
				//If you want to copy to the same position in the first array, you can use `memcpy(&screenMap[start], &wholeMap[start], (end - start) * sizeof wholeMap[0]);`
				//for (xb = start; xb < start + 300; xb++) {
				//	memcpy(&screenMap[xb], &wholeMap[xb], 1);
				//}
				appvar = ti_Open("SrvMap00", "w");
				ti_Write(wholeMap, sizeof(wholeMap), 1, appvar);
				ti_SetArchiveStatus(1, appvar);
				ti_CloseAll();
				gfx_End();
				return;
			}

			if kb_IsDown(kb_KeyYequ) {
				//Future File Menu...
			}
			if kb_IsDown(kb_KeyWindow) {
				//Map Editor Tools Menu...
				y = 140;
				i = y;
				for (OldY = 0; OldY < 15; OldY++) {
					for (OldX = 0; OldX < 20; OldX++) {
						gfx_Sprite(grass, OldX * 16, OldY * 16);
					}
				}
				for (OldY = 140; OldY < 200; OldY += 20) {
					for (OldX = 60; OldX < 244; OldX += 16) {
						gfx_Sprite(wood, OldX, OldY);
					}
				}
				option = 0;
				while (option == 0) {
					kb_Scan();
					if (redraw != 0) {
						redraw = 0;
						/* redraw only the one button that needs it */
						for (xb = 60; xb < 244; xb += 16) {
							gfx_Sprite(wood, xb, i);
						}
						/* button text */
						gfx_PrintStringXY("Fill Room", 118, 142);
						gfx_PrintStringXY("Option", 118, 162);
						gfx_PrintStringXY("Back to Editor", 108, 182);
						gfx_SetColor(2);
						gfx_Rectangle(60, y, 192, 16);
						gfx_Rectangle(61, y + 1, 190, 14);
					}
					i = y;
					if (kb_IsDown(kb_KeyUp) && y > 140) {
						delay(150);
						redraw = 1;
						y = y - 20;
					}
					if (kb_IsDown(kb_KeyDown) && y < 180) {
						delay(150);
						redraw = 1;
						y = y + 20;
					}
					if (kb_IsDown(kb_Key2nd) && (y = 140)) option = 1;
					if (kb_IsDown(kb_Key2nd) && (y = 160)) option = 2;
					if (kb_IsDown(kb_Key2nd) && (y = 180)) option = 3;
		
				}
				if (option = 1) {
					for (OldY = 0; OldY < 15; OldY++) {
						for (OldX = 0; OldX < 20; OldX++) {
							gfx_Sprite(wood, OldX * 16, OldY * 16);
						}
					}
					for (OldY = 100; OldY < 200; OldY += 20) {
						for (OldX = 60; OldX < 244; OldX += 16) {
							gfx_Sprite(stone, OldX, OldY);
						}
					}

					option = 0;
					while (!kb_IsDown(kb_Key2nd)) {
						kb_Scan();
						gfx_ScaledSprite_NoClip(sprites[option], 64, 104, 2, 2);
						if (option < 0) option = 11;
						if (option >11) option = 0;
						if (kb_IsDown(kb_KeyLeft)) option--;
						if (kb_IsDown(kb_KeyRight)) option++;
					}

				}
				redraw = 1;

			}

			if (redraw == 1) {
				drawScreen();
			}

	}
	gfx_End();

}


/* loading appvars… */
void createVars(void) {
	ti_var_t appvar;
	ti_CloseAll();
	appvar = ti_Open("SrvMap00", "r");

	if (!appvar) {
		ti_CloseAll();
		appvar = ti_Open("SrvMap00", "w");
		ti_Write(wholeMap, sizeof(wholeMap), 1, appvar);   //+300
		ti_SetArchiveStatus(1, appvar);
		ti_CloseAll();
	}
	

	if (appvar) {
		ti_CloseAll();
		appvar = ti_Open("SrvMap00", "r");
		ti_Read(wholeMap, ti_GetSize(appvar), 1, appvar);
		ti_CloseAll();
		xb = 0;
		gfx_SetColor(255);
		drawScreen();
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