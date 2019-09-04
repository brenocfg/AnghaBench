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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT64 ;
typedef  int UINT32 ;

/* Variables and functions */
 int calc_crc32c (int,int /*<<< orphan*/ *,int) ; 

UINT64 get_extent_data_ref_hash2(UINT64 root, UINT64 objid, UINT64 offset) {
    UINT32 high_crc = 0xffffffff, low_crc = 0xffffffff;

    high_crc = calc_crc32c(high_crc, (UINT8*)&root, sizeof(UINT64));
    low_crc = calc_crc32c(low_crc, (UINT8*)&objid, sizeof(UINT64));
    low_crc = calc_crc32c(low_crc, (UINT8*)&offset, sizeof(UINT64));

    return ((UINT64)high_crc << 31) ^ (UINT64)low_crc;
}