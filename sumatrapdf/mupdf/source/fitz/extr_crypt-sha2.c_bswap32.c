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

__attribute__((used)) static inline unsigned int bswap32(unsigned int num)
{
	return	( (((num) << 24))
		| (((num) << 8) & 0x00FF0000)
		| (((num) >> 8) & 0x0000FF00)
		| (((num) >> 24)) );
}