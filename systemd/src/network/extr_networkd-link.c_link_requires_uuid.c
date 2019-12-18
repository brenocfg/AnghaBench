#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ type; scalar_t__ raw_data_len; } ;
struct TYPE_10__ {int /*<<< orphan*/  dhcp_client_identifier; struct TYPE_10__* network; struct TYPE_10__* manager; } ;
typedef  TYPE_1__ Link ;
typedef  TYPE_2__ DUID ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_CLIENT_ID_DUID ; 
 int /*<<< orphan*/  DHCP_CLIENT_ID_DUID_ONLY ; 
 scalar_t__ DUID_TYPE_UUID ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ link_dhcp4_enabled (TYPE_1__*) ; 
 scalar_t__ link_dhcp6_enabled (TYPE_1__*) ; 
 TYPE_2__* link_get_duid (TYPE_1__*) ; 
 scalar_t__ link_ipv6_accept_ra_enabled (TYPE_1__*) ; 

__attribute__((used)) static bool link_requires_uuid(Link *link) {
        const DUID *duid;

        assert(link);
        assert(link->manager);
        assert(link->network);

        duid = link_get_duid(link);
        if (duid->type != DUID_TYPE_UUID || duid->raw_data_len != 0)
                return false;

        if (link_dhcp4_enabled(link) && IN_SET(link->network->dhcp_client_identifier, DHCP_CLIENT_ID_DUID, DHCP_CLIENT_ID_DUID_ONLY))
                return true;

        if (link_dhcp6_enabled(link) || link_ipv6_accept_ra_enabled(link))
                return true;

        return false;
}