#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lldp; int /*<<< orphan*/  mac; TYPE_1__* network; int /*<<< orphan*/  ifindex; } ;
struct TYPE_6__ {scalar_t__ lldp_mode; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 scalar_t__ LLDP_MODE_ROUTERS_ONLY ; 
 int /*<<< orphan*/  SD_LLDP_SYSTEM_CAPABILITIES_ALL ; 
 int /*<<< orphan*/  SD_LLDP_SYSTEM_CAPABILITIES_ALL_ROUTERS ; 
 int link_update_lldp (TYPE_2__*) ; 
 int /*<<< orphan*/  lldp_handler ; 
 int sd_lldp_attach_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_lldp_match_capabilities (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_lldp_new (int /*<<< orphan*/ *) ; 
 int sd_lldp_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int sd_lldp_set_filter_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_lldp_set_ifindex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int link_lldp_rx_configure(Link *link) {
        int r;

        r = sd_lldp_new(&link->lldp);
        if (r < 0)
                return r;

        r = sd_lldp_set_ifindex(link->lldp, link->ifindex);
        if (r < 0)
                return r;

        r = sd_lldp_match_capabilities(link->lldp,
                                       link->network->lldp_mode == LLDP_MODE_ROUTERS_ONLY ?
                                       SD_LLDP_SYSTEM_CAPABILITIES_ALL_ROUTERS :
                                       SD_LLDP_SYSTEM_CAPABILITIES_ALL);
        if (r < 0)
                return r;

        r = sd_lldp_set_filter_address(link->lldp, &link->mac);
        if (r < 0)
                return r;

        r = sd_lldp_attach_event(link->lldp, NULL, 0);
        if (r < 0)
                return r;

        r = sd_lldp_set_callback(link->lldp, lldp_handler, link);
        if (r < 0)
                return r;

        r = link_update_lldp(link);
        if (r < 0)
                return r;

        return 0;
}