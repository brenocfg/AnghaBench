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
little_endian(uint32_t v) {
	union {
		uint32_t v;
		uint8_t b[4];
	} u;
	u.v = v;
	return u.b[0] | u.b[1] << 8 | u.b[2] << 16 | u.b[3] << 24;
}