#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union sigval {TYPE_2__* sival_ptr; } ;
struct itimerspec {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ft_arg; int /*<<< orphan*/  ft_tid; int /*<<< orphan*/ * ft_hdl; } ;
typedef  TYPE_2__ fmd_timer_t ;
struct TYPE_8__ {TYPE_1__* mod_info; } ;
typedef  TYPE_3__ fmd_module_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* fmdo_timeout ) (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ fmd_hdl_ops_t ;
struct TYPE_6__ {TYPE_4__* fmdi_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct itimerspec*,int) ; 
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_timer_notify(union sigval sv)
{
	fmd_timer_t *ftp = sv.sival_ptr;
	fmd_hdl_t *hdl = ftp->ft_hdl;
	fmd_module_t *mp = (fmd_module_t *)hdl;
	const fmd_hdl_ops_t *ops = mp->mod_info->fmdi_ops;
	struct itimerspec its;

	fmd_hdl_debug(hdl, "timer fired (%p)", ftp->ft_tid);

	/* disarm the timer */
	bzero(&its, sizeof (struct itimerspec));
	timer_settime(ftp->ft_tid, 0, &its, NULL);

	/* Note that the fmdo_timeout can remove this timer */
	if (ops->fmdo_timeout != NULL)
		ops->fmdo_timeout(hdl, ftp, ftp->ft_arg);
}