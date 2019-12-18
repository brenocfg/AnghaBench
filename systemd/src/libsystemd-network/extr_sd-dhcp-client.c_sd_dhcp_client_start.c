#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  state; int /*<<< orphan*/  anonymize; scalar_t__ last_addr; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_STATE_INIT_REBOOT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int client_initialize (TYPE_1__*) ; 
 int client_start (TYPE_1__*) ; 
 int /*<<< orphan*/  log_dhcp_client (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

int sd_dhcp_client_start(sd_dhcp_client *client) {
        int r;

        assert_return(client, -EINVAL);

        r = client_initialize(client);
        if (r < 0)
                return r;

        /* RFC7844 section 3.3:
           SHOULD perform a complete four-way handshake, starting with a
           DHCPDISCOVER, to obtain a new address lease.  If the client can
           ascertain that this is exactly the same network to which it was
           previously connected, and if the link-layer address did not change,
           the client MAY issue a DHCPREQUEST to try to reclaim the current
           address. */
        if (client->last_addr && !client->anonymize)
                client->state = DHCP_STATE_INIT_REBOOT;

        r = client_start(client);
        if (r >= 0)
                log_dhcp_client(client, "STARTED on ifindex %i", client->ifindex);

        return r;
}