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
struct TYPE_4__ {scalar_t__ verified_feature_level; int packet_rrsig_missing; } ;
typedef  scalar_t__ DnsServerFeatureLevel ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_DO ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_EDNS0 ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_IS_TLS (scalar_t__) ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_TLS_PLAIN ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void dns_server_packet_rrsig_missing(DnsServer *s, DnsServerFeatureLevel level) {
        assert(s);

        if (level < DNS_SERVER_FEATURE_LEVEL_DO)
                return;

        /* If the RRSIG RRs are missing, we have to downgrade what we previously verified */
        if (s->verified_feature_level >= DNS_SERVER_FEATURE_LEVEL_DO)
                s->verified_feature_level = DNS_SERVER_FEATURE_LEVEL_IS_TLS(level) ? DNS_SERVER_FEATURE_LEVEL_TLS_PLAIN : DNS_SERVER_FEATURE_LEVEL_EDNS0;

        s->packet_rrsig_missing = true;
}