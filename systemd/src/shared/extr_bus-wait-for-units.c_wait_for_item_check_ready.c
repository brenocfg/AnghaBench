#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ job_id; int /*<<< orphan*/  userdata; int /*<<< orphan*/  bus_path; int /*<<< orphan*/  (* unit_callback ) (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;scalar_t__ active_state; int /*<<< orphan*/  flags; scalar_t__ clean_result; TYPE_2__* parent; } ;
typedef  TYPE_1__ WaitForItem ;
struct TYPE_10__ {int has_failed; TYPE_1__* current; } ;
typedef  TYPE_2__ BusWaitForUnits ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_WAIT_FOR_INACTIVE ; 
 int /*<<< orphan*/  BUS_WAIT_FOR_MAINTENANCE_END ; 
 int /*<<< orphan*/  BUS_WAIT_NO_JOB ; 
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (TYPE_2__*) ; 
 int /*<<< orphan*/  bus_wait_for_units_check_ready (TYPE_2__*) ; 
 scalar_t__ streq (scalar_t__,char*) ; 
 scalar_t__ streq_ptr (scalar_t__,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_item_free (TYPE_1__*) ; 

__attribute__((used)) static void wait_for_item_check_ready(WaitForItem *item) {
        BusWaitForUnits *d;

        assert(item);
        assert_se(d = item->parent);

        if (FLAGS_SET(item->flags, BUS_WAIT_FOR_MAINTENANCE_END)) {

                if (item->clean_result && !streq(item->clean_result, "success"))
                        d->has_failed = true;

                if (!item->active_state || streq(item->active_state, "maintenance"))
                        return;
        }

        if (FLAGS_SET(item->flags, BUS_WAIT_NO_JOB) && item->job_id != 0)
                return;

        if (FLAGS_SET(item->flags, BUS_WAIT_FOR_INACTIVE)) {

                if (streq_ptr(item->active_state, "failed"))
                        d->has_failed = true;
                else if (!streq_ptr(item->active_state, "inactive"))
                        return;
        }

        if (item->unit_callback) {
                d->current = item;
                item->unit_callback(d, item->bus_path, true, item->userdata);
        }

        wait_for_item_free(item);

        bus_wait_for_units_check_ready(d);
}