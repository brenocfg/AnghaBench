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
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IN_SET (int,int,int) ; 
 int /*<<< orphan*/  assert (struct in_addr const*) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_addr_is_link_local (int /*<<< orphan*/ ,union in_addr_union const*) ; 

__attribute__((used)) static bool ipv4ll_address_is_valid(const struct in_addr *address) {
        assert(address);

        if (!in_addr_is_link_local(AF_INET, (const union in_addr_union *) address))
                return false;

        return !IN_SET(be32toh(address->s_addr) & 0x0000FF00U, 0x0000U, 0xFF00U);
}