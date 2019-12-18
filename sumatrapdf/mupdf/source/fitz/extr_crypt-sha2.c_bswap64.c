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

__attribute__((used)) static inline uint64_t bswap64(uint64_t num)
{
	return ( (((num) << 56))
		| (((num) << 40) & 0x00FF000000000000ULL)
		| (((num) << 24) & 0x0000FF0000000000ULL)
		| (((num) << 8) & 0x000000FF00000000ULL)
		| (((num) >> 8) & 0x00000000FF000000ULL)
		| (((num) >> 24) & 0x0000000000FF0000ULL)
		| (((num) >> 40) & 0x000000000000FF00ULL)
		| (((num) >> 56)) );
}