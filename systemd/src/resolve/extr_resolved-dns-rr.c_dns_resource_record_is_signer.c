#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DnsResourceRecord ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int dns_name_equal (char const*,char const*) ; 
 int dns_resource_record_signer (int /*<<< orphan*/ *,char const**) ; 

int dns_resource_record_is_signer(DnsResourceRecord *rr, const char *zone) {
        const char *signer;
        int r;

        assert(rr);

        r = dns_resource_record_signer(rr, &signer);
        if (r < 0)
                return r;

        return dns_name_equal(zone, signer);
}