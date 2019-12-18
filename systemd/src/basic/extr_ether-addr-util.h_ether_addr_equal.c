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
struct ether_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ ether_addr_compare (struct ether_addr const*,struct ether_addr const*) ; 

__attribute__((used)) static inline bool ether_addr_equal(const struct ether_addr *a, const struct ether_addr *b) {
        return ether_addr_compare(a, b) == 0;
}