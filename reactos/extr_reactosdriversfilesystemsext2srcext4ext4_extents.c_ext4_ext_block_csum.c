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
struct inode {int dummy; } ;
struct ext4_extent_header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t ext4_ext_block_csum(struct inode *inode,
		struct ext4_extent_header *eh)
{
	/*return ext4_crc32c(inode->i_csum, eh, EXT4_EXTENT_TAIL_OFFSET(eh));*/
	return 0;
}