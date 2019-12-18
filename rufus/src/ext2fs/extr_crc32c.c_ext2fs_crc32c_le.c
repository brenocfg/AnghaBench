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
 int /*<<< orphan*/  CRC32C_POLY_LE ; 
 int /*<<< orphan*/  crc32_le_generic (int /*<<< orphan*/ ,unsigned char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32ctable_le ; 

uint32_t ext2fs_crc32c_le(uint32_t crc, unsigned char const *p, size_t len)
{
	return crc32_le_generic(crc, p, len, crc32ctable_le, CRC32C_POLY_LE);
}