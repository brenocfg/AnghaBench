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
 int CALLOUT_FLAG_ABSOLUTE ; 
 int /*<<< orphan*/  __cv_timedwait_hires (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gethrtime () ; 

__attribute__((used)) static clock_t
cv_timedwait_hires_common(kcondvar_t *cvp, kmutex_t *mp, hrtime_t tim,
    hrtime_t res, int flag, int state)
{
	if (!(flag & CALLOUT_FLAG_ABSOLUTE))
		tim += gethrtime();

	return (__cv_timedwait_hires(cvp, mp, tim, res, state));
}