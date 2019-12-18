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
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int link_carrier_gained (int /*<<< orphan*/ *) ; 
 int link_carrier_lost (int /*<<< orphan*/ *) ; 
 scalar_t__ link_has_carrier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_link_info (int /*<<< orphan*/ *,char*) ; 

int link_carrier_reset(Link *link) {
        int r;

        assert(link);

        if (link_has_carrier(link)) {
                r = link_carrier_lost(link);
                if (r < 0)
                        return r;

                r = link_carrier_gained(link);
                if (r < 0)
                        return r;

                log_link_info(link, "Reset carrier");
        }

        return 0;
}