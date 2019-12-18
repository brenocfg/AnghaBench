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

__attribute__((used)) static __inline uint64_t rdtsc(void)
{
	unsigned a, d;
	__asm__ __volatile__ ("cpuid");
	__asm__ __volatile__ ("rdtsc" : "=a" (a), "=d" (d));

	return (((uint64_t) a) | (((uint64_t) d) << 32));
}