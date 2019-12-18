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
struct TYPE_4__ {int /*<<< orphan*/  fqdn; } ;
typedef  TYPE_1__ sd_dhcp6_client ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int) ; 
 scalar_t__ dns_name_is_valid (char const*) ; 
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ hostname_is_valid (char const*,int) ; 

int sd_dhcp6_client_set_fqdn(
                sd_dhcp6_client *client,
                const char *fqdn) {

        assert_return(client, -EINVAL);

        /* Make sure FQDN qualifies as DNS and as Linux hostname */
        if (fqdn &&
            !(hostname_is_valid(fqdn, false) && dns_name_is_valid(fqdn) > 0))
                return -EINVAL;

        return free_and_strdup(&client->fqdn, fqdn);
}