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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int CRC_LE_BITS ; 
 int /*<<< orphan*/  crc32init_be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crc32init_le (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 

uint32_t* crc32_filltable(uint32_t *crc_table, int endian)
{
	/* Expects the caller to do the cleanup */
	if (!crc_table)
		crc_table = malloc((1 << CRC_LE_BITS) * sizeof(uint32_t));
	if (crc_table) {
		if (endian)
			crc32init_be(crc_table);
		else
			crc32init_le(crc_table);
	}
	return crc_table;
}