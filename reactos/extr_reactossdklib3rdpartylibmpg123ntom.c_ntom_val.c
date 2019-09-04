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
typedef  int off_t ;
struct TYPE_3__ {int spf; int ntom_step; } ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 int NTOM_MUL ; 

unsigned long ntom_val(mpg123_handle *fr, off_t frame)
{
	off_t ntm;
#ifdef SAFE_NTOM /* Carry out the loop, without the threatening integer overflow. */
	off_t f;
	ntm = NTOM_MUL>>1; /* for frame 0 */
	for(f=0; f<frame; ++f)   /* for frame > 0 */
	{
		ntm += fr->spf*fr->ntom_step;
		ntm -= (ntm/NTOM_MUL)*NTOM_MUL;
	}
#else /* Just make one computation with overall sample offset. */
	ntm  = (NTOM_MUL>>1) + fr->spf*frame*fr->ntom_step;
	ntm -= (ntm/NTOM_MUL)*NTOM_MUL;
#endif
	return (unsigned long) ntm;
}