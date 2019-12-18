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
struct sched_param {int /*<<< orphan*/  sched_priority; } ;
struct TYPE_8__ {int /*<<< orphan*/  cpu_sched_priority; scalar_t__ cpu_sched_set; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ sched_getparam (int /*<<< orphan*/ ,struct sched_param*) ; 
 int sd_bus_message_append (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int property_get_cpu_sched_priority(
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
                n = c->cpu_sched_priority;
        else {
                struct sched_param p = {};

                if (sched_getparam(0, &p) >= 0)
                        n = p.sched_priority;
                else
                        n = 0;
        }

        return sd_bus_message_append(reply, "i", n);
}