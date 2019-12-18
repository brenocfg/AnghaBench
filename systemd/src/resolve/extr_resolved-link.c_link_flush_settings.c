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
struct TYPE_4__ {int default_route; int /*<<< orphan*/  dnssec_negative_trust_anchors; int /*<<< orphan*/  search_domains; int /*<<< orphan*/  dns_servers; int /*<<< orphan*/  dns_over_tls_mode; int /*<<< orphan*/  dnssec_mode; int /*<<< orphan*/  mdns_support; int /*<<< orphan*/  llmnr_support; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVE_SUPPORT_NO ; 
 int /*<<< orphan*/  RESOLVE_SUPPORT_YES ; 
 int /*<<< orphan*/  _DNSSEC_MODE_INVALID ; 
 int /*<<< orphan*/  _DNS_OVER_TLS_MODE_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_search_domain_unlink_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_server_unlink_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 

void link_flush_settings(Link *l) {
        assert(l);

        l->default_route = -1;
        l->llmnr_support = RESOLVE_SUPPORT_YES;
        l->mdns_support = RESOLVE_SUPPORT_NO;
        l->dnssec_mode = _DNSSEC_MODE_INVALID;
        l->dns_over_tls_mode = _DNS_OVER_TLS_MODE_INVALID;

        dns_server_unlink_all(l->dns_servers);
        dns_search_domain_unlink_all(l->search_domains);

        l->dnssec_negative_trust_anchors = set_free_free(l->dnssec_negative_trust_anchors);
}