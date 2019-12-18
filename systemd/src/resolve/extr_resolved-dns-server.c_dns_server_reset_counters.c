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
struct TYPE_4__ {int packet_truncated; scalar_t__ verified_usec; scalar_t__ n_failed_tls; scalar_t__ n_failed_tcp; scalar_t__ n_failed_udp; } ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void dns_server_reset_counters(DnsServer *s) {
        assert(s);

        s->n_failed_udp = 0;
        s->n_failed_tcp = 0;
        s->n_failed_tls = 0;
        s->packet_truncated = false;
        s->verified_usec = 0;

        /* Note that we do not reset s->packet_bad_opt and s->packet_rrsig_missing here. We reset them only when the
         * grace period ends, but not when lowering the possible feature level, as a lower level feature level should
         * not make RRSIGs appear or OPT appear, but rather make them disappear. If the reappear anyway, then that's
         * indication for a differently broken OPT/RRSIG implementation, and we really don't want to support that
         * either.
         *
         * This is particularly important to deal with certain Belkin routers which break OPT for certain lookups (A),
         * but pass traffic through for others (AAAA). If we detect the broken behaviour on one lookup we should not
         * re-enable it for another, because we cannot validate things anyway, given that the RRSIG/OPT data will be
         * incomplete. */
}