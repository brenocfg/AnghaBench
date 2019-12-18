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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_lldp ;
typedef  int /*<<< orphan*/  sd_event_source ;

/* Variables and functions */
 int lldp_make_space (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lldp_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int log_lldp_errno (int,char*) ; 

__attribute__((used)) static int on_timer_event(sd_event_source *s, uint64_t usec, void *userdata) {
        sd_lldp *lldp = userdata;
        int r;

        r = lldp_make_space(lldp, 0);
        if (r < 0)
                return log_lldp_errno(r, "Failed to make space: %m");

        r = lldp_start_timer(lldp, NULL);
        if (r < 0)
                return log_lldp_errno(r, "Failed to restart timer: %m");

        return 0;
}