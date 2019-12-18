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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int SD_EVENT_FINISHED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int manager_dispatch_delayed (TYPE_1__*,int) ; 
 int /*<<< orphan*/  manager_gc (TYPE_1__*,int) ; 
 int sd_event_get_state (int /*<<< orphan*/ ) ; 
 int sd_event_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int manager_run(Manager *m) {
        int r;

        assert(m);

        for (;;) {
                r = sd_event_get_state(m->event);
                if (r < 0)
                        return r;
                if (r == SD_EVENT_FINISHED)
                        return 0;

                manager_gc(m, true);

                r = manager_dispatch_delayed(m, false);
                if (r < 0)
                        return r;
                if (r > 0)
                        continue;

                r = sd_event_run(m->event, (uint64_t) -1);
                if (r < 0)
                        return r;
        }
}