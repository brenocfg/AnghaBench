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
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  ddt_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

void
ddt_stat_add(ddt_stat_t *dst, const ddt_stat_t *src, uint64_t neg)
{
	const uint64_t *s = (const uint64_t *)src;
	uint64_t *d = (uint64_t *)dst;
	uint64_t *d_end = (uint64_t *)(dst + 1);

	ASSERT(neg == 0 || neg == -1ULL);	/* add or subtract */

	while (d < d_end)
		*d++ += (*s++ ^ neg) - neg;
}