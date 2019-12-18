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
typedef  int uint64 ;
typedef  scalar_t__ int64 ;

/* Variables and functions */

__attribute__((used)) static inline uint64
zig_zag_encode(uint64 value)
{
	// (((uint64)value) << 1) ^ (uint64)(value >> 63);
	/* since shift is underspecified, we use (value < 0 ? 0xFFFFFFFFFFFFFFFFull : 0)
	 * which compiles to the correct asm, and is well defined
	 */
	return (value << 1) ^ (((int64) value) < 0 ? 0xFFFFFFFFFFFFFFFFull : 0);
}