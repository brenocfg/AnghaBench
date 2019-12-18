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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static int key_qsort_cmp(const void *keyp_a, const void *keyp_b) {
	uint32_t key_a = **(uint32_t **)keyp_a;
	uint32_t key_b = **(uint32_t **)keyp_b;
	return (key_a < key_b) ? -1 : ((key_a > key_b) ? 1 : 0);
}