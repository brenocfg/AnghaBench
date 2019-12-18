#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {scalar_t__ timer_slack_nsec; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 scalar_t__ NSEC_INFINITY ; 
 int /*<<< orphan*/  PR_GET_TIMERSLACK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ) ; 
 int sd_bus_message_append (TYPE_1__*,char*,scalar_t__) ; 

__attribute__((used)) static int property_get_timer_slack_nsec(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        ExecContext *c = userdata;
        uint64_t u;

        assert(bus);
        assert(reply);
        assert(c);

        if (c->timer_slack_nsec != NSEC_INFINITY)
                u = (uint64_t) c->timer_slack_nsec;
        else
                u = (uint64_t) prctl(PR_GET_TIMERSLACK);

        return sd_bus_message_append(reply, "t", u);
}