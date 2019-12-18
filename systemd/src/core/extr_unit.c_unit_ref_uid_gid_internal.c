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
 scalar_t__ gid_is_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ uid_is_valid (int /*<<< orphan*/ ) ; 
 int unit_ref_gid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int unit_ref_uid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unit_unref_uid (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int unit_ref_uid_gid_internal(Unit *u, uid_t uid, gid_t gid, bool clean_ipc) {
        int r = 0, q = 0;

        assert(u);

        /* Reference both a UID and a GID in one go. Either references both, or neither. */

        if (uid_is_valid(uid)) {
                r = unit_ref_uid(u, uid, clean_ipc);
                if (r < 0)
                        return r;
        }

        if (gid_is_valid(gid)) {
                q = unit_ref_gid(u, gid, clean_ipc);
                if (q < 0) {
                        if (r > 0)
                                unit_unref_uid(u, false);

                        return q;
                }
        }

        return r > 0 || q > 0;
}