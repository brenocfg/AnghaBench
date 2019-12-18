#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int /*<<< orphan*/  raw_data_len; int /*<<< orphan*/ * raw_data; int /*<<< orphan*/  type; int /*<<< orphan*/  llt_time; } ;
struct TYPE_13__ {int dhcp_client_identifier; int /*<<< orphan*/  mac; struct TYPE_13__* dhcp_client; int /*<<< orphan*/  iaid; struct TYPE_13__* network; int /*<<< orphan*/  iaid_set; } ;
typedef  TYPE_1__ Link ;
typedef  TYPE_2__ DUID ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
#define  DHCP_CLIENT_ID_DUID 130 
#define  DHCP_CLIENT_ID_DUID_ONLY 129 
#define  DHCP_CLIENT_ID_MAC 128 
 int /*<<< orphan*/  DUID_TYPE_LLT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 TYPE_2__* link_get_duid (TYPE_1__*) ; 
 int log_link_error_errno (TYPE_1__*,int,char*) ; 
 int sd_dhcp_client_set_client_id (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int sd_dhcp_client_set_duid (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_dhcp_client_set_duid_llt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sd_dhcp_client_set_iaid_duid (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_dhcp_client_set_iaid_duid_llt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dhcp4_set_client_identifier(Link *link) {
        int r;

        assert(link);
        assert(link->network);
        assert(link->dhcp_client);

        switch (link->network->dhcp_client_identifier) {
        case DHCP_CLIENT_ID_DUID: {
                /* If configured, apply user specified DUID and IAID */
                const DUID *duid = link_get_duid(link);

                if (duid->type == DUID_TYPE_LLT && duid->raw_data_len == 0)
                        r = sd_dhcp_client_set_iaid_duid_llt(link->dhcp_client,
                                                             link->network->iaid_set,
                                                             link->network->iaid,
                                                             duid->llt_time);
                else
                        r = sd_dhcp_client_set_iaid_duid(link->dhcp_client,
                                                         link->network->iaid_set,
                                                         link->network->iaid,
                                                         duid->type,
                                                         duid->raw_data_len > 0 ? duid->raw_data : NULL,
                                                         duid->raw_data_len);
                if (r < 0)
                        return log_link_error_errno(link, r, "DHCP4 CLIENT: Failed to set IAID+DUID: %m");
                break;
        }
        case DHCP_CLIENT_ID_DUID_ONLY: {
                /* If configured, apply user specified DUID */
                const DUID *duid = link_get_duid(link);

                if (duid->type == DUID_TYPE_LLT && duid->raw_data_len == 0)
                        r = sd_dhcp_client_set_duid_llt(link->dhcp_client,
                                                        duid->llt_time);
                else
                        r = sd_dhcp_client_set_duid(link->dhcp_client,
                                                    duid->type,
                                                    duid->raw_data_len > 0 ? duid->raw_data : NULL,
                                                    duid->raw_data_len);
                if (r < 0)
                        return log_link_error_errno(link, r, "DHCP4 CLIENT: Failed to set DUID: %m");
                break;
        }
        case DHCP_CLIENT_ID_MAC:
                r = sd_dhcp_client_set_client_id(link->dhcp_client,
                                                 ARPHRD_ETHER,
                                                 (const uint8_t *) &link->mac,
                                                 sizeof(link->mac));
                if (r < 0)
                        return log_link_error_errno(link, r, "DHCP4 CLIENT: Failed to set client ID: %m");
                break;
        default:
                assert_not_reached("Unknown client identifier type.");
        }

        return 0;
}