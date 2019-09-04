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
typedef  int crc16_t ;

/* Variables and functions */
 int* crc16_table ; 

crc16_t ext2fs_crc16(crc16_t crc, const void *buffer, unsigned int len)
{
	const unsigned char *cp = buffer;

	while (len--)
		/*
		 * for an unknown reason, PPC treats __u16 as signed
		 * and keeps doing sign extension on the value.
		 * Instead, use only the low 16 bits of an unsigned
		 * int for holding the CRC value to avoid this.
		 */
		crc = (((crc >> 8) & 0xffU) ^
		       crc16_table[(crc ^ *cp++) & 0xffU]) & 0x0000ffffU;
	return crc;
}