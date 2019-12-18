#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  lldp; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_1__*,char*) ; 
 int log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int sd_lldp_start (int /*<<< orphan*/ ) ; 
 int sd_lldp_stop (int /*<<< orphan*/ ) ; 

int link_update_lldp(Link *link) {
        int r;

        assert(link);

        if (!link->lldp)
                return 0;

        if (link->flags & IFF_UP) {
                r = sd_lldp_start(link->lldp);
                if (r < 0)
                        return log_link_warning_errno(link, r, "Failed to start LLDP: %m");
                if (r > 0)
                        log_link_debug(link, "Started LLDP.");
        } else {
                r = sd_lldp_stop(link->lldp);
                if (r < 0)
                        return log_link_warning_errno(link, r, "Failed to stop LLDP: %m");
                if (r > 0)
                        log_link_debug(link, "Stopped LLDP.");
        }

        return r;
}