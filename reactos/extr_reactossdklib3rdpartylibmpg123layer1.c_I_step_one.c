#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int stereo; int jsbound; } ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 int SBLIMIT ; 
 scalar_t__ check_balloc (TYPE_1__*,unsigned int*,unsigned int*) ; 
 void* getbits (TYPE_1__*,int) ; 

__attribute__((used)) static int I_step_one(unsigned int balloc[], unsigned int scale_index[2][SBLIMIT],mpg123_handle *fr)
{
	unsigned int *ba=balloc;
	unsigned int *sca = (unsigned int *) scale_index;

	if(fr->stereo == 2)
	{
		int i;
		int jsbound = fr->jsbound;
		for(i=0;i<jsbound;i++)
		{
			*ba++ = getbits(fr, 4);
			*ba++ = getbits(fr, 4);
		}
		for(i=jsbound;i<SBLIMIT;i++) *ba++ = getbits(fr, 4);

		if(check_balloc(fr, balloc, ba)) return -1;

		ba = balloc;

		for(i=0;i<jsbound;i++)
		{
			if ((*ba++))
				*sca++ = getbits(fr, 6);
			if ((*ba++))
				*sca++ = getbits(fr, 6);
		}
		for (i=jsbound;i<SBLIMIT;i++)
		if((*ba++))
		{
			*sca++ =  getbits(fr, 6);
			*sca++ =  getbits(fr, 6);
		}
	}
	else
	{
		int i;
		for(i=0;i<SBLIMIT;i++) *ba++ = getbits(fr, 4);

		if(check_balloc(fr, balloc, ba)) return -1;

		ba = balloc;
		for (i=0;i<SBLIMIT;i++)
		if ((*ba++))
		*sca++ = getbits(fr, 6);
	}

	return 0;
}