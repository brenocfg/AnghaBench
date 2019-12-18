#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
struct TYPE_3__ {int /*<<< orphan*/  monotonic; int /*<<< orphan*/  realtime; } ;
typedef  TYPE_1__ dual_timestamp ;
typedef  int /*<<< orphan*/  Seat ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int seat_get_idle_hint (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int property_get_idle_since_hint(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Seat *s = userdata;
        dual_timestamp t;
        uint64_t u;
        int r;

        assert(bus);
        assert(reply);
        assert(s);

        r = seat_get_idle_hint(s, &t);
        if (r < 0)
                return r;

        u = streq(property, "IdleSinceHint") ? t.realtime : t.monotonic;

        return sd_bus_message_append(reply, "t", u);
}