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
struct ether_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  siphash24_compress (struct ether_addr const*,int,struct siphash*) ; 

__attribute__((used)) static void ether_addr_hash_func(const struct ether_addr *p, struct siphash *state) {
        siphash24_compress(p, sizeof(struct ether_addr), state);
}