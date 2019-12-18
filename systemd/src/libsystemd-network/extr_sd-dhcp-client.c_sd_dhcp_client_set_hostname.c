#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hostname; } ;
typedef  TYPE_1__ sd_dhcp_client ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int) ; 
 scalar_t__ dns_name_is_valid (char const*) ; 
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ hostname_is_valid (char const*,int) ; 

int sd_dhcp_client_set_hostname(
                sd_dhcp_client *client,
                const char *hostname) {

        assert_return(client, -EINVAL);

        /* Make sure hostnames qualify as DNS and as Linux hostnames */
        if (hostname &&
            !(hostname_is_valid(hostname, false) && dns_name_is_valid(hostname) > 0))
                return -EINVAL;

        return free_and_strdup(&client->hostname, hostname);
}