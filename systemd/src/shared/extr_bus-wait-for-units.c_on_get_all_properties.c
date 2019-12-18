#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
struct TYPE_12__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ sd_bus_error ;
struct TYPE_13__ {int /*<<< orphan*/  userdata; int /*<<< orphan*/  bus_path; int /*<<< orphan*/  (* unit_callback ) (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;TYPE_3__* parent; } ;
typedef  TYPE_2__ WaitForItem ;
struct TYPE_14__ {int has_failed; TYPE_2__* current; } ;
typedef  TYPE_3__ BusWaitForUnits ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  bus_wait_for_units_check_ready (TYPE_3__*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,...) ; 
 int /*<<< orphan*/  sd_bus_error_get_errno (TYPE_1__*) ; 
 scalar_t__ sd_bus_error_is_set (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_item_free (TYPE_2__*) ; 
 int wait_for_item_parse_properties (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_get_all_properties(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        WaitForItem *item = userdata;
        int r;

        assert(item);

        if (sd_bus_error_is_set(error)) {
                BusWaitForUnits *d = item->parent;

                d->has_failed = true;

                log_debug_errno(sd_bus_error_get_errno(error), "GetAll() failed for %s: %s",
                                item->bus_path, error->message);

                d->current = item;
                item->unit_callback(d, item->bus_path, false, item->userdata);
                wait_for_item_free(item);

                bus_wait_for_units_check_ready(d);
                return 0;
        }

        r = wait_for_item_parse_properties(item, m);
        if (r < 0)
                log_debug_errno(r, "Failed to process GetAll method reply: %m");

        return 0;
}