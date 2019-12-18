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
struct TYPE_6__ {int /*<<< orphan*/  userdata; int /*<<< orphan*/  state; int /*<<< orphan*/  (* ready_callback ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ has_failed; } ;
typedef  TYPE_1__ BusWaitForUnits ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_WAIT_FAILURE ; 
 int /*<<< orphan*/  BUS_WAIT_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_wait_for_units_is_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bus_wait_for_units_check_ready(BusWaitForUnits *d) {
        assert(d);

        if (!bus_wait_for_units_is_ready(d))
                return;

        d->state = d->has_failed ? BUS_WAIT_FAILURE : BUS_WAIT_SUCCESS;

        if (d->ready_callback)
                d->ready_callback(d, d->state, d->userdata);
}