#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cancelXfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  gBackToTopJmp ; 
 int gCancelCtrl ; 
 TYPE_1__ gConn ; 
 int gGotSig ; 
 scalar_t__ gMayBackToTopJmp ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  siglongjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
XferCanceller(int sigNum)
{
	gGotSig = sigNum;
	if (gConn.cancelXfer > 0) {
#if defined(WIN32) || defined(_WINDOWS)
		signal(SIGINT, SIG_DFL);
#else
		/* User already tried it once, they
		 * must think it's locked up.
		 *
		 * Jump back to the top, and
		 * close down the current session.
		 */
		gCancelCtrl = 1;
		if (gMayBackToTopJmp > 0) {
#ifdef HAVE_SIGSETJMP
			siglongjmp(gBackToTopJmp, 1);
#else	/* HAVE_SIGSETJMP */
			longjmp(gBackToTopJmp, 1);
#endif	/* HAVE_SIGSETJMP */
		}
#endif
	}
	gConn.cancelXfer++;
}