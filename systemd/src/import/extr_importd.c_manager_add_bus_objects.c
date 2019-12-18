#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  event; int /*<<< orphan*/  bus; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  manager_vtable ; 
 int sd_bus_add_fallback_vtable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_bus_add_node_enumerator (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_bus_add_object_vtable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_bus_attach_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_bus_request_name_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transfer_node_enumerator ; 
 int /*<<< orphan*/  transfer_object_find ; 
 int /*<<< orphan*/  transfer_vtable ; 

__attribute__((used)) static int manager_add_bus_objects(Manager *m) {
        int r;

        assert(m);

        r = sd_bus_add_object_vtable(m->bus, NULL, "/org/freedesktop/import1", "org.freedesktop.import1.Manager", manager_vtable, m);
        if (r < 0)
                return log_error_errno(r, "Failed to register object: %m");

        r = sd_bus_add_fallback_vtable(m->bus, NULL, "/org/freedesktop/import1/transfer", "org.freedesktop.import1.Transfer", transfer_vtable, transfer_object_find, m);
        if (r < 0)
                return log_error_errno(r, "Failed to register object: %m");

        r = sd_bus_add_node_enumerator(m->bus, NULL, "/org/freedesktop/import1/transfer", transfer_node_enumerator, m);
        if (r < 0)
                return log_error_errno(r, "Failed to add transfer enumerator: %m");

        r = sd_bus_request_name_async(m->bus, NULL, "org.freedesktop.import1", 0, NULL, NULL);
        if (r < 0)
                return log_error_errno(r, "Failed to request name: %m");

        r = sd_bus_attach_event(m->bus, m->event, 0);
        if (r < 0)
                return log_error_errno(r, "Failed to attach bus to event loop: %m");

        return 0;
}