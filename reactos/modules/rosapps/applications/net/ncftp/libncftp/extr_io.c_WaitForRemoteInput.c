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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int fd_set ;
struct TYPE_4__ {int xferTimeout; int dataSocket; int cancelXfer; int stalled; int dataTimedOut; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  FD_SET (int,int*) ; 
 int /*<<< orphan*/  FD_ZERO (int*) ; 
 int /*<<< orphan*/  FTPUpdateIOTimer (TYPE_1__* const) ; 
 int SELECT_TYPE_ARG234 ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int select (int,int,int /*<<< orphan*/ *,int,struct timeval*) ; 

__attribute__((used)) static int
WaitForRemoteInput(const FTPCIPtr cip)
{
	fd_set ss, ss2;
	struct timeval tv;
	int result;
	int fd;
	int wsecs;
	int xferTimeout;
	int ocancelXfer;

	xferTimeout = cip->xferTimeout;
	if (xferTimeout < 1)
		return (1);

	fd = cip->dataSocket;
	if (fd < 0)
		return (1);

	ocancelXfer = cip->cancelXfer;
	wsecs = 0;
	cip->stalled = 0;

	while ((xferTimeout <= 0) || (wsecs < xferTimeout)) {
		if ((cip->cancelXfer != 0) && (ocancelXfer == 0)) {
			/* leave cip->stalled -- could have been stalled and then canceled. */
			return (1);
		}
		FD_ZERO(&ss);
		FD_SET(fd, &ss);
		ss2 = ss;
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		result = select(fd + 1, SELECT_TYPE_ARG234 &ss, NULL, SELECT_TYPE_ARG234 &ss2, &tv);
		if (result == 1) {
			/* ready */
			cip->stalled = 0;
			return (1);
		} else if (result < 0) {
			if (result != EINTR) {
				perror("select");
				cip->stalled = 0;
				return (1);
			}
		} else {
			wsecs++;
			cip->stalled = wsecs;
		}
		FTPUpdateIOTimer(cip);
	}

#if !defined(NO_SIGNALS)
	/* Shouldn't get here -- alarm() should have
	 * went off by now.
	 */
	(void) kill(getpid(), SIGALRM);
#endif	/* NO_SIGNALS */

	cip->dataTimedOut = 1;
	return (0);	/* timed-out */
}