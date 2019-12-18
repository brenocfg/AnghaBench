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
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_3__ {int maxFd; int /*<<< orphan*/  clientHead; int /*<<< orphan*/  allFds; } ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int defer_time ; 
 int /*<<< orphan*/  rfbProcessEvents (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 TYPE_1__* server ; 

int
ui_select(int rdpSocket)
{
	fd_set fds;
	struct timeval tv;
	int n, m = server->maxFd;

	if (rdpSocket > m)
		m = rdpSocket;
	while (1)
	{
		fds = server->allFds;
		FD_SET(rdpSocket, &fds);
		tv.tv_sec = defer_time / 1000;
		tv.tv_usec = (defer_time % 1000) * 1000;
		n = select(m + 1, &fds, NULL, NULL, &tv);
		rfbProcessEvents(server, 0);
		/* if client is gone, close connection */
		if (!server->clientHead)
			close(rdpSocket);
		if (FD_ISSET(rdpSocket, &fds))
			return 1;
	}
	return 0;
}