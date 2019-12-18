#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ tsd_t ;

/* Variables and functions */
 scalar_t__ malloc_slow ; 
 scalar_t__ tsd_nominal (TYPE_1__*) ; 
 scalar_t__ tsd_reentrancy_level_get (TYPE_1__*) ; 
 int /*<<< orphan*/  tsd_state_nominal ; 
 int /*<<< orphan*/  tsd_state_nominal_slow ; 
 int /*<<< orphan*/  tsd_tcache_enabled_get (TYPE_1__*) ; 

void
tsd_slow_update(tsd_t *tsd) {
	if (tsd_nominal(tsd)) {
		if (malloc_slow || !tsd_tcache_enabled_get(tsd) ||
		    tsd_reentrancy_level_get(tsd) > 0) {
			tsd->state = tsd_state_nominal_slow;
		} else {
			tsd->state = tsd_state_nominal;
		}
	}
}