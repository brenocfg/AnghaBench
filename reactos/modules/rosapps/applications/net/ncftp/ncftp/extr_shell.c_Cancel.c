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
 int /*<<< orphan*/  gCancelJmp ; 
 int gGotSig ; 
 scalar_t__ gMayCancelJmp ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 

void
Cancel(int sigNum)
{
	if (gMayCancelJmp != 0) {
		gGotSig = sigNum;
		gMayCancelJmp = 0;
#ifdef HAVE_SIGSETJMP
		siglongjmp(gCancelJmp, 1);
#else	/* HAVE_SIGSETJMP */
		longjmp(gCancelJmp, 1);
#endif	/* HAVE_SIGSETJMP */
	}
}