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
typedef  int /*<<< orphan*/  sd_bus ;
struct TYPE_5__ {int /*<<< orphan*/  private_listen_fd; int /*<<< orphan*/  private_listen_event_source; int /*<<< orphan*/  private_buses; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_bus (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * set_steal_first (int /*<<< orphan*/ ) ; 

void bus_done_private(Manager *m) {
        sd_bus *b;

        assert(m);

        while ((b = set_steal_first(m->private_buses)))
                destroy_bus(m, &b);

        m->private_buses = set_free(m->private_buses);

        m->private_listen_event_source = sd_event_source_unref(m->private_listen_event_source);
        m->private_listen_fd = safe_close(m->private_listen_fd);
}