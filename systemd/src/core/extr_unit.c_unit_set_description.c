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
struct TYPE_5__ {int /*<<< orphan*/  description; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  empty_to_null (char const*) ; 
 int free_and_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_add_to_dbus_queue (TYPE_1__*) ; 

int unit_set_description(Unit *u, const char *description) {
        int r;

        assert(u);

        r = free_and_strdup(&u->description, empty_to_null(description));
        if (r < 0)
                return r;
        if (r > 0)
                unit_add_to_dbus_queue(u);

        return 0;
}