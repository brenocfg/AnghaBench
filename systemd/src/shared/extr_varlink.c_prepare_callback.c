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
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_7__ {int /*<<< orphan*/  time_event_source; int /*<<< orphan*/  io_event_source; } ;
typedef  TYPE_1__ sd_event_source ;
typedef  TYPE_1__ Varlink ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EVENT_OFF ; 
 int /*<<< orphan*/  SD_EVENT_ON ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_event_source_set_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_io_events (int /*<<< orphan*/ ,int) ; 
 int sd_event_source_set_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int varlink_get_events (TYPE_1__*) ; 
 int varlink_get_timeout (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prepare_callback(sd_event_source *s, void *userdata) {
        Varlink *v = userdata;
        int r, e;
        usec_t until;

        assert(s);
        assert(v);

        e = varlink_get_events(v);
        if (e < 0)
                return e;

        r = sd_event_source_set_io_events(v->io_event_source, e);
        if (r < 0)
                return r;

        r = varlink_get_timeout(v, &until);
        if (r < 0)
                return r;
        if (r > 0) {
                r = sd_event_source_set_time(v->time_event_source, until);
                if (r < 0)
                        return r;
        }

        r = sd_event_source_set_enabled(v->time_event_source, r > 0 ? SD_EVENT_ON : SD_EVENT_OFF);
        if (r < 0)
                return r;

        return 1;
}