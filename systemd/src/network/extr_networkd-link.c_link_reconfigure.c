#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_1__* network; int /*<<< orphan*/  state; int /*<<< orphan*/  dhcp_server; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid; int /*<<< orphan*/  wlan_iftype; int /*<<< orphan*/  mac; int /*<<< orphan*/  ifname; int /*<<< orphan*/  sd_device; int /*<<< orphan*/  manager; } ;
struct TYPE_23__ {int /*<<< orphan*/  filename; scalar_t__ unmanaged; } ;
typedef  TYPE_1__ Network ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_STATE_INITIALIZED ; 
 int /*<<< orphan*/  LINK_STATE_LINGER ; 
 int /*<<< orphan*/  LINK_STATE_PENDING ; 
 int /*<<< orphan*/  LINK_STATE_UNMANAGED ; 
 int link_configure (TYPE_2__*) ; 
 int link_configure_duid (TYPE_2__*) ; 
 scalar_t__ link_dhcp4_server_enabled (TYPE_2__*) ; 
 int link_drop_config (TYPE_2__*) ; 
 int link_drop_foreign_config (TYPE_2__*) ; 
 int /*<<< orphan*/  link_enter_failed (TYPE_2__*) ; 
 int /*<<< orphan*/  link_enter_unmanaged (TYPE_2__*) ; 
 int /*<<< orphan*/  link_free_carrier_maps (TYPE_2__*) ; 
 int /*<<< orphan*/  link_free_engines (TYPE_2__*) ; 
 int link_new_carrier_maps (TYPE_2__*) ; 
 int /*<<< orphan*/  link_set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_state_to_string (int /*<<< orphan*/ ) ; 
 int link_stop_clients (TYPE_2__*,int) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_link_info (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int network_apply (TYPE_1__*,TYPE_2__*) ; 
 int network_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**) ; 
 TYPE_1__* network_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_dhcp_server_stop (int /*<<< orphan*/ ) ; 

int link_reconfigure(Link *link, bool force) {
        Network *network;
        int r;

        if (IN_SET(link->state, LINK_STATE_PENDING, LINK_STATE_LINGER))
                return 0;

        r = network_get(link->manager, link->sd_device, link->ifname,
                        &link->mac, link->wlan_iftype, link->ssid, &link->bssid, &network);
        if (r == -ENOENT) {
                link_enter_unmanaged(link);
                return 0;
        } else if (r == 0 && network->unmanaged) {
                link_enter_unmanaged(link);
                return 0;
        } else if (r < 0)
                return r;

        if (link->network == network && !force)
                return 0;

        log_link_info(link, "Re-configuring with %s", network->filename);

        /* Dropping old .network file */
        r = link_stop_clients(link, false);
        if (r < 0) {
                link_enter_failed(link);
                return r;
        }

        if (link_dhcp4_server_enabled(link))
                (void) sd_dhcp_server_stop(link->dhcp_server);

        r = link_drop_config(link);
        if (r < 0)
                return r;

        if (!IN_SET(link->state, LINK_STATE_UNMANAGED, LINK_STATE_PENDING)) {
                log_link_debug(link, "State is %s, dropping config", link_state_to_string(link->state));
                r = link_drop_foreign_config(link);
                if (r < 0)
                        return r;
        }

        link_free_carrier_maps(link);
        link_free_engines(link);
        link->network = network_unref(link->network);

        /* Then, apply new .network file */
        r = network_apply(network, link);
        if (r < 0)
                return r;

        r = link_new_carrier_maps(link);
        if (r < 0)
                return r;

        link_set_state(link, LINK_STATE_INITIALIZED);

        /* link_configure_duid() returns 0 if it requests product UUID. In that case,
         * link_configure() is called later asynchronously. */
        r = link_configure_duid(link);
        if (r <= 0)
                return r;

        r = link_configure(link);
        if (r < 0)
                return r;

        return 0;
}