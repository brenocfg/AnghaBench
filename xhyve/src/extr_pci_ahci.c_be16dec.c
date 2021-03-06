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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */

__attribute__((used)) static __inline uint16_t
be16dec(const void *pp)
{
	unsigned char const *p = (unsigned char const *)pp;

	return ((uint16_t) ((((uint32_t) p[0]) << 8) | ((uint32_t) p[1])));
}