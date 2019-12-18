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
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct TYPE_4__ {int /*<<< orphan*/  addresses_foreign; } ;
typedef  TYPE_1__ Link ;
typedef  int /*<<< orphan*/  Address ;

/* Variables and functions */
 int address_add_internal (TYPE_1__*,int /*<<< orphan*/ *,int,union in_addr_union const*,unsigned char,int /*<<< orphan*/ **) ; 

int address_add_foreign(Link *link, int family, const union in_addr_union *in_addr, unsigned char prefixlen, Address **ret) {
        return address_add_internal(link, &link->addresses_foreign, family, in_addr, prefixlen, ret);
}