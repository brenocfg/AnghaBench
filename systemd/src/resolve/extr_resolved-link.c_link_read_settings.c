#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int is_managed; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_flush_settings (TYPE_1__*) ; 
 int link_is_managed (TYPE_1__*) ; 
 int link_update_default_route (TYPE_1__*) ; 
 int link_update_dns_over_tls_mode (TYPE_1__*) ; 
 int link_update_dns_servers (TYPE_1__*) ; 
 int link_update_dnssec_mode (TYPE_1__*) ; 
 int link_update_dnssec_negative_trust_anchors (TYPE_1__*) ; 
 int link_update_llmnr_support (TYPE_1__*) ; 
 int link_update_mdns_support (TYPE_1__*) ; 
 int link_update_search_domains (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_warning_errno (TYPE_1__*,int,char*) ; 

__attribute__((used)) static void link_read_settings(Link *l) {
        int r;

        assert(l);

        /* Read settings from networkd, except when networkd is not managing this interface. */

        r = link_is_managed(l);
        if (r < 0) {
                log_link_warning_errno(l, r, "Failed to determine whether the interface is managed: %m");
                return;
        }
        if (r == 0) {

                /* If this link used to be managed, but is now unmanaged, flush all our settings — but only once. */
                if (l->is_managed)
                        link_flush_settings(l);

                l->is_managed = false;
                return;
        }

        l->is_managed = true;

        r = link_update_dns_servers(l);
        if (r < 0)
                log_link_warning_errno(l, r, "Failed to read DNS servers for the interface, ignoring: %m");

        r = link_update_llmnr_support(l);
        if (r < 0)
                log_link_warning_errno(l, r, "Failed to read LLMNR support for the interface, ignoring: %m");

        r = link_update_mdns_support(l);
        if (r < 0)
                log_link_warning_errno(l, r, "Failed to read mDNS support for the interface, ignoring: %m");

        r = link_update_dns_over_tls_mode(l);
        if (r < 0)
                log_link_warning_errno(l, r, "Failed to read DNS-over-TLS mode for the interface, ignoring: %m");

        r = link_update_dnssec_mode(l);
        if (r < 0)
                log_link_warning_errno(l, r, "Failed to read DNSSEC mode for the interface, ignoring: %m");

        r = link_update_dnssec_negative_trust_anchors(l);
        if (r < 0)
                log_link_warning_errno(l, r, "Failed to read DNSSEC negative trust anchors for the interface, ignoring: %m");

        r = link_update_search_domains(l);
        if (r < 0)
                log_link_warning_errno(l, r, "Failed to read search domains for the interface, ignoring: %m");

        r = link_update_default_route(l);
        if (r < 0)
                log_link_warning_errno(l, r, "Failed to read default route setting for the interface, proceeding anyway: %m");
}