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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
from_bigendian(uint32_t n) {
	union {
		uint32_t big;
		uint8_t bytes[4];
	} u;
	u.big = n;
	return u.bytes[0] << 24 | u.bytes[1] << 16 | u.bytes[2] << 8 | u.bytes[3];
}