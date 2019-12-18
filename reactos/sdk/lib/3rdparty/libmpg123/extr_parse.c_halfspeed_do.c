#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ halfspeed; } ;
struct TYPE_6__ {unsigned char* wordpointer; int lay; TYPE_1__ p; scalar_t__ halfphase; int /*<<< orphan*/  crc; scalar_t__ error_protection; int /*<<< orphan*/  ssize; int /*<<< orphan*/  ssave; scalar_t__ bsbuf; scalar_t__ bitindex; int /*<<< orphan*/  to_ignore; int /*<<< orphan*/  to_decode; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  getbits (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int halfspeed_do(mpg123_handle *fr)
{
	/* Speed-down hack: Play it again, Sam (the frame, I mean). */
	if (fr->p.halfspeed) 
	{
		if(fr->halfphase) /* repeat last frame */
		{
			debug("repeat!");
			fr->to_decode = fr->to_ignore = TRUE;
			--fr->halfphase;
			fr->bitindex = 0;
			fr->wordpointer = (unsigned char *) fr->bsbuf;
			if(fr->lay == 3) memcpy (fr->bsbuf, fr->ssave, fr->ssize);
			if(fr->error_protection) fr->crc = getbits(fr, 16); /* skip crc */
			return 1;
		}
		else
		{
			fr->halfphase = fr->p.halfspeed - 1;
		}
	}
	return 0;
}