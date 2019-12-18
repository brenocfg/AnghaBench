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

/* Variables and functions */
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  WaitForChar (long) ; 
 scalar_t__ mzthreads_allowed () ; 
 int /*<<< orphan*/  mzvim_check_threads () ; 
 long p_mzq ; 

void
mch_delay(
    long    msec,
    int	    ignoreinput)
{
#ifdef FEAT_GUI_W32
    Sleep((int)msec);	    /* never wait for input */
#else /* Console */
    if (ignoreinput)
# ifdef FEAT_MZSCHEME
	if (mzthreads_allowed() && p_mzq > 0 && msec > p_mzq)
	{
	    int towait = p_mzq;

	    /* if msec is large enough, wait by portions in p_mzq */
	    while (msec > 0)
	    {
		mzvim_check_threads();
		if (msec < towait)
		    towait = msec;
		Sleep(towait);
		msec -= towait;
	    }
	}
	else
# endif
	    Sleep((int)msec);
    else
	WaitForChar(msec);
#endif
}