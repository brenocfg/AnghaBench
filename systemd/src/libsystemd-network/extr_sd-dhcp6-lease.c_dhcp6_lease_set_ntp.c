#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ntp_count; int ntp_fqdn_count; int /*<<< orphan*/  ntp_fqdn; scalar_t__ ntp_allocated; int /*<<< orphan*/  ntp; } ;
typedef  TYPE_1__ uint8_t ;
typedef  int uint16_t ;
typedef  TYPE_1__ sd_dhcp6_lease ;

/* Variables and functions */
#define  DHCP6_NTP_SUBOPTION_MC_ADDR 130 
#define  DHCP6_NTP_SUBOPTION_SRV_ADDR 129 
#define  DHCP6_NTP_SUBOPTION_SRV_FQDN 128 
 int /*<<< orphan*/  EINVAL ; 
 int ENOMSG ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dhcp6_option_parse (TYPE_1__**,size_t*,int*,size_t*,TYPE_1__**) ; 
 int dhcp6_option_parse_domainname (TYPE_1__*,size_t,char***) ; 
 int dhcp6_option_parse_ip6addrs (TYPE_1__*,size_t,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_free_and_replace (int /*<<< orphan*/ ,char**) ; 

int dhcp6_lease_set_ntp(sd_dhcp6_lease *lease, uint8_t *optval, size_t optlen) {
        int r;
        uint16_t subopt;
        size_t sublen;
        uint8_t *subval;

        assert_return(lease, -EINVAL);
        assert_return(optval, -EINVAL);

        lease->ntp = mfree(lease->ntp);
        lease->ntp_count = 0;
        lease->ntp_allocated = 0;

        while ((r = dhcp6_option_parse(&optval, &optlen, &subopt, &sublen,
                                       &subval)) >= 0) {
                int s;
                char **servers;

                switch(subopt) {
                case DHCP6_NTP_SUBOPTION_SRV_ADDR:
                case DHCP6_NTP_SUBOPTION_MC_ADDR:
                        if (sublen != 16)
                                return 0;

                        s = dhcp6_option_parse_ip6addrs(subval, sublen,
                                                        &lease->ntp,
                                                        lease->ntp_count,
                                                        &lease->ntp_allocated);
                        if (s < 0)
                                return s;

                        lease->ntp_count = s;

                        break;

                case DHCP6_NTP_SUBOPTION_SRV_FQDN:
                        r = dhcp6_option_parse_domainname(subval, sublen,
                                                          &servers);
                        if (r < 0)
                                return 0;

                        strv_free_and_replace(lease->ntp_fqdn, servers);
                        lease->ntp_fqdn_count = r;

                        break;
                }
        }

        if (r != -ENOMSG)
                return r;

        return 0;
}