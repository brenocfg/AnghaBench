#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {scalar_t__ ttl; int n_ref; TYPE_1__* key; } ;
struct TYPE_8__ {scalar_t__ type; } ;
typedef  TYPE_2__ DnsResourceRecord ;

/* Variables and functions */
 scalar_t__ DNS_TYPE_OPT ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (TYPE_2__**) ; 
 TYPE_2__* dns_resource_record_copy (TYPE_2__*) ; 
 int /*<<< orphan*/  dns_resource_record_unref (TYPE_2__*) ; 

int dns_resource_record_clamp_ttl(DnsResourceRecord **rr, uint32_t max_ttl) {
        DnsResourceRecord *old_rr, *new_rr;
        uint32_t new_ttl;

        assert(rr);
        old_rr = *rr;

        if (old_rr->key->type == DNS_TYPE_OPT)
                return -EINVAL;

        new_ttl = MIN(old_rr->ttl, max_ttl);
        if (new_ttl == old_rr->ttl)
                return 0;

        if (old_rr->n_ref == 1) {
                /* Patch in place */
                old_rr->ttl = new_ttl;
                return 1;
        }

        new_rr = dns_resource_record_copy(old_rr);
        if (!new_rr)
                return -ENOMEM;

        new_rr->ttl = new_ttl;

        dns_resource_record_unref(*rr);
        *rr = new_rr;

        return 1;
}