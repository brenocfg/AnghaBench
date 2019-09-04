#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GLYPH ;

/* Variables and functions */
 int /*<<< orphan*/  GLYPH_REDRAW ; 

void RedrawBlip(GLYPH *glypharr, int blippos)
{
	glypharr[blippos+0] |= GLYPH_REDRAW;
	glypharr[blippos+1] |= GLYPH_REDRAW;
	glypharr[blippos+8] |= GLYPH_REDRAW;
	glypharr[blippos+9] |= GLYPH_REDRAW;
}