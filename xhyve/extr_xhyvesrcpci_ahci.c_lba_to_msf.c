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

__attribute__((used)) static inline void lba_to_msf(uint8_t *buf, int lba)
{
	lba += 150;
	buf[0] = (uint8_t) ((lba / 75) / 60);
	buf[1] = (lba / 75) % 60;
	buf[2] = lba % 75;
}