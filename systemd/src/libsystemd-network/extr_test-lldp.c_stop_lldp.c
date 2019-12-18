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
typedef  int /*<<< orphan*/  sd_lldp ;

/* Variables and functions */
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int sd_lldp_detach_event (int /*<<< orphan*/ *) ; 
 int sd_lldp_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_lldp_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_fd ; 

__attribute__((used)) static int stop_lldp(sd_lldp *lldp) {
        int r;

        r = sd_lldp_stop(lldp);
        if (r < 0)
                return r;

        r = sd_lldp_detach_event(lldp);
        if (r < 0)
                return r;

        sd_lldp_unref(lldp);
        safe_close(test_fd[1]);

        return 0;
}