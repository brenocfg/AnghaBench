#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ DnsResourceRecord ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int dns_resource_key_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dns_resource_record_payload_equal (TYPE_1__ const*,TYPE_1__ const*) ; 

int dns_resource_record_equal(const DnsResourceRecord *a, const DnsResourceRecord *b) {
        int r;

        assert(a);
        assert(b);

        if (a == b)
                return 1;

        r = dns_resource_key_equal(a->key, b->key);
        if (r <= 0)
                return r;

        return dns_resource_record_payload_equal(a, b);
}