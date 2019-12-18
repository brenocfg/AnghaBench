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

__attribute__((used)) static uint8_t
mpt_compute_checksum(void *base, size_t len)
{
	uint8_t	*bytes;
	uint8_t	sum;

	for(bytes = base, sum = 0; len > 0; len--) {
		sum += *bytes++;
	}

	return ((uint8_t) (256 - sum));
}