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

/* Variables and functions */

__attribute__((used)) static inline void
uint32_to_uint64(int negative, uint8_t *buffer) {
	if (negative) {
		buffer[4] = 0xff;
		buffer[5] = 0xff;
		buffer[6] = 0xff;
		buffer[7] = 0xff;
	} else {
		buffer[4] = 0;
		buffer[5] = 0;
		buffer[6] = 0;
		buffer[7] = 0;
	}
}