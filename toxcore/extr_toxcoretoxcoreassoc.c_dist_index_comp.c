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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */

__attribute__((used)) static int dist_index_comp(const void *a, const void *b)
{
    const uint64_t *_a = a;
    const uint64_t *_b = b;

    if (*_a < *_b)
        return -1;

    if (*_a > *_b)
        return 1;

    return 0;
}