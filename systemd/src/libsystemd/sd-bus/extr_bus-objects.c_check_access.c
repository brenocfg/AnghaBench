#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct vtable_member {int /*<<< orphan*/  member; int /*<<< orphan*/  interface; TYPE_3__* parent; TYPE_1__* vtable; scalar_t__ trusted; } ;
typedef  struct vtable_member sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  struct vtable_member sd_bus ;
struct TYPE_6__ {TYPE_2__* vtable; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 scalar_t__ CAPABILITY_SHIFT (int) ; 
 scalar_t__ CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  SD_BUS_ERROR_ACCESS_DENIED ; 
 int SD_BUS_VTABLE_UNPRIVILEGED ; 
 int /*<<< orphan*/  assert (struct vtable_member*) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_bus_query_sender_privilege (struct vtable_member*,scalar_t__) ; 

__attribute__((used)) static int check_access(sd_bus *bus, sd_bus_message *m, struct vtable_member *c, sd_bus_error *error) {
        uint64_t cap;
        int r;

        assert(bus);
        assert(m);
        assert(c);

        /* If the entire bus is trusted let's grant access */
        if (bus->trusted)
                return 0;

        /* If the member is marked UNPRIVILEGED let's grant access */
        if (c->vtable->flags & SD_BUS_VTABLE_UNPRIVILEGED)
                return 0;

        /* Check have the caller has the requested capability
         * set. Note that the flags value contains the capability
         * number plus one, which we need to subtract here. We do this
         * so that we have 0 as special value for "default
         * capability". */
        cap = CAPABILITY_SHIFT(c->vtable->flags);
        if (cap == 0)
                cap = CAPABILITY_SHIFT(c->parent->vtable[0].flags);
        if (cap == 0)
                cap = CAP_SYS_ADMIN;
        else
                cap--;

        r = sd_bus_query_sender_privilege(m, cap);
        if (r < 0)
                return r;
        if (r > 0)
                return 0;

        return sd_bus_error_setf(error, SD_BUS_ERROR_ACCESS_DENIED, "Access to %s.%s() not permitted.", c->interface, c->member);
}