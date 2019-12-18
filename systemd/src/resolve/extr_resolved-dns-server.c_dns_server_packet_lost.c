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
struct TYPE_4__ {scalar_t__ possible_feature_level; int /*<<< orphan*/  n_failed_tcp; int /*<<< orphan*/  n_failed_tls; int /*<<< orphan*/  n_failed_udp; struct TYPE_4__* manager; } ;
typedef  scalar_t__ DnsServerFeatureLevel ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_IS_TLS (scalar_t__) ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void dns_server_packet_lost(DnsServer *s, int protocol, DnsServerFeatureLevel level) {
        assert(s);
        assert(s->manager);

        if (s->possible_feature_level == level) {
                if (protocol == IPPROTO_UDP)
                        s->n_failed_udp++;
                else if (protocol == IPPROTO_TCP) {
                        if (DNS_SERVER_FEATURE_LEVEL_IS_TLS(level))
                                s->n_failed_tls++;
                        else
                                s->n_failed_tcp++;
                }
        }
}