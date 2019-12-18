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
struct TYPE_4__ {scalar_t__ dns_over_tls_mode; } ;
typedef  TYPE_1__ Link ;
typedef  scalar_t__ DnsOverTlsMode ;

/* Variables and functions */
 scalar_t__ DNS_OVER_TLS_NO ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_warning (char*) ; 

void link_set_dns_over_tls_mode(Link *l, DnsOverTlsMode mode) {

        assert(l);

#if ! ENABLE_DNS_OVER_TLS
        if (mode != DNS_OVER_TLS_NO)
                log_warning("DNS-over-TLS option for the link cannot be enabled or set to opportunistic when systemd-resolved is built without DNS-over-TLS support. Turning off DNS-over-TLS support.");
        return;
#endif

        l->dns_over_tls_mode = mode;
}