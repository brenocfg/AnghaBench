#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_dhcp_client ;
struct TYPE_15__ {int /*<<< orphan*/  keep_configuration; struct TYPE_15__* network; int /*<<< orphan*/  dhcp_lease; int /*<<< orphan*/  dhcp_send_release; struct TYPE_15__* ipv4ll; int /*<<< orphan*/  state; struct TYPE_15__* manager; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_FAMILY_FALLBACK_IPV4 ; 
 int ENOMSG ; 
 int /*<<< orphan*/  FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEEP_CONFIGURATION_DHCP ; 
 int /*<<< orphan*/  LINK_STATE_FAILED ; 
 int /*<<< orphan*/  LINK_STATE_LINGER ; 
#define  SD_DHCP_CLIENT_EVENT_EXPIRED 133 
#define  SD_DHCP_CLIENT_EVENT_IP_ACQUIRE 132 
#define  SD_DHCP_CLIENT_EVENT_IP_CHANGE 131 
#define  SD_DHCP_CLIENT_EVENT_RENEW 130 
#define  SD_DHCP_CLIENT_EVENT_SELECTING 129 
#define  SD_DHCP_CLIENT_EVENT_STOP 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dhcp_lease_acquired (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dhcp_lease_ip_change (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dhcp_lease_lost (TYPE_1__*) ; 
 int dhcp_lease_renew (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dhcp_server_is_black_listed (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_enter_failed (TYPE_1__*) ; 
 int /*<<< orphan*/  link_ipv4ll_enabled (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  log_link_notice (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  log_link_warning (TYPE_1__*,char*,int) ; 
 int log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  sd_dhcp_client_send_release (int /*<<< orphan*/ *) ; 
 int sd_ipv4ll_start (TYPE_1__*) ; 

__attribute__((used)) static int dhcp4_handler(sd_dhcp_client *client, int event, void *userdata) {
        Link *link = userdata;
        int r;

        assert(link);
        assert(link->network);
        assert(link->manager);

        if (IN_SET(link->state, LINK_STATE_FAILED, LINK_STATE_LINGER))
                return 0;

        switch (event) {
                case SD_DHCP_CLIENT_EVENT_STOP:

                        if (link_ipv4ll_enabled(link, ADDRESS_FAMILY_FALLBACK_IPV4)) {
                                assert(link->ipv4ll);

                                log_link_debug(link, "DHCP client is stopped. Acquiring IPv4 link-local address");

                                r = sd_ipv4ll_start(link->ipv4ll);
                                if (r < 0)
                                        return log_link_warning_errno(link, r, "Could not acquire IPv4 link-local address: %m");
                        }

                        if (FLAGS_SET(link->network->keep_configuration, KEEP_CONFIGURATION_DHCP)) {
                                log_link_notice(link, "DHCPv4 connection considered critical, ignoring request to reconfigure it.");
                                return 0;
                        }

                        if (link->dhcp_lease) {
                                if (link->network->dhcp_send_release)
                                        (void) sd_dhcp_client_send_release(client);

                                r = dhcp_lease_lost(link);
                                if (r < 0) {
                                        link_enter_failed(link);
                                        return r;
                                }
                        }

                        break;
                case SD_DHCP_CLIENT_EVENT_EXPIRED:
                        if (FLAGS_SET(link->network->keep_configuration, KEEP_CONFIGURATION_DHCP)) {
                                log_link_notice(link, "DHCPv4 connection considered critical, ignoring request to reconfigure it.");
                                return 0;
                        }

                        if (link->dhcp_lease) {
                                r = dhcp_lease_lost(link);
                                if (r < 0) {
                                        link_enter_failed(link);
                                        return r;
                                }
                        }

                        break;
                case SD_DHCP_CLIENT_EVENT_IP_CHANGE:
                        if (FLAGS_SET(link->network->keep_configuration, KEEP_CONFIGURATION_DHCP)) {
                                log_link_notice(link, "DHCPv4 connection considered critical, ignoring request to reconfigure it.");
                                return 0;
                        }

                        r = dhcp_lease_ip_change(client, link);
                        if (r < 0) {
                                link_enter_failed(link);
                                return r;
                        }

                        break;
                case SD_DHCP_CLIENT_EVENT_RENEW:
                        r = dhcp_lease_renew(client, link);
                        if (r < 0) {
                                link_enter_failed(link);
                                return r;
                        }
                        break;
                case SD_DHCP_CLIENT_EVENT_IP_ACQUIRE:
                        r = dhcp_lease_acquired(client, link);
                        if (r < 0) {
                                link_enter_failed(link);
                                return r;
                        }
                        break;
                case SD_DHCP_CLIENT_EVENT_SELECTING:
                        r = dhcp_server_is_black_listed(link, client);
                        if (r < 0)
                                return r;
                        if (r != 0)
                                return -ENOMSG;
                        break;
                default:
                        if (event < 0)
                                log_link_warning_errno(link, event, "DHCP error: Client failed: %m");
                        else
                                log_link_warning(link, "DHCP unknown event: %i", event);
                        break;
        }

        return 0;
}