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
struct TYPE_4__ {scalar_t__ llmnr_support; scalar_t__ mdns_support; scalar_t__ dnssec_mode; scalar_t__ dns_over_tls_mode; scalar_t__ default_route; int /*<<< orphan*/  dnssec_negative_trust_anchors; scalar_t__ search_domains; scalar_t__ dns_servers; scalar_t__ is_managed; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 scalar_t__ RESOLVE_SUPPORT_NO ; 
 scalar_t__ RESOLVE_SUPPORT_YES ; 
 scalar_t__ _DNSSEC_MODE_INVALID ; 
 scalar_t__ _DNS_OVER_TLS_MODE_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  set_isempty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool link_needs_save(Link *l) {
        assert(l);

        /* Returns true if any of the settings where set different from the default */

        if (l->is_managed)
                return false;

        if (l->llmnr_support != RESOLVE_SUPPORT_YES ||
            l->mdns_support != RESOLVE_SUPPORT_NO ||
            l->dnssec_mode != _DNSSEC_MODE_INVALID ||
            l->dns_over_tls_mode != _DNS_OVER_TLS_MODE_INVALID)
                return true;

        if (l->dns_servers ||
            l->search_domains)
                return true;

        if (!set_isempty(l->dnssec_negative_trust_anchors))
                return true;

        if (l->default_route >= 0)
                return true;

        return false;
}