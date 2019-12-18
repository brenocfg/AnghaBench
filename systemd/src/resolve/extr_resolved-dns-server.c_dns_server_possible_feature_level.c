#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ possible_feature_level; int packet_bad_opt; int packet_rrsig_missing; scalar_t__ verified_feature_level; scalar_t__ n_failed_tcp; scalar_t__ n_failed_tls; scalar_t__ n_failed_udp; scalar_t__ packet_truncated; } ;
typedef  scalar_t__ DnsServerFeatureLevel ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 scalar_t__ DNSSEC_NO ; 
 scalar_t__ DNSSEC_YES ; 
 scalar_t__ DNS_OVER_TLS_NO ; 
 scalar_t__ DNS_OVER_TLS_YES ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_DO ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_EDNS0 ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_IS_TLS (scalar_t__) ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_LARGE ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_TCP ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_TLS_DO ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_TLS_PLAIN ; 
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_UDP ; 
 scalar_t__ DNS_SERVER_FEATURE_RETRY_ATTEMPTS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_server_feature_level_to_string (scalar_t__) ; 
 int /*<<< orphan*/  dns_server_flush_cache (TYPE_1__*) ; 
 scalar_t__ dns_server_get_dns_over_tls_mode (TYPE_1__*) ; 
 scalar_t__ dns_server_get_dnssec_mode (TYPE_1__*) ; 
 scalar_t__ dns_server_grace_period_expired (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_server_reset_counters (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_server_string (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DnsServerFeatureLevel dns_server_possible_feature_level(DnsServer *s) {
        DnsServerFeatureLevel best;

        assert(s);

        /* Determine the best feature level we care about. If DNSSEC mode is off there's no point in using anything
         * better than EDNS0, hence don't even try. */
        if (dns_server_get_dnssec_mode(s) != DNSSEC_NO)
                best = dns_server_get_dns_over_tls_mode(s) == DNS_OVER_TLS_NO ?
                        DNS_SERVER_FEATURE_LEVEL_LARGE :
                        DNS_SERVER_FEATURE_LEVEL_TLS_DO;
        else
                best = dns_server_get_dns_over_tls_mode(s) == DNS_OVER_TLS_NO ?
                        DNS_SERVER_FEATURE_LEVEL_EDNS0 :
                        DNS_SERVER_FEATURE_LEVEL_TLS_PLAIN;

        /* Clamp the feature level the highest level we care about. The DNSSEC mode might have changed since the last
         * time, hence let's downgrade if we are still at a higher level. */
        if (s->possible_feature_level > best)
                s->possible_feature_level = best;

        if (s->possible_feature_level < best && dns_server_grace_period_expired(s)) {

                s->possible_feature_level = best;

                dns_server_reset_counters(s);

                s->packet_bad_opt = false;
                s->packet_rrsig_missing = false;

                log_info("Grace period over, resuming full feature set (%s) for DNS server %s.",
                         dns_server_feature_level_to_string(s->possible_feature_level),
                         dns_server_string(s));

                dns_server_flush_cache(s);

        } else if (s->possible_feature_level <= s->verified_feature_level)
                s->possible_feature_level = s->verified_feature_level;
        else {
                DnsServerFeatureLevel p = s->possible_feature_level;

                if (s->n_failed_tcp >= DNS_SERVER_FEATURE_RETRY_ATTEMPTS &&
                    s->possible_feature_level == DNS_SERVER_FEATURE_LEVEL_TCP) {

                        /* We are at the TCP (lowest) level, and we tried a couple of TCP connections, and it didn't
                         * work. Upgrade back to UDP again. */
                        log_debug("Reached maximum number of failed TCP connection attempts, trying UDP again...");
                        s->possible_feature_level = DNS_SERVER_FEATURE_LEVEL_UDP;
                } else if (s->n_failed_tls > 0 &&
                           DNS_SERVER_FEATURE_LEVEL_IS_TLS(s->possible_feature_level) && dns_server_get_dns_over_tls_mode(s) != DNS_OVER_TLS_YES) {

                        /* We tried to connect using DNS-over-TLS, and it didn't work. Downgrade to plaintext UDP
                         * if we don't require DNS-over-TLS */

                        log_debug("Server doesn't support DNS-over-TLS, downgrading protocol...");
                        s->possible_feature_level--;
                } else if (s->packet_bad_opt &&
                           s->possible_feature_level >= DNS_SERVER_FEATURE_LEVEL_EDNS0) {

                        /* A reply to one of our EDNS0 queries didn't carry a valid OPT RR, then downgrade to below
                         * EDNS0 levels. After all, some records generate different responses with and without OPT RR
                         * in the request. Example:
                         * https://open.nlnetlabs.nl/pipermail/dnssec-trigger/2014-November/000376.html */

                        log_debug("Server doesn't support EDNS(0) properly, downgrading feature level...");
                        s->possible_feature_level = DNS_SERVER_FEATURE_LEVEL_UDP;

                } else if (s->packet_rrsig_missing &&
                           s->possible_feature_level >= DNS_SERVER_FEATURE_LEVEL_DO) {

                        /* RRSIG data was missing on a EDNS0 packet with DO bit set. This means the server doesn't
                         * augment responses with DNSSEC RRs. If so, let's better not ask the server for it anymore,
                         * after all some servers generate different replies depending if an OPT RR is in the query or
                         * not. */

                        log_debug("Detected server responses lack RRSIG records, downgrading feature level...");
                        s->possible_feature_level = DNS_SERVER_FEATURE_LEVEL_IS_TLS(s->possible_feature_level) ? DNS_SERVER_FEATURE_LEVEL_TLS_PLAIN : DNS_SERVER_FEATURE_LEVEL_EDNS0;

                } else if (s->n_failed_udp >= DNS_SERVER_FEATURE_RETRY_ATTEMPTS &&
                           s->possible_feature_level >= (dns_server_get_dnssec_mode(s) == DNSSEC_YES ? DNS_SERVER_FEATURE_LEVEL_LARGE : DNS_SERVER_FEATURE_LEVEL_UDP)) {

                        /* We lost too many UDP packets in a row, and are on a feature level of UDP or higher. If the
                         * packets are lost, maybe the server cannot parse them, hence downgrading sounds like a good
                         * idea. We might downgrade all the way down to TCP this way.
                         *
                         * If strict DNSSEC mode is used we won't downgrade below DO level however, as packet loss
                         * might have many reasons, a broken DNSSEC implementation being only one reason. And if the
                         * user is strict on DNSSEC, then let's assume that DNSSEC is not the fault here. */

                        log_debug("Lost too many UDP packets, downgrading feature level...");
                        s->possible_feature_level--;

                } else if (s->n_failed_tcp >= DNS_SERVER_FEATURE_RETRY_ATTEMPTS &&
                           s->packet_truncated &&
                           s->possible_feature_level > (dns_server_get_dnssec_mode(s) == DNSSEC_YES ? DNS_SERVER_FEATURE_LEVEL_LARGE : DNS_SERVER_FEATURE_LEVEL_UDP)) {

                         /* We got too many TCP connection failures in a row, we had at least one truncated packet, and
                          * are on a feature level above UDP. By downgrading things and getting rid of DNSSEC or EDNS0
                          * data we hope to make the packet smaller, so that it still works via UDP given that TCP
                          * appears not to be a fallback. Note that if we are already at the lowest UDP level, we don't
                          * go further down, since that's TCP, and TCP failed too often after all. */

                        log_debug("Got too many failed TCP connection failures and truncated UDP packets, downgrading feature level...");
                        s->possible_feature_level--;
                }

                if (p != s->possible_feature_level) {

                        /* We changed the feature level, reset the counting */
                        dns_server_reset_counters(s);

                        log_warning("Using degraded feature set (%s) for DNS server %s.",
                                    dns_server_feature_level_to_string(s->possible_feature_level),
                                    dns_server_string(s));
                }
        }

        return s->possible_feature_level;
}