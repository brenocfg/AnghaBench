#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_sb; } ;
struct ext4_extent_header {int dummy; } ;
struct ext4_extent {int dummy; } ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */

__attribute__((used)) static inline int ext4_ext_space_block(struct inode *inode, int check)
{
	int size;

	size = (inode->i_sb->s_blocksize - sizeof(struct ext4_extent_header))
		/ sizeof(struct ext4_extent);
#ifdef AGGRESSIVE_TEST
	if (!check && size > 6)
		size = 6;
#endif
	return size;
}