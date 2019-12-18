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
 int bb_got_signal ; 
 scalar_t__ wait (int*) ; 
 scalar_t__ wait_any_nohang (int*) ; 

void check_errors_in_children(int signo)
{
	int status;

	if (!signo) {
		/* block waiting for any child */
		if (wait(&status) < 0)
//FIXME: check EINTR?
			return; /* probably there are no children */
		goto check_status;
	}

	/* Wait for any child without blocking */
	for (;;) {
		if (wait_any_nohang(&status) < 0)
//FIXME: check EINTR?
			/* wait failed?! I'm confused... */
			return;
 check_status:
		/*if (WIFEXITED(status) && WEXITSTATUS(status) == 0)*/
		/* On Linux, the above can be checked simply as: */
		if (status == 0)
			/* this child exited with 0 */
			continue;
		/* Cannot happen:
		if (!WIFSIGNALED(status) && !WIFEXITED(status)) ???;
		 */
		bb_got_signal = 1;
	}
}