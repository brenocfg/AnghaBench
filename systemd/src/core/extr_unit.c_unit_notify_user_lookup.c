#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_add_to_dbus_queue (int /*<<< orphan*/ *) ; 
 int unit_ref_uid_gid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void unit_notify_user_lookup(Unit *u, uid_t uid, gid_t gid) {
        int r;

        assert(u);

        /* This is invoked whenever one of the forked off processes let's us know the UID/GID its user name/group names
         * resolved to. We keep track of which UID/GID is currently assigned in order to be able to destroy its IPC
         * objects when no service references the UID/GID anymore. */

        r = unit_ref_uid_gid(u, uid, gid);
        if (r > 0)
                unit_add_to_dbus_queue(u);
}