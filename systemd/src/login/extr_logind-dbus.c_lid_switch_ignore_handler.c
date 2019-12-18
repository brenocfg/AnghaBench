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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  lid_switch_ignore_event_source; } ;
typedef  TYPE_1__ sd_event_source ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lid_switch_ignore_handler(sd_event_source *e, uint64_t usec, void *userdata) {
        Manager *m = userdata;

        assert(e);
        assert(m);

        m->lid_switch_ignore_event_source = sd_event_source_unref(m->lid_switch_ignore_event_source);
        return 0;
}