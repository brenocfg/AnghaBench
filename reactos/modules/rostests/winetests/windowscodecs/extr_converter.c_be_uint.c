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

__attribute__((used)) static unsigned be_uint(unsigned val)
{
    union
    {
        unsigned val;
        char c[4];
    } u;

    u.val = val;
    return (u.c[0] << 24) | (u.c[1] << 16) | (u.c[2] << 8) | u.c[3];
}