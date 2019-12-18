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
struct TYPE_3__ {scalar_t__ started; scalar_t__ countdown; int state; int length; scalar_t__ runlen; scalar_t__ blippos; scalar_t__ bliplen; int /*<<< orphan*/ * glyph; } ;
typedef  TYPE_1__ MATRIX_COLUMN ;
typedef  int /*<<< orphan*/  GLYPH ;

/* Variables and functions */
 int DENSITY ; 
 int DENSITY_MAX ; 
 int DENSITY_MIN ; 
 int /*<<< orphan*/  DarkenGlyph (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int GlyphIntensity (int /*<<< orphan*/ ) ; 
 int MAX_INTENSITY ; 
 int /*<<< orphan*/  RandomGlyph (int) ; 
 int /*<<< orphan*/  RedrawBlip (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int crc_rand () ; 

void ScrollMatrixColumn(MATRIX_COLUMN *col)
{
	int y;
	GLYPH lastglyph = 0;
	GLYPH thisglyph;

	// wait until we are allowed to scroll
	if(col->started == FALSE)
	{
		if(--col->countdown <= 0)
			col->started = TRUE;

		return;
	}

	// "seed" the glyph-run
	lastglyph = col->state ? (GLYPH)0 : (GLYPH)(MAX_INTENSITY << 8);

	//
	// loop over the entire length of the column, looking for changes
	// in intensity/darkness. This change signifies the start/end
	// of a run of glyphs.
	//
	for(y = 0; y < col->length; y++)
	{
		thisglyph = col->glyph[y];

		// bottom-most part of "run". Insert a new character (glyph)
		// at the end to lengthen the run down the screen..gives the
		// impression that the run is "falling" down the screen
		if(GlyphIntensity(thisglyph) < GlyphIntensity(lastglyph) &&
			GlyphIntensity(thisglyph) == 0)
		{
			col->glyph[y] = RandomGlyph(MAX_INTENSITY - 1);
			y++;
		}
		// top-most part of "run". Delete a character off the top by
		// darkening the glyph until it eventually disappears (turns black).
		// this gives the effect that the run as dropped downwards
		else if(GlyphIntensity(thisglyph) > GlyphIntensity(lastglyph))
		{
			col->glyph[y] = DarkenGlyph(thisglyph);

			// if we've just darkened the last bit, skip on so
			// the whole run doesn't go dark
			if(GlyphIntensity(thisglyph) == MAX_INTENSITY - 1)
				y++;
		}

		lastglyph = col->glyph[y];
	}

	// change state from blanks <-> runs when the current run as expired
	if(--col->runlen <= 0)
	{
		if(col->state ^= 1)
			col->runlen = crc_rand() % (3 * DENSITY/2) + DENSITY_MIN;
		else
			col->runlen = crc_rand() % (DENSITY_MAX+1-DENSITY) + (DENSITY_MIN*2);
	}

	//
	// make a "blip" run down this column at double-speed
	//

	// mark current blip as redraw so it gets "erased"
	if(col->blippos >= 0 && col->blippos < col->length)
		RedrawBlip(col->glyph, col->blippos);

	// advance down screen at double-speed
	col->blippos += 2;

	// if the blip gets to the end of a run, start it again (for a random
	// length so that the blips never get synched together)
	if(col->blippos >= col->bliplen)
	{
		col->bliplen = col->length + crc_rand() % 50;
		col->blippos = 0;
	}

	// now redraw blip at new position
	if(col->blippos >= 0 && col->blippos < col->length)
		RedrawBlip(col->glyph, col->blippos);

}