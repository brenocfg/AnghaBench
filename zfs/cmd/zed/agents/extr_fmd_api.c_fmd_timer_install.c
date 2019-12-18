#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* sival_ptr; } ;
struct sigevent {TYPE_2__ sigev_value; int /*<<< orphan*/ * sigev_notify_attributes; int /*<<< orphan*/  sigev_notify_function; int /*<<< orphan*/  sigev_notify; } ;
struct TYPE_9__ {int tv_sec; int tv_nsec; } ;
struct TYPE_7__ {int tv_sec; int tv_nsec; } ;
struct itimerspec {TYPE_3__ it_value; TYPE_1__ it_interval; } ;
typedef  int hrtime_t ;
struct TYPE_10__ {int /*<<< orphan*/  ft_tid; int /*<<< orphan*/ * ft_hdl; void* ft_arg; } ;
typedef  TYPE_4__ fmd_timer_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
typedef  int /*<<< orphan*/  fmd_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  FMD_SLEEP ; 
 int /*<<< orphan*/  SIGEV_THREAD ; 
 int /*<<< orphan*/  _timer_notify ; 
 TYPE_4__* fmd_hdl_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_create (int /*<<< orphan*/ ,struct sigevent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

fmd_timer_t *
fmd_timer_install(fmd_hdl_t *hdl, void *arg, fmd_event_t *ep, hrtime_t delta)
{
	struct sigevent sev;
	struct itimerspec its;
	fmd_timer_t *ftp;

	ftp = fmd_hdl_alloc(hdl, sizeof (fmd_timer_t), FMD_SLEEP);
	ftp->ft_arg = arg;
	ftp->ft_hdl = hdl;

	its.it_value.tv_sec = delta / 1000000000;
	its.it_value.tv_nsec = delta % 1000000000;
	its.it_interval.tv_sec = its.it_value.tv_sec;
	its.it_interval.tv_nsec = its.it_value.tv_nsec;

	sev.sigev_notify = SIGEV_THREAD;
	sev.sigev_notify_function = _timer_notify;
	sev.sigev_notify_attributes = NULL;
	sev.sigev_value.sival_ptr = ftp;

	timer_create(CLOCK_REALTIME, &sev, &ftp->ft_tid);
	timer_settime(ftp->ft_tid, 0, &its, NULL);

	fmd_hdl_debug(hdl, "installing timer for %d secs (%p)",
	    (int)its.it_value.tv_sec, ftp->ft_tid);

	return (ftp);
}