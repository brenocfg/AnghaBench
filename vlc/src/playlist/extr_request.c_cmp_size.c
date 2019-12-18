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

/* Variables and functions */

__attribute__((used)) static int
cmp_size(const void *lhs, const void *rhs)
{
    size_t a = *(size_t *) lhs;
    size_t b = *(size_t *) rhs;
    if (a < b)
        return -1;
    if (a == b)
        return 0;
    return 1;
}