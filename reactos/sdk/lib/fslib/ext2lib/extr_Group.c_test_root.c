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

int test_root(int a, int b)
{
    if (a == 0)
        return 1;
    while (1)
    {
        if (a == 1)
            return 1;
        if (a % b)
            return 0;
        a = a / b;
    }
}