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
struct TYPE_10__ {unsigned int n_ref; } ;
typedef  TYPE_1__ DnsResourceKey ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__**) ; 
 scalar_t__ dns_resource_key_equal (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* dns_resource_key_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_resource_key_unref (TYPE_1__*) ; 

bool dns_resource_key_reduce(DnsResourceKey **a, DnsResourceKey **b) {
        assert(a);
        assert(b);

        /* Try to replace one RR key by another if they are identical, thus saving a bit of memory. Note that we do
         * this only for RR keys, not for RRs themselves, as they carry a lot of additional metadata (where they come
         * from, validity data, and suchlike), and cannot be replaced so easily by other RRs that have the same
         * superficial data. */

        if (!*a)
                return false;
        if (!*b)
                return false;

        /* We refuse merging const keys */
        if ((*a)->n_ref == (unsigned) -1)
                return false;
        if ((*b)->n_ref == (unsigned) -1)
                return false;

        /* Already the same? */
        if (*a == *b)
                return true;

        /* Are they really identical? */
        if (dns_resource_key_equal(*a, *b) <= 0)
                return false;

        /* Keep the one which already has more references. */
        if ((*a)->n_ref > (*b)->n_ref) {
                dns_resource_key_unref(*b);
                *b = dns_resource_key_ref(*a);
        } else {
                dns_resource_key_unref(*a);
                *a = dns_resource_key_ref(*b);
        }

        return true;
}