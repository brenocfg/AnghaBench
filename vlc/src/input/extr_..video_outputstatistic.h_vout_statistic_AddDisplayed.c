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
struct TYPE_3__ {int /*<<< orphan*/  displayed; } ;
typedef  TYPE_1__ vout_statistic_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fetch_add_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

__attribute__((used)) static inline void vout_statistic_AddDisplayed(vout_statistic_t *stat,
                                               int displayed)
{
    atomic_fetch_add_explicit(&stat->displayed, displayed,
                              memory_order_relaxed);
}