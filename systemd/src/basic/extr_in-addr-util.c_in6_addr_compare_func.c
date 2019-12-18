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
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int memcmp (struct in6_addr const*,struct in6_addr const*,int) ; 

__attribute__((used)) static int in6_addr_compare_func(const struct in6_addr *a, const struct in6_addr *b) {
        return memcmp(a, b, sizeof(*a));
}