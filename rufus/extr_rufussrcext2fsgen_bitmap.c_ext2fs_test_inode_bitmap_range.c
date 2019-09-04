#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ext2fs_inode_bitmap ;
typedef  TYPE_1__* ext2fs_generic_bitmap_32 ;
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;
typedef  int ext2_ino_t ;
struct TYPE_3__ {int start; int real_end; int /*<<< orphan*/  description; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_BAD_INODE_TEST ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_INODE_BITMAP ; 
 int ext2fs_test_clear_generic_bitmap_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ext2fs_warn_bitmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int ext2fs_test_inode_bitmap_range(ext2fs_inode_bitmap gen_bitmap,
				   ext2_ino_t inode, int num)
{
	ext2fs_generic_bitmap_32 bitmap = (ext2fs_generic_bitmap_32) gen_bitmap;

	EXT2_CHECK_MAGIC(bitmap, EXT2_ET_MAGIC_INODE_BITMAP);
	if ((inode < bitmap->start) || (inode > bitmap->real_end) ||
	    (inode+num-1 > bitmap->real_end)) {
		ext2fs_warn_bitmap(EXT2_ET_BAD_INODE_TEST,
				   inode, bitmap->description);
		return 0;
	}
	return ext2fs_test_clear_generic_bitmap_range((ext2fs_generic_bitmap)
						      bitmap, inode, num);
}