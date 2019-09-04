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

__attribute__((used)) static inline float
getfloat(const void *v) {
	union {
		uint32_t d;
		float f;
		uint8_t t[4];
	} test = { 1 };
	if (test.t[0] == 0) {
		// big endian
		test.d = *(const uint32_t *)v;
		test.d = test.t[0] | test.t[1] << 4 | test.t[2] << 8 | test.t[3] << 12;
		return test.f;
	} else {
		return *(const float *)v;
	}
}