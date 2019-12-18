#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  clean_result; int /*<<< orphan*/  active_state; int /*<<< orphan*/  bus_path; int /*<<< orphan*/  slot_get_all; int /*<<< orphan*/  slot_properties_changed; TYPE_1__* parent; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ WaitForItem ;
struct TYPE_8__ {TYPE_2__* current; int /*<<< orphan*/  items; scalar_t__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_WAIT_REFFED ; 
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_2__* hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int sd_bus_call_method_async (scalar_t__,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_slot_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WaitForItem *wait_for_item_free(WaitForItem *item) {
        int r;

        if (!item)
                return NULL;

        if (item->parent) {
                if (FLAGS_SET(item->flags, BUS_WAIT_REFFED) && item->bus_path && item->parent->bus) {
                        r = sd_bus_call_method_async(
                                        item->parent->bus,
                                        NULL,
                                        "org.freedesktop.systemd1",
                                        item->bus_path,
                                        "org.freedesktop.systemd1.Unit",
                                        "Unref",
                                        NULL,
                                        NULL,
                                        NULL);
                        if (r < 0)
                                log_debug_errno(r, "Failed to drop reference to unit %s, ignoring: %m", item->bus_path);
                }

                assert_se(hashmap_remove(item->parent->items, item->bus_path) == item);

                if (item->parent->current == item)
                        item->parent->current = NULL;
        }

        sd_bus_slot_unref(item->slot_properties_changed);
        sd_bus_slot_unref(item->slot_get_all);

        free(item->bus_path);
        free(item->active_state);
        free(item->clean_result);

        return mfree(item);
}