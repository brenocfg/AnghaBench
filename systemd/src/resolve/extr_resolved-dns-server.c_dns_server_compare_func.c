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
struct TYPE_4__ {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  family; int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAMILY_ADDRESS_SIZE (int /*<<< orphan*/ ) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dns_server_compare_func(const DnsServer *x, const DnsServer *y) {
        int r;

        r = CMP(x->family, y->family);
        if (r != 0)
                return r;

        r = memcmp(&x->address, &y->address, FAMILY_ADDRESS_SIZE(x->family));
        if (r != 0)
                return r;

        r = CMP(x->ifindex, y->ifindex);
        if (r != 0)
                return r;

        return 0;
}