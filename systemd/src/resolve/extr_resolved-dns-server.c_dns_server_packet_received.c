#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t received_udp_packet_max; scalar_t__ packet_bad_opt; scalar_t__ packet_rrsig_missing; scalar_t__ n_failed_tcp; scalar_t__ possible_feature_level; scalar_t__ n_failed_tls; scalar_t__ n_failed_udp; } ;
typedef  scalar_t__ DnsServerFeatureLevel ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_DO ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_EDNS0 ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_IS_TLS (scalar_t__) ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_LARGE ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_TCP ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_TLS_PLAIN ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_server_verified (TYPE_1__*,scalar_t__) ; 

void dns_server_packet_received(DnsServer *s, int protocol, DnsServerFeatureLevel level, size_t size) {
        assert(s);

        if (protocol == IPPROTO_UDP) {
                if (s->possible_feature_level == level)
                        s->n_failed_udp = 0;
        } else if (protocol == IPPROTO_TCP) {
                if (DNS_SERVER_FEATURE_LEVEL_IS_TLS(level)) {
                        if (s->possible_feature_level == level)
                                s->n_failed_tls = 0;
                } else {
                        if (s->possible_feature_level == level)
                                s->n_failed_tcp = 0;

                        /* Successful TCP connections are only useful to verify the TCP feature level. */
                        level = DNS_SERVER_FEATURE_LEVEL_TCP;
                }
        }

        /* If the RRSIG data is missing, then we can only validate EDNS0 at max */
        if (s->packet_rrsig_missing && level >= DNS_SERVER_FEATURE_LEVEL_DO)
                level = DNS_SERVER_FEATURE_LEVEL_IS_TLS(level) ? DNS_SERVER_FEATURE_LEVEL_TLS_PLAIN : DNS_SERVER_FEATURE_LEVEL_EDNS0;

        /* If the OPT RR got lost, then we can only validate UDP at max */
        if (s->packet_bad_opt && level >= DNS_SERVER_FEATURE_LEVEL_EDNS0)
                level = DNS_SERVER_FEATURE_LEVEL_EDNS0 - 1;

        /* Even if we successfully receive a reply to a request announcing support for large packets,
                that does not mean we can necessarily receive large packets. */
        if (level == DNS_SERVER_FEATURE_LEVEL_LARGE)
                level = DNS_SERVER_FEATURE_LEVEL_LARGE - 1;

        dns_server_verified(s, level);

        /* Remember the size of the largest UDP packet we received from a server,
           we know that we can always announce support for packets with at least
           this size. */
        if (protocol == IPPROTO_UDP && s->received_udp_packet_max < size)
                s->received_udp_packet_max = size;
}