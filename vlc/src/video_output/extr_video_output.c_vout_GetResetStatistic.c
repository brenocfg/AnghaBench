#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
struct TYPE_4__ {int /*<<< orphan*/  statistic; int /*<<< orphan*/  dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vout_statistic_GetReset (int /*<<< orphan*/ *,unsigned int*,unsigned int*) ; 

void vout_GetResetStatistic(vout_thread_t *vout, unsigned *restrict displayed,
                            unsigned *restrict lost)
{
    assert(!vout->p->dummy);
    vout_statistic_GetReset( &vout->p->statistic, displayed, lost );
}