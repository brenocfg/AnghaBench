#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  network_monitor_event_source; int /*<<< orphan*/  event; int /*<<< orphan*/  network_monitor; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  on_network_event ; 
 int sd_event_add_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int sd_network_monitor_get_events (int /*<<< orphan*/ ) ; 
 int sd_network_monitor_get_fd (int /*<<< orphan*/ ) ; 
 int sd_network_monitor_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int manager_network_monitor_listen(Manager *m) {
        int r, fd, events;

        assert(m);

        r = sd_network_monitor_new(&m->network_monitor, NULL);
        if (r < 0)
                return r;

        fd = sd_network_monitor_get_fd(m->network_monitor);
        if (fd < 0)
                return fd;

        events = sd_network_monitor_get_events(m->network_monitor);
        if (events < 0)
                return events;

        r = sd_event_add_io(m->event, &m->network_monitor_event_source,
                            fd, events, &on_network_event, m);
        if (r < 0)
                return r;

        return 0;
}