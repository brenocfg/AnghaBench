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
typedef  int uint32_t ;
struct TYPE_5__ {int family; int prefixlen; int /*<<< orphan*/  in_addr; } ;
typedef  TYPE_1__ Address ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int CMP (int,int) ; 
 int /*<<< orphan*/  FAMILY_ADDRESS_SIZE (int) ; 
 int /*<<< orphan*/  _fallthrough_ ; 
 int address_prefix (TYPE_1__ const*) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int address_compare_func(const Address *a1, const Address *a2) {
        int r;

        r = CMP(a1->family, a2->family);
        if (r != 0)
                return r;

        switch (a1->family) {
        /* use the same notion of equality as the kernel does */
        case AF_INET:
                r = CMP(a1->prefixlen, a2->prefixlen);
                if (r != 0)
                        return r;

                uint32_t prefix1 = address_prefix(a1);
                uint32_t prefix2 = address_prefix(a2);
                r = CMP(prefix1, prefix2);
                if (r != 0)
                        return r;

                _fallthrough_;
        case AF_INET6:
                return memcmp(&a1->in_addr, &a2->in_addr, FAMILY_ADDRESS_SIZE(a1->family));
        default:
                /* treat any other address family as AF_UNSPEC */
                return 0;
        }
}