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
struct siphash {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  family; int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ DnsServer ;

/* Variables and functions */
 int FAMILY_ADDRESS_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  siphash24_compress (int /*<<< orphan*/ *,int,struct siphash*) ; 

__attribute__((used)) static void dns_server_hash_func(const DnsServer *s, struct siphash *state) {
        assert(s);

        siphash24_compress(&s->family, sizeof(s->family), state);
        siphash24_compress(&s->address, FAMILY_ADDRESS_SIZE(s->family), state);
        siphash24_compress(&s->ifindex, sizeof(s->ifindex), state);
}