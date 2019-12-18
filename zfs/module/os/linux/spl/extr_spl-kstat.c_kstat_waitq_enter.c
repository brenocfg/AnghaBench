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
typedef  int ulong_t ;
struct TYPE_3__ {int wlastupdate; int wlentime; int wtime; int /*<<< orphan*/  wcnt; } ;
typedef  TYPE_1__ kstat_io_t ;
typedef  int hrtime_t ;

/* Variables and functions */
 int gethrtime () ; 

void
kstat_waitq_enter(kstat_io_t *kiop)
{
	hrtime_t new, delta;
	ulong_t wcnt;

	new = gethrtime();
	delta = new - kiop->wlastupdate;
	kiop->wlastupdate = new;
	wcnt = kiop->wcnt++;
	if (wcnt != 0) {
		kiop->wlentime += delta * wcnt;
		kiop->wtime += delta;
	}
}