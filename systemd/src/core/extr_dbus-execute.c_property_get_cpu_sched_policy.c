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
struct TYPE_8__ {scalar_t__ cpu_sched_policy; scalar_t__ cpu_sched_set; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  scalar_t__ int32_t ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 scalar_t__ SCHED_OTHER ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ sched_getscheduler (int /*<<< orphan*/ ) ; 
 int sd_bus_message_append (TYPE_1__*,char*,scalar_t__) ; 

__attribute__((used)) static int property_get_cpu_sched_policy(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        ExecContext *c = userdata;
        int32_t n;

        assert(bus);
        assert(reply);
        assert(c);

        if (c->cpu_sched_set)
                n = c->cpu_sched_policy;
        else {
                n = sched_getscheduler(0);
                if (n < 0)
                        n = SCHED_OTHER;
        }

        return sd_bus_message_append(reply, "i", n);
}