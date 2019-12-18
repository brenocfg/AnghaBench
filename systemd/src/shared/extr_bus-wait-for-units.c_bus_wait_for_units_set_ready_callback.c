#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bus_wait_for_units_ready_callback ;
struct TYPE_4__ {void* userdata; int /*<<< orphan*/  ready_callback; } ;
typedef  TYPE_1__ BusWaitForUnits ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void bus_wait_for_units_set_ready_callback(BusWaitForUnits *d, bus_wait_for_units_ready_callback callback, void *userdata) {
        assert(d);

        d->ready_callback = callback;
        d->userdata = userdata;
}