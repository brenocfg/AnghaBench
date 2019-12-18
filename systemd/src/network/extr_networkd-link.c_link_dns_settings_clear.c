#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int n_dns; int dns_default_route; int /*<<< orphan*/  dnssec_negative_trust_anchors; int /*<<< orphan*/  dns_over_tls_mode; int /*<<< orphan*/  dnssec_mode; void* mdns; void* llmnr; void* route_domains; void* search_domains; int /*<<< orphan*/  dns; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  _DNSSEC_MODE_INVALID ; 
 int /*<<< orphan*/  _DNS_OVER_TLS_MODE_INVALID ; 
 void* _RESOLVE_SUPPORT_INVALID ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 void* ordered_set_free_free (void*) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 

void link_dns_settings_clear(Link *link) {
        link->dns = mfree(link->dns);
        link->n_dns = (unsigned) -1;

        link->search_domains = ordered_set_free_free(link->search_domains);
        link->route_domains = ordered_set_free_free(link->route_domains);

        link->dns_default_route = -1;
        link->llmnr = _RESOLVE_SUPPORT_INVALID;
        link->mdns = _RESOLVE_SUPPORT_INVALID;
        link->dnssec_mode = _DNSSEC_MODE_INVALID;
        link->dns_over_tls_mode = _DNS_OVER_TLS_MODE_INVALID;

        link->dnssec_negative_trust_anchors = set_free_free(link->dnssec_negative_trust_anchors);
}