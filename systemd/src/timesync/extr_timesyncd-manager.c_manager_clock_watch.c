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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_5__ {int jumped; int poll_resync; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  manager_clock_watch_setup (TYPE_1__*) ; 
 int manager_send_request (TYPE_1__*) ; 

__attribute__((used)) static int manager_clock_watch(sd_event_source *source, int fd, uint32_t revents, void *userdata) {
        Manager *m = userdata;

        assert(m);

        /* rearm timer */
        manager_clock_watch_setup(m);

        /* skip our own jumps */
        if (m->jumped) {
                m->jumped = false;
                return 0;
        }

        /* resync */
        log_debug("System time changed. Resyncing.");
        m->poll_resync = true;

        return manager_send_request(m);
}