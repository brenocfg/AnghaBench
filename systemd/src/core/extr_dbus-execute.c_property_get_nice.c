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
struct TYPE_8__ {scalar_t__ nice; scalar_t__ nice_set; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  scalar_t__ int32_t ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ errno ; 
 scalar_t__ getpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_bus_message_append (TYPE_1__*,char*,scalar_t__) ; 

__attribute__((used)) static int property_get_nice(
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

        if (c->nice_set)
                n = c->nice;
        else {
                errno = 0;
                n = getpriority(PRIO_PROCESS, 0);
                if (errno > 0)
                        n = 0;
        }

        return sd_bus_message_append(reply, "i", n);
}