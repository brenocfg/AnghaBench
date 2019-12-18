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
typedef  int uint32 ;
struct timeval {int tv_sec; int tv_usec; } ;
struct async_iorequest {scalar_t__ fd; int major; int timeout; int itv_timeout; struct async_iorequest* next; int /*<<< orphan*/  partial_len; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_3__ {scalar_t__ min_timeout_fd; struct async_iorequest* iorequest; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
#define  IRP_MJ_DEVICE_CONTROL 130 
#define  IRP_MJ_READ 129 
#define  IRP_MJ_WRITE 128 
 int MAX (int,scalar_t__) ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  write (scalar_t__,char*,int /*<<< orphan*/ ) ; 

void
rdpdr_add_fds(RDPCLIENT * This, int *n, fd_set * rfds, fd_set * wfds, struct timeval *tv, BOOL * timeout)
{
	uint32 select_timeout = 0;	/* Timeout value to be used for select() (in millisecons). */
	struct async_iorequest *iorq;
	char c;

	iorq = This->iorequest;
	while (iorq != NULL)
	{
		if (iorq->fd != 0)
		{
			switch (iorq->major)
			{
				case IRP_MJ_READ:
					/* Is this FD valid? FDs will
					   be invalid when
					   reconnecting. FIXME: Real
					   support for reconnects. */

					FD_SET(iorq->fd, rfds);
					*n = MAX(*n, iorq->fd);

					/* Check if io request timeout is smaller than current (but not 0). */
					if (iorq->timeout
					    && (select_timeout == 0
						|| iorq->timeout < select_timeout))
					{
						/* Set new timeout */
						select_timeout = iorq->timeout;
						This->min_timeout_fd = iorq->fd;	/* Remember fd */
						tv->tv_sec = select_timeout / 1000;
						tv->tv_usec = (select_timeout % 1000) * 1000;
						*timeout = True;
						break;
					}
					if (iorq->itv_timeout && iorq->partial_len > 0
					    && (select_timeout == 0
						|| iorq->itv_timeout < select_timeout))
					{
						/* Set new timeout */
						select_timeout = iorq->itv_timeout;
						This->min_timeout_fd = iorq->fd;	/* Remember fd */
						tv->tv_sec = select_timeout / 1000;
						tv->tv_usec = (select_timeout % 1000) * 1000;
						*timeout = True;
						break;
					}
					break;

				case IRP_MJ_WRITE:
					/* FD still valid? See above. */
					if ((write(iorq->fd, &c, 0) != 0) && (errno == EBADF))
						break;

					FD_SET(iorq->fd, wfds);
					*n = MAX(*n, iorq->fd);
					break;

				case IRP_MJ_DEVICE_CONTROL:
					if (select_timeout > 5)
						select_timeout = 5;	/* serial event queue */
					break;

			}

		}

		iorq = iorq->next;
	}
}