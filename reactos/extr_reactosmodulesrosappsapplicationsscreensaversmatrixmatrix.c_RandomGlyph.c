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
typedef  int GLYPH ;

/* Variables and functions */
 int GLYPH_REDRAW ; 
 int NUM_GLYPHS ; 
 int crc_rand () ; 

GLYPH RandomGlyph(int intensity)
{
	return GLYPH_REDRAW | (intensity << 8) | (crc_rand() % NUM_GLYPHS);
}