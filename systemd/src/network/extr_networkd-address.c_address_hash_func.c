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
struct siphash {int dummy; } ;
typedef  int /*<<< orphan*/  prefix ;
struct TYPE_5__ {int family; int prefixlen; int in_addr; } ;
typedef  TYPE_1__ Address ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int FAMILY_ADDRESS_SIZE (int) ; 
 int /*<<< orphan*/  _fallthrough_ ; 
 int address_prefix (TYPE_1__ const*) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  siphash24_compress (int*,int,struct siphash*) ; 

__attribute__((used)) static void address_hash_func(const Address *a, struct siphash *state) {
        assert(a);

        siphash24_compress(&a->family, sizeof(a->family), state);

        switch (a->family) {
        case AF_INET:
                siphash24_compress(&a->prefixlen, sizeof(a->prefixlen), state);

                /* peer prefix */
                uint32_t prefix = address_prefix(a);
                siphash24_compress(&prefix, sizeof(prefix), state);

                _fallthrough_;
        case AF_INET6:
                /* local address */
                siphash24_compress(&a->in_addr, FAMILY_ADDRESS_SIZE(a->family), state);

                break;
        default:
                /* treat any other address family as AF_UNSPEC */
                break;
        }
}