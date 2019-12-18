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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sd_dhcp_client ;

/* Variables and functions */
 int dhcp_client_set_iaid_duid_internal (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 

int sd_dhcp_client_set_iaid_duid(
                sd_dhcp_client *client,
                bool iaid_set,
                uint32_t iaid,
                uint16_t duid_type,
                const void *duid,
                size_t duid_len) {
        return dhcp_client_set_iaid_duid_internal(client, true, iaid_set, iaid, duid_type, duid, duid_len, 0);
}