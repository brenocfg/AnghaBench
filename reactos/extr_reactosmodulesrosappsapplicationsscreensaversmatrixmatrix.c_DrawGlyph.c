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
struct TYPE_3__ {int /*<<< orphan*/  hdcBitmap; } ;
typedef  TYPE_1__ MATRIX ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int GLYPH ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int GLYPH_HEIGHT ; 
 int GLYPH_WIDTH ; 
 int GlyphIntensity (int) ; 
 int /*<<< orphan*/  SRCCOPY ; 

void DrawGlyph(MATRIX *matrix, HDC hdc, int xpos, int ypos, GLYPH glyph)
{
	int intensity = GlyphIntensity(glyph);
	int glyphidx  = glyph & 0xff;

	BitBlt(hdc, xpos, ypos, GLYPH_WIDTH, GLYPH_HEIGHT, matrix->hdcBitmap,
		glyphidx * GLYPH_WIDTH, intensity * GLYPH_HEIGHT, SRCCOPY);
}