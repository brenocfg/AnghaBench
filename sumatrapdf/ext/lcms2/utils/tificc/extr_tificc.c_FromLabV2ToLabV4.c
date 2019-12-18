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

__attribute__((used)) static int FromLabV2ToLabV4(int x)
{
    int a;

    a = ((x << 8) | x) >> 8;  // * 257 / 256
    if ( a > 0xffff) return 0xffff;
    return a;
}