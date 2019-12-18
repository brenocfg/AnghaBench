#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_8__ {void* id; } ;
struct TYPE_9__ {TYPE_1__ ia_pd; } ;
struct TYPE_11__ {void* id; } ;
struct TYPE_10__ {TYPE_4__ ia_na; } ;
struct TYPE_12__ {int iaid_set; TYPE_2__ ia_pd; TYPE_3__ ia_na; int /*<<< orphan*/  mac_addr_len; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  ifindex; } ;
typedef  TYPE_5__ sd_dhcp6_client ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 int dhcp_identifier_set_iaid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**) ; 

__attribute__((used)) static int client_ensure_iaid(sd_dhcp6_client *client) {
        int r;
        uint32_t iaid;

        assert(client);

        if (client->iaid_set)
                return 0;

        r = dhcp_identifier_set_iaid(client->ifindex, client->mac_addr, client->mac_addr_len, true, &iaid);
        if (r < 0)
                return r;

        client->ia_na.ia_na.id = iaid;
        client->ia_pd.ia_pd.id = iaid;
        client->iaid_set = true;

        return 0;
}