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
 int FS_PER_S ; 
 scalar_t__ HPET_CAP_COUNT_SIZE ; 
 int HPET_FREQ ; 
 int VHPET_NUM_TIMERS ; 

__attribute__((used)) static uint64_t
vhpet_capabilities(void)
{
	uint64_t cap = 0;

	cap |= ((uint64_t) 0x8086) << 16; /* vendor id */
	cap |= ((uint64_t) (VHPET_NUM_TIMERS - 1)) << 8; /* number of timers */
	cap |= (uint64_t) 1; /* revision */
	cap &= ~((uint64_t) HPET_CAP_COUNT_SIZE); /* 32-bit timer */
	cap &= (uint64_t) 0xffffffff;
	cap |= ((uint64_t) (FS_PER_S / HPET_FREQ)) << 32; /* tick period in fs */

	return (cap);
}