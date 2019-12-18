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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static __inline int popcnt64(register uint64_t u)
{
	u = (u & 0x5555555555555555) + ((u >> 1) & 0x5555555555555555);
	u = (u & 0x3333333333333333) + ((u >> 2) & 0x3333333333333333);
	u = (u & 0x0f0f0f0f0f0f0f0f) + ((u >> 4) & 0x0f0f0f0f0f0f0f0f);
	u = (u & 0x00ff00ff00ff00ff) + ((u >> 8) & 0x00ff00ff00ff00ff);
	u = (u & 0x0000ffff0000ffff) + ((u >> 16) & 0x0000ffff0000ffff);
	u = (u & 0x00000000ffffffff) + ((u >> 32) & 0x00000000ffffffff);
	return (int)u;
}