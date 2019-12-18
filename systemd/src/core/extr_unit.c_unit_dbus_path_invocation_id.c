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
struct TYPE_4__ {int /*<<< orphan*/  invocation_id_string; int /*<<< orphan*/  invocation_id; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ sd_id128_is_null (int /*<<< orphan*/ ) ; 
 char* unit_dbus_path_from_name (int /*<<< orphan*/ ) ; 

char *unit_dbus_path_invocation_id(Unit *u) {
        assert(u);

        if (sd_id128_is_null(u->invocation_id))
                return NULL;

        return unit_dbus_path_from_name(u->invocation_id_string);
}