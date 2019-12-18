#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_4__ {scalar_t__ spf; scalar_t__ ntom_step; } ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 scalar_t__ NTOM_MUL ; 
 scalar_t__ ntom_val (TYPE_1__*,int /*<<< orphan*/ ) ; 

off_t ntom_ins2outs(mpg123_handle *fr, off_t ins)
{
	off_t soff = 0;
	off_t ntm = ntom_val(fr,0);
#ifdef SAFE_NTOM
	{
		off_t block = fr->spf;
		if(ins <= 0) return 0;
		do
		{
			off_t nowblock = ins > block ? block : ins;
			ntm  += nowblock*fr->ntom_step;
			soff += ntm/NTOM_MUL;
			ntm  -= (ntm/NTOM_MUL)*NTOM_MUL;
			ins -= nowblock;
		} while(ins > 0);
	}
#else
	/* Beware of overflows: when off_t is 32bits, the multiplication blows too easily.
	   Of course, it blows for 64bits, too, in theory, but that's for _really_ large files. */
	soff = ((off_t)ntm + (off_t)ins*(off_t)fr->ntom_step)/(off_t)NTOM_MUL;
#endif
	return soff;
}