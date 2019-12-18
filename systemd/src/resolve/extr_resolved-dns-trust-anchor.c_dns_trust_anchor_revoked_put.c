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
struct TYPE_4__ {int /*<<< orphan*/  revoked_by_rr; } ;
typedef  TYPE_1__ DnsTrustAnchor ;
typedef  int /*<<< orphan*/  DnsResourceRecord ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_resource_record_hash_ops ; 
 int /*<<< orphan*/  dns_resource_record_ref (int /*<<< orphan*/ *) ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dns_trust_anchor_revoked_put(DnsTrustAnchor *d, DnsResourceRecord *rr) {
        int r;

        assert(d);

        r = set_ensure_allocated(&d->revoked_by_rr, &dns_resource_record_hash_ops);
        if (r < 0)
                return r;

        r = set_put(d->revoked_by_rr, rr);
        if (r < 0)
                return r;
        if (r > 0)
                dns_resource_record_ref(rr);

        return r;
}