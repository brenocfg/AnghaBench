#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int packet_bad_opt; int packet_rrsig_missing; int warned_downgrade; int /*<<< orphan*/  features_grace_period_usec; int /*<<< orphan*/  received_udp_packet_max; int /*<<< orphan*/  possible_feature_level; int /*<<< orphan*/  verified_feature_level; } ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_PACKET_UNICAST_SIZE_MAX ; 
 int /*<<< orphan*/  DNS_SERVER_FEATURE_GRACE_PERIOD_MIN_USEC ; 
 int /*<<< orphan*/  DNS_SERVER_FEATURE_LEVEL_BEST ; 
 int /*<<< orphan*/  _DNS_SERVER_FEATURE_LEVEL_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_server_reset_counters (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_server_unref_stream (TYPE_1__*) ; 

void dns_server_reset_features(DnsServer *s) {
        assert(s);

        s->verified_feature_level = _DNS_SERVER_FEATURE_LEVEL_INVALID;
        s->possible_feature_level = DNS_SERVER_FEATURE_LEVEL_BEST;

        s->received_udp_packet_max = DNS_PACKET_UNICAST_SIZE_MAX;

        s->packet_bad_opt = false;
        s->packet_rrsig_missing = false;

        s->features_grace_period_usec = DNS_SERVER_FEATURE_GRACE_PERIOD_MIN_USEC;

        s->warned_downgrade = false;

        dns_server_reset_counters(s);

        /* Let's close the default stream, so that we reprobe with the new features */
        dns_server_unref_stream(s);
}