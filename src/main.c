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
void editor(void);
void drawScreen(void);
void addRoom(void);
void scanForBuildings(void);


	static gfx_sprite_t* sprites[16] = { dirt, grass, stone, wood, wood2, water, lava, netherrack, fireball, traptile1, traptile2, sailcloth, door, wall_brick, roof, sword };
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
	static uint24_t TypeB;
    //buildings[0] = count on screen, buildings[1] = building 1 pos in map data, building[2] = building 2 pos in map data, and so on...
    static uint24_t buildings[21] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	static uint24_t buildingData[6000] = {0};


void main(void) {
	gfx_Begin();
	gfx_SetPalette(mypalette, sizeof_mypalette, 0);
	for (xa = 0; xa < sizeof(wholeMap); xa++) {
		wholeMap[xa] = 0;
	}
	screen = 1;
	createVars();
	start();
	editor();
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
	gfx_SetDrawBuffer();
	gfx_FillScreen(255);
	CursorX = 0;
	CursorY = 0;
	Type = 0;
	xa = 0;
	redraw = 1;
	room = 1;
	roomX = 1;
	roomY = 1;
}

void editor(void) {
	uint8_t start;
	uint8_t end;
	int timer = 0, timer2 = 0;
	while (1) {
		kb_Scan();
		timer++;

		if (timer > 20) {
			timer = 0;
			timer2 = (timer2 == 0);
		}
			if (timer2 == 0) {
				gfx_SetColor(255);
				gfx_FillRectangle(CursorX, CursorY, 16, 16);
				gfx_SetColor(210);
				gfx_FillRectangle(CursorX + 6, CursorY + 6, 4, 4);
			}else{
				gfx_Sprite(sprites[Type], CursorX, CursorY);
			}

		if (kb_IsDown(kb_KeyStat)) {
			while (kb_IsDown(kb_KeyStat)) {
				kb_Scan();
				gfx_SetColor(10);
				gfx_FillRectangle(10, 10, 170, 30);
				gfx_PrintStringXY("Position in Map Data:", 12, 12);
				gfx_SetTextXY(12,22);
				gfx_PrintInt(xa, 1);
				gfx_BlitBuffer();
			}
			drawScreen();
		}

			gfx_BlitBuffer();

		if (kb_IsDown(kb_KeyUp) && CursorY > 0) {
			redraw = 1;
			gfx_Sprite(sprites[Type], CursorX, CursorY);
			delay(100);
			CursorY = CursorY - 16;
			xa -= 20 * 14;
		}
		if (kb_IsDown(kb_KeyDown) && CursorY < 224) {
			redraw = 1;
			gfx_Sprite(sprites[Type], CursorX, CursorY);
			delay(100);
			CursorY = CursorY + 16;
			xa += 20 * 14;
		}
		if (kb_IsDown(kb_KeyLeft) && CursorX > 0) {
			redraw = 1;
			gfx_Sprite(sprites[Type], CursorX, CursorY);
			delay(100);
			CursorX = CursorX - 16;
			xa--;
		}
		if (kb_IsDown(kb_KeyRight) && CursorX < 304) {
			redraw = 1;
			gfx_Sprite(sprites[Type], CursorX, CursorY);
			delay(100);
			CursorX = CursorX + 16;
			xa++;
		}
		
		if (kb_IsDown(kb_Key4) && roomX > 1) {
			redraw = 1;
			gfx_Sprite(sprites[Type], CursorX, CursorY);
			delay(100);
			roomX--;
			room -= 20;
			xa -= 20;
		}
		if (kb_IsDown(kb_Key6) && roomX < 14) {
			redraw = 1;
			gfx_Sprite(sprites[Type], CursorX, CursorY);
			delay(100);
			roomX++;
			room += 20;
			xa += 20;
		}
		if (kb_IsDown(kb_Key8) && roomY > 1) {
			redraw = 1;
			gfx_Sprite(sprites[Type], CursorX, CursorY);
			delay(100);
			roomY--;
			room -= 4200;
			xa -= 4200;
		}
		if (kb_IsDown(kb_Key2) && roomY < 14) {
			redraw = 1;
			gfx_Sprite(sprites[Type], CursorX, CursorY);
			delay(100);
			roomY++;
			room += 4200;
			xa += 4200;
		}
/*  I wouldn't try this... It's too buggy...
		if ((kb_IsDown(kb_KeyYequ)) && (wholeMap[xa] = 12)) {
			gfx_FillScreen(20);
			y = 20;
			x = 0;
			while (!(kb_IsDown(kb_KeyEnter))) {
				kb_Scan();
				if (x != y) {
					gfx_SetColor(15);
					gfx_PrintStringXY("House/Building Options:", 5, 5);
					for (i = 20; i < 60; i += 20) {
						gfx_FillRectangle(20, i, 110, 14);
					}
					gfx_PrintStringXY("Design a room...", 22, 22);
					gfx_PrintStringXY("Back...", 22, 42);	
					x = y;
				}
				gfx_SetColor(3);
				gfx_Rectangle(20, y, 110, 14);
				gfx_Rectangle(21, y + 1, 108, 12);
				if (kb_IsDown(kb_KeyUp)) y = 20;
				if (kb_IsDown(kb_KeyDown)) y = 40;
				if (kb_IsDown(kb_KeyClear)) drawScreen();
				gfx_BlitBuffer();
			}
				if (y = 20) {
					scanForBuildings();
					addRoom();
				}
				if (y = 40)drawScreen();
		}
		*/

		if (kb_IsDown(kb_Key2nd)) {
			delay(100);
			wholeMap[xa] = Type;
		}
		if (kb_IsDown(kb_KeyAlpha)) {
			delay(160);
			gfx_Sprite(sprites[Type], CursorX, CursorY);
			Type++;
		}
			if (Type > 15)Type = 0;

			if (kb_IsDown(kb_KeyClear)) {
				ti_CloseAll();
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
				gfx_SetDrawBuffer();
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
					gfx_BlitBuffer();
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


		gfx_BlitBuffer();
	}
	gfx_End();

}



/* loading appvars� */
void createVars(void) {
	ti_var_t appvar;
	ti_CloseAll();
	appvar = ti_Open("SrvMap00", "r");

	if (!appvar) {
		ti_CloseAll();
		appvar = ti_Open("SrvMap00", "w");
		ti_Write(wholeMap, sizeof(wholeMap), 1, appvar);
		ti_SetArchiveStatus(1, appvar);
		ti_CloseAll();
		appvar = ti_Open("SMapDATA", "w");
		ti_Write(buildings, sizeof(buildings), 1, appvar);
		ti_SetArchiveStatus(1, appvar);
		ti_CloseAll();
		appvar = ti_Open("SMapBDAT", "w");
		ti_Write(buildingData, sizeof(buildingData), 1, appvar);
		ti_SetArchiveStatus(1, appvar);
		ti_CloseAll();
	}
	

	if (appvar) {
		ti_CloseAll();
		appvar = ti_Open("SrvMap00", "r");
		ti_Read(wholeMap, ti_GetSize(appvar), 1, appvar);
		ti_CloseAll();
		appvar = ti_Open("SMapDATA", "r");
		ti_Read(buildings, ti_GetSize(appvar), 1, appvar);
		ti_CloseAll();
		appvar = ti_Open("SMapBDAT", "r");
		ti_Read(buildingData, ti_GetSize(appvar), 1, appvar);
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

void scanForBuildings() {
	for (i = 0; i < sizeof(wholeMap); i++) {
		if ((wholeMap[i] = 12) && (xa == i)) {
			buildings[0] = buildings[0] + 1;
			buildings[buildings[0]] = i;
		}
	}
}

void addRoom(void) {
	int xx, yy, posB;
	x = 0;
	y = 0;
	pos = buildings[0] * 300;
	TypeB = 0;
	redraw = 1;
	while (!(kb_IsDown(kb_KeyClear))) {
		kb_Scan();
		if (redraw == 1) {
			posB = buildings[0];
			for (xx = 0; xx < 20; xx++) {
				for (yy = 0; yy < 15; yy++) {
					gfx_Sprite(sprites[buildingData[posB * 300]], xx * 16, yy * 16);
				}
			}
		}


			gfx_SetColor(255);
			gfx_FillRectangle(x, y, 16, 16);
			gfx_SetColor(210);
			gfx_FillRectangle(x + 6, y + 6, 4, 4);
			

		if (Type < 15)gfx_Sprite(sprites[Type], x, y);

		if (kb_IsDown(kb_KeyUp) && y > 0) {
			redraw = 1;
			delay(100);
			y -= 16;
			pos -= 20 * 300;
		}
		if (kb_IsDown(kb_KeyDown) && y < 224) {
			redraw = 1;
			delay(100);
			y += 16;
			pos += 20 * 300;
		}
		if (kb_IsDown(kb_KeyLeft) && x > 0) {
			redraw = 1;
			delay(100);
			x -= 16;
			pos--;
		}
		if (kb_IsDown(kb_KeyRight) && x < 304) {
			redraw = 1;
			delay(100);
			x += 16;
			pos++;
		}
		if (kb_IsDown(kb_Key2nd)) {
			redraw = 1;
			buildingData[pos] = Type;
		}
		if (kb_IsDown(kb_KeyAlpha)) {
			delay(160);
			Type++;
		}
		
		if (Type > 14)Type = 0;

	gfx_BlitBuffer();

	}
	ti_Delete("SrvMap00");
	ti_Delete("SMapBDAT");
	createVars();
	start();
}