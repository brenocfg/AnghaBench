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
typedef  scalar_t__ dev_t ;

/* Variables and functions */

__attribute__((used)) static int cmpdev (const void *a, const void *b)
{
    const dev_t *da = a, *db = b;

    if (*da > *db)
        return +1;
    if (*da < *db)
        return -1;
    return 0;
}