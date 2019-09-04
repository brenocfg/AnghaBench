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

__attribute__((used)) static unsigned int
ComputeDJBHash(const char *name)
{
    unsigned int val = 5381;
    int i = 0;

    for (i = 0; name[i]; i++)
    {
        val = (33 * val) + name[i];
    }

    return val;
}