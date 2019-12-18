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
typedef  unsigned long uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t
single_histo_average(uint64_t *histo, unsigned int buckets)
{
	int i;
	uint64_t count = 0, total = 0;

	for (i = 0; i < buckets; i++) {
		/*
		 * Our buckets are power-of-two latency ranges.  Use the
		 * midpoint latency of each bucket to calculate the average.
		 * For example:
		 *
		 * Bucket          Midpoint
		 * 8ns-15ns:       12ns
		 * 16ns-31ns:      24ns
		 * ...
		 */
		if (histo[i] != 0) {
			total += histo[i] * (((1UL << i) + ((1UL << i)/2)));
			count += histo[i];
		}
	}

	/* Prevent divide by zero */
	return (count == 0 ? 0 : total / count);
}