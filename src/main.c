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
void start(void);

void start(void) {
	uint8_t Xrooms;
	uint8_t Yrooms;
	uint8_t Xsize;
	uint8_t Ysize;
	uint16_t mapL;
	uint16_t mapR;
	char* string = "Map X Size: ";
	char buffer[10];
	//os_GetStringInput(char* "Map X Size: ", buffer, size_t 10);
	os_GetStringInput(string, buffer, _sizeof(buffer));
	Xrooms = 20;
	Yrooms = 20;
	Xsize = Xrooms * 20;
	Ysize = Yrooms * 15;
	uint mapL[Xsize][Ysize];

	return;
}