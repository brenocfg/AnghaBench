#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long tv_sec; long tv_usec; } ;
struct TYPE_6__ {TYPE_1__ timeout; } ;
typedef  TYPE_2__* SelectSetPtr ;
typedef  int /*<<< orphan*/  SelectSet ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__* const,int /*<<< orphan*/ ,int) ; 

void
SelectSetInit(SelectSetPtr const ssp, const double timeout)
{
	double i;
	long l;

	/* Inititalize SelectSet, which will clear the fd_set, the
	 * timeval, and the maxfd and numfds to 0.
	 */
	memset(ssp, 0, sizeof(SelectSet));
	l = (long) timeout;
	i = (double) l;
	ssp->timeout.tv_sec = l;
	ssp->timeout.tv_usec = (long) ((timeout - i) * 1000000.0);
}