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
struct TYPE_4__ {int /*<<< orphan*/  mount_monitor; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_error_errno (int,char*) ; 
 int mnt_monitor_next_change (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drain_libmount(Manager *m) {
        bool rescan = false;
        int r;

        assert(m);

        /* Drain all events and verify that the event is valid.
         *
         * Note that libmount also monitors /run/mount mkdir if the directory does not exist yet. The mkdir
         * may generate event which is irrelevant for us.
         *
         * error: r < 0; valid: r == 0, false positive: r == 1 */
        do {
                r = mnt_monitor_next_change(m->mount_monitor, NULL, NULL);
                if (r < 0)
                        return log_error_errno(r, "Failed to drain libmount events: %m");
                if (r == 0)
                        rescan = true;
        } while (r == 0);

        return rescan;
}