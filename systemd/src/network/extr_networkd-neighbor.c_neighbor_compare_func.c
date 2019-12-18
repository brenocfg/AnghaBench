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
struct TYPE_4__ {int family; int lladdr_size; int /*<<< orphan*/  lladdr; int /*<<< orphan*/  in_addr; } ;
typedef  TYPE_1__ Neighbor ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int CMP (int,int) ; 
 int FAMILY_ADDRESS_SIZE (int) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int neighbor_compare_func(const Neighbor *a, const Neighbor *b) {
        int r;

        r = CMP(a->family, b->family);
        if (r != 0)
                return r;

        r = CMP(a->lladdr_size, b->lladdr_size);
        if (r != 0)
                return r;

        switch (a->family) {
        case AF_INET:
        case AF_INET6:
                r = memcmp(&a->in_addr, &b->in_addr, FAMILY_ADDRESS_SIZE(a->family));
                if (r != 0)
                        return r;
        }

        return memcmp(&a->lladdr, &b->lladdr, a->lladdr_size);
}