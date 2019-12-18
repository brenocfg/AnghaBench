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
typedef  int /*<<< orphan*/  kmutex_t ;
typedef  int /*<<< orphan*/  kcondvar_t ;
typedef  int /*<<< orphan*/  hrtime_t ;
typedef  int /*<<< orphan*/  clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  cv_timedwait_hires_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

clock_t
cv_timedwait_sig_hires(kcondvar_t *cvp, kmutex_t *mp, hrtime_t tim,
    hrtime_t res, int flag)
{
	return (cv_timedwait_hires_common(cvp, mp, tim, res, flag,
	    TASK_INTERRUPTIBLE));
}