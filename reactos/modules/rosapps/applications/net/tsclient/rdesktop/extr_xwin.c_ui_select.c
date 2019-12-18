#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_9__ {int x_socket; scalar_t__ seamless_active; } ;
struct TYPE_10__ {int dsp_fd; scalar_t__ dsp_busy; TYPE_1__ xwin; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ False ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdpdr_add_fds (TYPE_2__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*,scalar_t__*) ; 
 int /*<<< orphan*/  rdpdr_check_fds (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  seamless_select_timeout (TYPE_2__*,struct timeval*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_check_timers (TYPE_2__*) ; 
 int /*<<< orphan*/  wave_out_play () ; 
 int /*<<< orphan*/  xwin_process_events (TYPE_2__*) ; 

int
ui_select(RDPCLIENT * This, int rdp_socket)
{
	int n;
	fd_set rfds, wfds;
	struct timeval tv;
	BOOL s_timeout = False;

	while (True)
	{
		n = (rdp_socket > This->xwin.x_socket) ? rdp_socket : This->xwin.x_socket;
		/* Process any events already waiting */
		if (!xwin_process_events(This))
			/* User quit */
			return 0;

		if (This->xwin.seamless_active)
			sw_check_timers(This);

		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		FD_SET(rdp_socket, &rfds);
		FD_SET(This->xwin.x_socket, &rfds);

#ifdef WITH_RDPSND
		/* FIXME: there should be an API for registering fds */
		if (This->dsp_busy)
		{
			FD_SET(This->dsp_fd, &wfds);
			n = (This->dsp_fd > n) ? This->dsp_fd : n;
		}
#endif
		/* default timeout */
		tv.tv_sec = 60;
		tv.tv_usec = 0;

		/* add redirection handles */
		rdpdr_add_fds(This, &n, &rfds, &wfds, &tv, &s_timeout);
		seamless_select_timeout(This, &tv);

		n++;

		switch (select(n, &rfds, &wfds, NULL, &tv))
		{
			case -1:
				error("select: %s\n", strerror(errno));

			case 0:
				/* Abort serial read calls */
				if (s_timeout)
					rdpdr_check_fds(This, &rfds, &wfds, (BOOL) True);
				continue;
		}

		rdpdr_check_fds(This, &rfds, &wfds, (BOOL) False);

		if (FD_ISSET(rdp_socket, &rfds))
			return 1;

#ifdef WITH_RDPSND
		if (This->dsp_busy && FD_ISSET(This->dsp_fd, &wfds))
			wave_out_play();
#endif
	}
}