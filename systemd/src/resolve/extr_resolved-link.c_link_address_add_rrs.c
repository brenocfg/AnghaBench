#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  zone; } ;
struct TYPE_17__ {int /*<<< orphan*/  in6_addr; } ;
struct TYPE_16__ {int /*<<< orphan*/  in_addr; } ;
struct TYPE_21__ {void* ttl; TYPE_2__ aaaa; TYPE_1__ a; } ;
struct TYPE_15__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  in; } ;
struct TYPE_20__ {scalar_t__ family; TYPE_8__* mdns_ptr_rr; TYPE_4__* link; TYPE_8__* mdns_address_rr; TYPE_13__ in_addr; TYPE_8__* llmnr_ptr_rr; TYPE_8__* llmnr_address_rr; } ;
struct TYPE_19__ {scalar_t__ llmnr_support; scalar_t__ mdns_support; TYPE_9__* mdns_ipv6_scope; TYPE_3__* manager; TYPE_9__* llmnr_ipv6_scope; TYPE_9__* mdns_ipv4_scope; TYPE_9__* llmnr_ipv4_scope; } ;
struct TYPE_18__ {scalar_t__ llmnr_support; scalar_t__ mdns_support; int /*<<< orphan*/  mdns_hostname; void* mdns_host_ipv6_key; int /*<<< orphan*/  llmnr_hostname; void* llmnr_host_ipv6_key; void* mdns_host_ipv4_key; void* llmnr_host_ipv4_key; } ;
typedef  TYPE_5__ LinkAddress ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  DNS_CLASS_IN ; 
 int /*<<< orphan*/  DNS_TYPE_A ; 
 int /*<<< orphan*/  DNS_TYPE_AAAA ; 
 int ENOMEM ; 
 void* LLMNR_DEFAULT_TTL ; 
 void* MDNS_DEFAULT_TTL ; 
 scalar_t__ RESOLVE_SUPPORT_YES ; 
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 void* dns_resource_key_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dns_resource_record_new (void*) ; 
 int dns_resource_record_new_reverse (TYPE_8__**,scalar_t__,TYPE_13__*,int /*<<< orphan*/ ) ; 
 void* dns_resource_record_unref (TYPE_8__*) ; 
 int dns_zone_put (int /*<<< orphan*/ *,TYPE_9__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  dns_zone_remove_rr (int /*<<< orphan*/ *,TYPE_8__*) ; 
 scalar_t__ link_address_relevant (TYPE_5__*,int) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 

void link_address_add_rrs(LinkAddress *a, bool force_remove) {
        int r;

        assert(a);

        if (a->family == AF_INET) {

                if (!force_remove &&
                    link_address_relevant(a, true) &&
                    a->link->llmnr_ipv4_scope &&
                    a->link->llmnr_support == RESOLVE_SUPPORT_YES &&
                    a->link->manager->llmnr_support == RESOLVE_SUPPORT_YES) {

                        if (!a->link->manager->llmnr_host_ipv4_key) {
                                a->link->manager->llmnr_host_ipv4_key = dns_resource_key_new(DNS_CLASS_IN, DNS_TYPE_A, a->link->manager->llmnr_hostname);
                                if (!a->link->manager->llmnr_host_ipv4_key) {
                                        r = -ENOMEM;
                                        goto fail;
                                }
                        }

                        if (!a->llmnr_address_rr) {
                                a->llmnr_address_rr = dns_resource_record_new(a->link->manager->llmnr_host_ipv4_key);
                                if (!a->llmnr_address_rr) {
                                        r = -ENOMEM;
                                        goto fail;
                                }

                                a->llmnr_address_rr->a.in_addr = a->in_addr.in;
                                a->llmnr_address_rr->ttl = LLMNR_DEFAULT_TTL;
                        }

                        if (!a->llmnr_ptr_rr) {
                                r = dns_resource_record_new_reverse(&a->llmnr_ptr_rr, a->family, &a->in_addr, a->link->manager->llmnr_hostname);
                                if (r < 0)
                                        goto fail;

                                a->llmnr_ptr_rr->ttl = LLMNR_DEFAULT_TTL;
                        }

                        r = dns_zone_put(&a->link->llmnr_ipv4_scope->zone, a->link->llmnr_ipv4_scope, a->llmnr_address_rr, true);
                        if (r < 0)
                                log_warning_errno(r, "Failed to add A record to LLMNR zone: %m");

                        r = dns_zone_put(&a->link->llmnr_ipv4_scope->zone, a->link->llmnr_ipv4_scope, a->llmnr_ptr_rr, false);
                        if (r < 0)
                                log_warning_errno(r, "Failed to add IPv4 PTR record to LLMNR zone: %m");
                } else {
                        if (a->llmnr_address_rr) {
                                if (a->link->llmnr_ipv4_scope)
                                        dns_zone_remove_rr(&a->link->llmnr_ipv4_scope->zone, a->llmnr_address_rr);
                                a->llmnr_address_rr = dns_resource_record_unref(a->llmnr_address_rr);
                        }

                        if (a->llmnr_ptr_rr) {
                                if (a->link->llmnr_ipv4_scope)
                                        dns_zone_remove_rr(&a->link->llmnr_ipv4_scope->zone, a->llmnr_ptr_rr);
                                a->llmnr_ptr_rr = dns_resource_record_unref(a->llmnr_ptr_rr);
                        }
                }

                if (!force_remove &&
                    link_address_relevant(a, true) &&
                    a->link->mdns_ipv4_scope &&
                    a->link->mdns_support == RESOLVE_SUPPORT_YES &&
                    a->link->manager->mdns_support == RESOLVE_SUPPORT_YES) {
                        if (!a->link->manager->mdns_host_ipv4_key) {
                                a->link->manager->mdns_host_ipv4_key = dns_resource_key_new(DNS_CLASS_IN, DNS_TYPE_A, a->link->manager->mdns_hostname);
                                if (!a->link->manager->mdns_host_ipv4_key) {
                                        r = -ENOMEM;
                                        goto fail;
                                }
                        }

                        if (!a->mdns_address_rr) {
                                a->mdns_address_rr = dns_resource_record_new(a->link->manager->mdns_host_ipv4_key);
                                if (!a->mdns_address_rr) {
                                        r = -ENOMEM;
                                        goto fail;
                                }

                                a->mdns_address_rr->a.in_addr = a->in_addr.in;
                                a->mdns_address_rr->ttl = MDNS_DEFAULT_TTL;
                        }

                        if (!a->mdns_ptr_rr) {
                                r = dns_resource_record_new_reverse(&a->mdns_ptr_rr, a->family, &a->in_addr, a->link->manager->mdns_hostname);
                                if (r < 0)
                                        goto fail;

                                a->mdns_ptr_rr->ttl = MDNS_DEFAULT_TTL;
                        }

                        r = dns_zone_put(&a->link->mdns_ipv4_scope->zone, a->link->mdns_ipv4_scope, a->mdns_address_rr, true);
                        if (r < 0)
                                log_warning_errno(r, "Failed to add A record to MDNS zone: %m");

                        r = dns_zone_put(&a->link->mdns_ipv4_scope->zone, a->link->mdns_ipv4_scope, a->mdns_ptr_rr, false);
                        if (r < 0)
                                log_warning_errno(r, "Failed to add IPv4 PTR record to MDNS zone: %m");
                } else {
                        if (a->mdns_address_rr) {
                                if (a->link->mdns_ipv4_scope)
                                        dns_zone_remove_rr(&a->link->mdns_ipv4_scope->zone, a->mdns_address_rr);
                                a->mdns_address_rr = dns_resource_record_unref(a->mdns_address_rr);
                        }

                        if (a->mdns_ptr_rr) {
                                if (a->link->mdns_ipv4_scope)
                                        dns_zone_remove_rr(&a->link->mdns_ipv4_scope->zone, a->mdns_ptr_rr);
                                a->mdns_ptr_rr = dns_resource_record_unref(a->mdns_ptr_rr);
                        }
                }
        }

        if (a->family == AF_INET6) {

                if (!force_remove &&
                    link_address_relevant(a, true) &&
                    a->link->llmnr_ipv6_scope &&
                    a->link->llmnr_support == RESOLVE_SUPPORT_YES &&
                    a->link->manager->llmnr_support == RESOLVE_SUPPORT_YES) {

                        if (!a->link->manager->llmnr_host_ipv6_key) {
                                a->link->manager->llmnr_host_ipv6_key = dns_resource_key_new(DNS_CLASS_IN, DNS_TYPE_AAAA, a->link->manager->llmnr_hostname);
                                if (!a->link->manager->llmnr_host_ipv6_key) {
                                        r = -ENOMEM;
                                        goto fail;
                                }
                        }

                        if (!a->llmnr_address_rr) {
                                a->llmnr_address_rr = dns_resource_record_new(a->link->manager->llmnr_host_ipv6_key);
                                if (!a->llmnr_address_rr) {
                                        r = -ENOMEM;
                                        goto fail;
                                }

                                a->llmnr_address_rr->aaaa.in6_addr = a->in_addr.in6;
                                a->llmnr_address_rr->ttl = LLMNR_DEFAULT_TTL;
                        }

                        if (!a->llmnr_ptr_rr) {
                                r = dns_resource_record_new_reverse(&a->llmnr_ptr_rr, a->family, &a->in_addr, a->link->manager->llmnr_hostname);
                                if (r < 0)
                                        goto fail;

                                a->llmnr_ptr_rr->ttl = LLMNR_DEFAULT_TTL;
                        }

                        r = dns_zone_put(&a->link->llmnr_ipv6_scope->zone, a->link->llmnr_ipv6_scope, a->llmnr_address_rr, true);
                        if (r < 0)
                                log_warning_errno(r, "Failed to add AAAA record to LLMNR zone: %m");

                        r = dns_zone_put(&a->link->llmnr_ipv6_scope->zone, a->link->llmnr_ipv6_scope, a->llmnr_ptr_rr, false);
                        if (r < 0)
                                log_warning_errno(r, "Failed to add IPv6 PTR record to LLMNR zone: %m");
                } else {
                        if (a->llmnr_address_rr) {
                                if (a->link->llmnr_ipv6_scope)
                                        dns_zone_remove_rr(&a->link->llmnr_ipv6_scope->zone, a->llmnr_address_rr);
                                a->llmnr_address_rr = dns_resource_record_unref(a->llmnr_address_rr);
                        }

                        if (a->llmnr_ptr_rr) {
                                if (a->link->llmnr_ipv6_scope)
                                        dns_zone_remove_rr(&a->link->llmnr_ipv6_scope->zone, a->llmnr_ptr_rr);
                                a->llmnr_ptr_rr = dns_resource_record_unref(a->llmnr_ptr_rr);
                        }
                }

                if (!force_remove &&
                    link_address_relevant(a, true) &&
                    a->link->mdns_ipv6_scope &&
                    a->link->mdns_support == RESOLVE_SUPPORT_YES &&
                    a->link->manager->mdns_support == RESOLVE_SUPPORT_YES) {

                        if (!a->link->manager->mdns_host_ipv6_key) {
                                a->link->manager->mdns_host_ipv6_key = dns_resource_key_new(DNS_CLASS_IN, DNS_TYPE_AAAA, a->link->manager->mdns_hostname);
                                if (!a->link->manager->mdns_host_ipv6_key) {
                                        r = -ENOMEM;
                                        goto fail;
                                }
                        }

                        if (!a->mdns_address_rr) {
                                a->mdns_address_rr = dns_resource_record_new(a->link->manager->mdns_host_ipv6_key);
                                if (!a->mdns_address_rr) {
                                        r = -ENOMEM;
                                        goto fail;
                                }

                                a->mdns_address_rr->aaaa.in6_addr = a->in_addr.in6;
                                a->mdns_address_rr->ttl = MDNS_DEFAULT_TTL;
                        }

                        if (!a->mdns_ptr_rr) {
                                r = dns_resource_record_new_reverse(&a->mdns_ptr_rr, a->family, &a->in_addr, a->link->manager->mdns_hostname);
                                if (r < 0)
                                        goto fail;

                                a->mdns_ptr_rr->ttl = MDNS_DEFAULT_TTL;
                        }

                        r = dns_zone_put(&a->link->mdns_ipv6_scope->zone, a->link->mdns_ipv6_scope, a->mdns_address_rr, true);
                        if (r < 0)
                                log_warning_errno(r, "Failed to add AAAA record to MDNS zone: %m");

                        r = dns_zone_put(&a->link->mdns_ipv6_scope->zone, a->link->mdns_ipv6_scope, a->mdns_ptr_rr, false);
                        if (r < 0)
                                log_warning_errno(r, "Failed to add IPv6 PTR record to MDNS zone: %m");
                } else {
                        if (a->mdns_address_rr) {
                                if (a->link->mdns_ipv6_scope)
                                        dns_zone_remove_rr(&a->link->mdns_ipv6_scope->zone, a->mdns_address_rr);
                                a->mdns_address_rr = dns_resource_record_unref(a->mdns_address_rr);
                        }

                        if (a->mdns_ptr_rr) {
                                if (a->link->mdns_ipv6_scope)
                                        dns_zone_remove_rr(&a->link->mdns_ipv6_scope->zone, a->mdns_ptr_rr);
                                a->mdns_ptr_rr = dns_resource_record_unref(a->mdns_ptr_rr);
                        }
                }
        }

        return;

fail:
        log_debug_errno(r, "Failed to update address RRs: %m");
}