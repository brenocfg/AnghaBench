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
typedef  int WORD ;

/* Variables and functions */

WORD crc_msgrand(WORD reg)
{
	const WORD mask = 0xb400;

	if(reg & 1)
		reg = (reg >> 1) ^ mask;
	else
		reg = (reg >> 1);

	return reg;
}