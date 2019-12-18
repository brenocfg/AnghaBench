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
struct mevent {int dummy; } ;
struct kevent {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  EVF_READ ; 
 int MEVENT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int kevent (int,struct kevent*,int,struct kevent*,int,int /*<<< orphan*/ *) ; 
 int kqueue () ; 
 struct mevent* mevent_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mevent_build (int,struct kevent*) ; 
 int /*<<< orphan*/  mevent_handle (struct kevent*,int) ; 
 int /*<<< orphan*/  mevent_pipe_read ; 
 int /*<<< orphan*/ * mevent_pipefd ; 
 int /*<<< orphan*/  mevent_set_name () ; 
 int /*<<< orphan*/  mevent_tid ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pipe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 

__attribute__ ((noreturn)) void
mevent_dispatch(void)
{
	struct kevent changelist[MEVENT_MAX];
	struct kevent eventlist[MEVENT_MAX];
	struct mevent *pipev;
	int mfd;
	int numev;
	int ret;

	mevent_tid = pthread_self();
	mevent_set_name();

	mfd = kqueue();
	assert(mfd > 0);

	/*
	 * Open the pipe that will be used for other threads to force
	 * the blocking kqueue call to exit by writing to it. Set the
	 * descriptor to non-blocking.
	 */
	ret = pipe(mevent_pipefd);
	if (ret < 0) {
		perror("pipe");
		exit(0);
	}

	/*
	 * Add internal event handler for the pipe write fd
	 */
	pipev = mevent_add(mevent_pipefd[0], EVF_READ, mevent_pipe_read, NULL);
	assert(pipev != NULL);

	for (;;) {
		/*
		 * Build changelist if required.
		 * XXX the changelist can be put into the blocking call
		 * to eliminate the extra syscall. Currently better for
		 * debug.
		 */
		numev = mevent_build(mfd, changelist);
		if (numev) {
			ret = kevent(mfd, changelist, numev, NULL, 0, NULL);
			if (ret == -1) {
				perror("Error return from kevent change");
			}
		}

		/*
		 * Block awaiting events
		 */
		ret = kevent(mfd, NULL, 0, eventlist, MEVENT_MAX, NULL);
		if (ret == -1 && errno != EINTR) {
			perror("Error return from kevent monitor");
		}
		
		/*
		 * Handle reported events
		 */
		mevent_handle(eventlist, ret);
	}			
}