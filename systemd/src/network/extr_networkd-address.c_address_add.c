#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct TYPE_5__ {int /*<<< orphan*/  addresses_foreign; int /*<<< orphan*/  addresses; } ;
typedef  TYPE_1__ Link ;
typedef  int /*<<< orphan*/  Address ;

/* Variables and functions */
 int ENOENT ; 
 int address_add_internal (TYPE_1__*,int /*<<< orphan*/ *,int,union in_addr_union const*,unsigned char,int /*<<< orphan*/ **) ; 
 int address_get (TYPE_1__*,int,union in_addr_union const*,unsigned char,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  address_hash_ops ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int address_add(Link *link, int family, const union in_addr_union *in_addr, unsigned char prefixlen, Address **ret) {
        Address *address;
        int r;

        r = address_get(link, family, in_addr, prefixlen, &address);
        if (r == -ENOENT) {
                /* Address does not exist, create a new one */
                r = address_add_internal(link, &link->addresses, family, in_addr, prefixlen, &address);
                if (r < 0)
                        return r;
        } else if (r == 0) {
                /* Take over a foreign address */
                r = set_ensure_allocated(&link->addresses, &address_hash_ops);
                if (r < 0)
                        return r;

                r = set_put(link->addresses, address);
                if (r < 0)
                        return r;

                set_remove(link->addresses_foreign, address);
        } else if (r == 1) {
                /* Already exists, do nothing */
                ;
        } else
                return r;

        if (ret)
                *ret = address;

        return 0;
}