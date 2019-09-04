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

/* Variables and functions */
 int CRCPOLY_LE ; 
 int CRC_LE_BITS ; 

__attribute__((used)) static void crc32init_le(uint32_t *crc32table_le)
{
	unsigned i, j;
	uint32_t crc = 1;

	crc32table_le[0] = 0;

	for (i = 1 << (CRC_LE_BITS - 1); i; i >>= 1) {
		crc = (crc >> 1) ^ ((crc & 1) ? CRCPOLY_LE : 0);
		for (j = 0; j < 1 << CRC_LE_BITS; j += 2 * i)
			crc32table_le[i + j] = crc ^ crc32table_le[j];
	}
}