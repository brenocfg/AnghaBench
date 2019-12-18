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
struct siphash {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct in6_addr const*) ; 
 int /*<<< orphan*/  siphash24_compress (struct in6_addr const*,int,struct siphash*) ; 

__attribute__((used)) static void in6_addr_hash_func(const struct in6_addr *addr, struct siphash *state) {
        assert(addr);

        siphash24_compress(addr, sizeof(*addr), state);
}