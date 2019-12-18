#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_dhcp6_client ;
struct TYPE_14__ {int dhcp6_configured; int /*<<< orphan*/  manager; int /*<<< orphan*/  state; struct TYPE_14__* network; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_STATE_FAILED ; 
 int /*<<< orphan*/  LINK_STATE_LINGER ; 
#define  SD_DHCP6_CLIENT_EVENT_INFORMATION_REQUEST 132 
#define  SD_DHCP6_CLIENT_EVENT_IP_ACQUIRE 131 
#define  SD_DHCP6_CLIENT_EVENT_RESEND_EXPIRE 130 
#define  SD_DHCP6_CLIENT_EVENT_RETRANS_MAX 129 
#define  SD_DHCP6_CLIENT_EVENT_STOP 128 
 int /*<<< orphan*/  _fallthrough_ ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dhcp6_lease_address_acquired (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dhcp6_lease_information_acquired (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dhcp6_lease_pd_prefix_acquired (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dhcp6_lease_pd_prefix_lost (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dhcp6_prefix_remove_all (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  link_check_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  link_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  link_enter_failed (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  log_link_warning (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  sd_dhcp6_client_get_lease (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dhcp6_handler(sd_dhcp6_client *client, int event, void *userdata) {
        int r;
        Link *link = userdata;

        assert(link);
        assert(link->network);

        if (IN_SET(link->state, LINK_STATE_FAILED, LINK_STATE_LINGER))
                return;

        switch(event) {
        case SD_DHCP6_CLIENT_EVENT_STOP:
        case SD_DHCP6_CLIENT_EVENT_RESEND_EXPIRE:
        case SD_DHCP6_CLIENT_EVENT_RETRANS_MAX:
                if (sd_dhcp6_client_get_lease(client, NULL) >= 0)
                        log_link_warning(link, "DHCPv6 lease lost");

                (void) dhcp6_lease_pd_prefix_lost(client, link);
                (void) dhcp6_prefix_remove_all(link->manager, link);

                link_dirty(link);
                link->dhcp6_configured = false;
                break;

        case SD_DHCP6_CLIENT_EVENT_IP_ACQUIRE:
                r = dhcp6_lease_address_acquired(client, link);
                if (r < 0) {
                        link_enter_failed(link);
                        return;
                }

                r = dhcp6_lease_pd_prefix_acquired(client, link);
                if (r < 0)
                        log_link_debug(link, "DHCPv6 did not receive prefixes to delegate");

                _fallthrough_;
        case SD_DHCP6_CLIENT_EVENT_INFORMATION_REQUEST:
                r = dhcp6_lease_information_acquired(client, link);
                if (r < 0) {
                        link_enter_failed(link);
                        return;
                }

                link_dirty(link);
                link->dhcp6_configured = true;
                break;

        default:
                if (event < 0)
                        log_link_warning_errno(link, event, "DHCPv6 error: %m");
                else
                        log_link_warning(link, "DHCPv6 unknown event: %d", event);
                return;
        }

        link_check_ready(link);
}