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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static __inline uint32_t
be32dec(const void *pp)
{
	unsigned char const *p = (unsigned char const *)pp;

	return (uint32_t) ((((uint64_t) p[0]) << 24) | 
		(((uint64_t) p[1]) << 16) | (((uint64_t) p[2]) << 8) |
			((uint64_t) p[3]));
}