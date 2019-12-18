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
struct TYPE_6__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  event; int /*<<< orphan*/  resolve; int /*<<< orphan*/  network_monitor; int /*<<< orphan*/  network_event_source; int /*<<< orphan*/  event_retry; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  SERVER_FALLBACK ; 
 int /*<<< orphan*/  SERVER_LINK ; 
 int /*<<< orphan*/  SERVER_SYSTEM ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_flush_server_names (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_flush_close_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_network_monitor_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_resolve_unref (int /*<<< orphan*/ ) ; 

void manager_free(Manager *m) {
        if (!m)
                return;

        manager_disconnect(m);
        manager_flush_server_names(m, SERVER_SYSTEM);
        manager_flush_server_names(m, SERVER_LINK);
        manager_flush_server_names(m, SERVER_FALLBACK);

        sd_event_source_unref(m->event_retry);

        sd_event_source_unref(m->network_event_source);
        sd_network_monitor_unref(m->network_monitor);

        sd_resolve_unref(m->resolve);
        sd_event_unref(m->event);

        sd_bus_flush_close_unref(m->bus);

        free(m);
}