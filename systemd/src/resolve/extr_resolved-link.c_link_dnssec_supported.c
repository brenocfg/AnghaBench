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
typedef  int /*<<< orphan*/  Link ;
typedef  int /*<<< orphan*/  DnsServer ;

/* Variables and functions */
 scalar_t__ DNSSEC_NO ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int dns_server_dnssec_supported (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * link_get_dns_server (int /*<<< orphan*/ *) ; 
 scalar_t__ link_get_dnssec_mode (int /*<<< orphan*/ *) ; 

bool link_dnssec_supported(Link *l) {
        DnsServer *server;

        assert(l);

        if (link_get_dnssec_mode(l) == DNSSEC_NO)
                return false;

        server = link_get_dns_server(l);
        if (server)
                return dns_server_dnssec_supported(server);

        return true;
}