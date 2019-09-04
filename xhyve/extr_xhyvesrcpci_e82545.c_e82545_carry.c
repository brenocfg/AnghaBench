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

__attribute__((used)) static uint16_t
e82545_carry(uint32_t sum)
{

	sum = (sum & 0xFFFF) + (sum >> 16);
	if (sum > 0xFFFF)
		sum -= 0xFFFF;
	return (uint16_t)sum;
}