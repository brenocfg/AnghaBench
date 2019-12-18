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
typedef  scalar_t__ usec_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_5__ {int /*<<< orphan*/  timer_event_source; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_get_description (int /*<<< orphan*/ ,char const**) ; 
 int sd_event_source_get_time (int /*<<< orphan*/ *,scalar_t__*) ; 
 int sd_event_source_set_time (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strna (char const*) ; 

__attribute__((used)) static void service_extend_event_source_timeout(Service *s, sd_event_source *source, usec_t extended) {
        usec_t current;
        int r;

        assert(s);

        /* Extends the specified event source timer to at least the specified time, unless it is already later
         * anyway. */

        if (!source)
                return;

        r = sd_event_source_get_time(source, &current);
        if (r < 0) {
                const char *desc;
                (void) sd_event_source_get_description(s->timer_event_source, &desc);
                log_unit_warning_errno(UNIT(s), r, "Failed to retrieve timeout time for event source '%s', ignoring: %m", strna(desc));
                return;
        }

        if (current >= extended) /* Current timeout is already longer, ignore this. */
                return;

        r = sd_event_source_set_time(source, extended);
        if (r < 0) {
                const char *desc;
                (void) sd_event_source_get_description(s->timer_event_source, &desc);
                log_unit_warning_errno(UNIT(s), r, "Failed to set timeout time for even source '%s', ignoring %m", strna(desc));
        }
}