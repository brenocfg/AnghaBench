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
struct TYPE_5__ {int /*<<< orphan*/  description; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  log_unit_debug_errno (TYPE_1__*,int,char*) ; 
 int unit_load_fragment_and_dropin (TYPE_1__*,int) ; 
 int unit_name_to_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int device_load(Unit *u) {
        int r;

        r = unit_load_fragment_and_dropin(u, false);
        if (r < 0)
                return r;

        if (!u->description) {
                /* Generate a description based on the path, to be used until the
                   device is initialized properly */
                r = unit_name_to_path(u->id, &u->description);
                if (r < 0)
                        log_unit_debug_errno(u, r, "Failed to unescape name: %m");
        }

        return 0;
}