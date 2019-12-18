#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  types; } ;
struct TYPE_8__ {int /*<<< orphan*/  types; } ;
struct TYPE_10__ {TYPE_3__ nsec3; TYPE_2__ nsec; TYPE_1__* key; } ;
struct TYPE_7__ {int type; } ;
typedef  TYPE_4__ DnsResourceRecord ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_TYPE_NS ; 
#define  DNS_TYPE_NSEC 129 
#define  DNS_TYPE_NSEC3 128 
 int /*<<< orphan*/  DNS_TYPE_SOA ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int /*<<< orphan*/  bitmap_isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rr_eligible(DnsResourceRecord *rr) {
        assert(rr);

        /* When we see an NSEC/NSEC3 RR, we'll only cache it if it is from the lower zone, not the upper zone, since
         * that's where the interesting bits are (with exception of DS RRs). Of course, this way we cannot derive DS
         * existence from any cached NSEC/NSEC3, but that should be fine. */

        switch (rr->key->type) {

        case DNS_TYPE_NSEC:
                return !bitmap_isset(rr->nsec.types, DNS_TYPE_NS) ||
                        bitmap_isset(rr->nsec.types, DNS_TYPE_SOA);

        case DNS_TYPE_NSEC3:
                return !bitmap_isset(rr->nsec3.types, DNS_TYPE_NS) ||
                        bitmap_isset(rr->nsec3.types, DNS_TYPE_SOA);

        default:
                return true;
        }
}