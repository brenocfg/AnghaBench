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
typedef  int /*<<< orphan*/  Manager ;
typedef  int /*<<< orphan*/  AddressPool ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int address_pool_new_from_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_default_address_pool(Manager *m) {
        AddressPool *p;
        int r;

        assert(m);

        /* Add in the well-known private address ranges. */

        r = address_pool_new_from_string(m, &p, AF_INET6, "fd00::", 8);
        if (r < 0)
                return r;

        r = address_pool_new_from_string(m, &p, AF_INET, "10.0.0.0", 8);
        if (r < 0)
                return r;

        r = address_pool_new_from_string(m, &p, AF_INET, "172.16.0.0", 12);
        if (r < 0)
                return r;

        r = address_pool_new_from_string(m, &p, AF_INET, "192.168.0.0", 16);
        if (r < 0)
                return r;

        return 0;
}