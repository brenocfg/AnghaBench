#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int audit_fd; int /*<<< orphan*/  bus; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  audit_close (int) ; 
 int /*<<< orphan*/  sd_bus_flush_close_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_clear(Context *c) {
        assert(c);

        c->bus = sd_bus_flush_close_unref(c->bus);
#if HAVE_AUDIT
        if (c->audit_fd >= 0)
                audit_close(c->audit_fd);
        c->audit_fd = -1;
#endif
}