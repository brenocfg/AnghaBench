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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MAXNAMELEN ; 
 int ZFS_CRC64_POLY ; 
 int* zfs_crc64_table ; 

uint64_t
zvol_name_hash(const char *name)
{
	int i;
	uint64_t crc = -1ULL;
	const uint8_t *p = (const uint8_t *)name;
	ASSERT(zfs_crc64_table[128] == ZFS_CRC64_POLY);
	for (i = 0; i < MAXNAMELEN - 1 && *p; i++, p++) {
		crc = (crc >> 8) ^ zfs_crc64_table[(crc ^ (*p)) & 0xFF];
	}
	return (crc);
}