#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* glyph; int length; } ;
typedef  TYPE_1__ MATRIX_COLUMN ;

/* Variables and functions */
 int GLYPH_REDRAW ; 
 int GlyphIntensity (int) ; 
 int MAX_INTENSITY ; 
 int NUM_GLYPHS ; 
 int crc_rand () ; 

void RandomMatrixColumn(MATRIX_COLUMN *col)
{
	int i, y;

	for(i = 1, y = 0; i < 16; i++)
	{
		// find a run
		while(GlyphIntensity(col->glyph[y]) < MAX_INTENSITY-1 && y < col->length)
			y++;

		if(y >= col->length)
			break;

		col->glyph[y]  = (col->glyph[y] & 0xff00) | (crc_rand() % NUM_GLYPHS);
		col->glyph[y] |= GLYPH_REDRAW;

		y += crc_rand() % 10;
	}
}