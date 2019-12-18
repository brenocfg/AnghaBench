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
typedef  int off_t ;
struct TYPE_4__ {int spf; int ntom_step; } ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 int NTOM_MUL ; 
 int ntom_val (TYPE_1__*,int /*<<< orphan*/ ) ; 

off_t ntom_frameoff(mpg123_handle *fr, off_t soff)
{
	off_t ioff = 0; /* frames or samples */
	off_t ntm = ntom_val(fr,0);
#ifdef SAFE_NTOM
	if(soff <= 0) return 0;
	for(ioff=0; 1; ++ioff)
	{
		ntm  += fr->spf*fr->ntom_step;
		if(ntm/NTOM_MUL > soff) break;
		soff -= ntm/NTOM_MUL;
		ntm  -= (ntm/NTOM_MUL)*NTOM_MUL;
	}
	return ioff;
#else
	ioff = (soff*(off_t)NTOM_MUL-ntm)/(off_t)fr->ntom_step;
	return ioff/(off_t)fr->spf;
#endif
}