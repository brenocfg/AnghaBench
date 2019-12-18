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
struct TYPE_7__ {int domains_count; int /*<<< orphan*/  domains; } ;
typedef  TYPE_1__ uint8_t ;
typedef  TYPE_1__ sd_dhcp6_lease ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dhcp6_option_parse_domainname (TYPE_1__*,size_t,char***) ; 
 int /*<<< orphan*/  strv_free_and_replace (int /*<<< orphan*/ ,char**) ; 

int dhcp6_lease_set_domains(sd_dhcp6_lease *lease, uint8_t *optval,
                            size_t optlen) {
        int r;
        char **domains;

        assert_return(lease, -EINVAL);
        assert_return(optval, -EINVAL);

        if (!optlen)
                return 0;

        r = dhcp6_option_parse_domainname(optval, optlen, &domains);
        if (r < 0)
                return 0;

        strv_free_and_replace(lease->domains, domains);
        lease->domains_count = r;

        return r;
}