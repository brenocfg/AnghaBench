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

__attribute__((used)) static inline void
to_bigendian(uint8_t *buffer, uint32_t n) {
	buffer[0] = (n >> 24) & 0xff;
	buffer[1] = (n >> 16) & 0xff;
	buffer[2] = (n >> 8) & 0xff;
	buffer[3] = n & 0xff;
}