#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usec_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ minimum; } ;
struct TYPE_8__ {scalar_t__ expiry; TYPE_1__ soa; TYPE_2__* key; int /*<<< orphan*/  ttl; } ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_3__ DnsResourceRecord ;

/* Variables and functions */
 scalar_t__ CACHE_TTL_MAX_USEC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ DNS_TYPE_SOA ; 
 scalar_t__ LESS_BY (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ USEC_INFINITY ; 
 scalar_t__ USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 

__attribute__((used)) static usec_t calculate_until(DnsResourceRecord *rr, uint32_t nsec_ttl, usec_t timestamp, bool use_soa_minimum) {
        uint32_t ttl;
        usec_t u;

        assert(rr);

        ttl = MIN(rr->ttl, nsec_ttl);
        if (rr->key->type == DNS_TYPE_SOA && use_soa_minimum) {
                /* If this is a SOA RR, and it is requested, clamp to
                 * the SOA's minimum field. This is used when we do
                 * negative caching, to determine the TTL for the
                 * negative caching entry.  See RFC 2308, Section
                 * 5. */

                if (ttl > rr->soa.minimum)
                        ttl = rr->soa.minimum;
        }

        u = ttl * USEC_PER_SEC;
        if (u > CACHE_TTL_MAX_USEC)
                u = CACHE_TTL_MAX_USEC;

        if (rr->expiry != USEC_INFINITY) {
                usec_t left;

                /* Make use of the DNSSEC RRSIG expiry info, if we
                 * have it */

                left = LESS_BY(rr->expiry, now(CLOCK_REALTIME));
                if (u > left)
                        u = left;
        }

        return timestamp + u;
}