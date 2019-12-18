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
struct TYPE_3__ {int length; int* glyph; int blippos; } ;
typedef  TYPE_1__ MATRIX_COLUMN ;
typedef  int /*<<< orphan*/  MATRIX ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int GLYPH ;

/* Variables and functions */
 int /*<<< orphan*/  DrawGlyph (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int GLYPH_HEIGHT ; 
 int GLYPH_REDRAW ; 
 int GlyphIntensity (int) ; 
 int MAX_INTENSITY ; 

void RedrawMatrixColumn(MATRIX_COLUMN *col, MATRIX *matrix, HDC hdc, int xpos)
{
	int y;

	// loop down the length of the column redrawing only what needs doing
	for(y = 0; y < col->length; y++)
	{
		GLYPH glyph = col->glyph[y];

		// does this glyph (character) need to be redrawn?
		if(glyph & GLYPH_REDRAW)
		{
			if((y == col->blippos+0 || y == col->blippos+1 ||
				y == col->blippos+8 || y == col->blippos+9) &&
				GlyphIntensity(glyph) >= MAX_INTENSITY-1)
				glyph |= MAX_INTENSITY << 8;

			DrawGlyph(matrix, hdc, xpos, y * GLYPH_HEIGHT, glyph);

			// clear redraw state
			col->glyph[y] &= ~GLYPH_REDRAW;
		}
	}
}