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
void main(void);
void createVars(void);
void LoadMapChunk(void);
uint16_t LoadMapX;
uint16_t LoadMapY;
uint16_t xa;
uint16_t ya;



void main(void) {

	uint16_t CursorX;
	uint16_t CursorY;
	char screenMap[20*15];
	char wholeMap[((20*20)*(15*20))];
	int LoadMapX = 1;
	uint16_t x;
	uint16_t y;
	uint16_t OldLoadX;
	OldLoadX = LoadMapX;
	/* Load the map screen data from the whole map */
	for (y = 1; y < 15; y++) {
		for (x = 1; x < 20; x++) {
			screenMap[x] = wholeMap[LoadMapX];
			LoadMapX = LoadMapX + 1;
		}
		LoadMapX = LoadMapX + ((20*20) - 20);
	}
	LoadMapX = OldLoadX;
	/* Draw the screen */
	gfx_FillScreen(255);
	xa = 1;
	for (y = 1; y < 15; y++) {
		for (x = 1; x < 20; x++) {

			xa = xa + 1;
		}
	}

}



/*

void test(void) {

	uint8_t Xrooms;
	uint8_t Yrooms;
	uint8_t Xsize;
	uint8_t Ysize;
	uint16_t mapL;
	uint16_t mapR;
	uint16_t XsizeL;
	uint16_t XsizeR;
	const char* chars = "\0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0";
	uint8_t key, i = 0;
	char buffer[50];
	gfx_Begin();
	while ((key = os_GetCSC()) != sk_Enter) {
		if (chars[key]) {
			buffer[i++] = chars[key];
		}
	}
	gfx_PrintStringXY(buffer, 1, 1);
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

void createVarsTEST(void) {
	char mapL[XsizeL];

	return;
};

*/