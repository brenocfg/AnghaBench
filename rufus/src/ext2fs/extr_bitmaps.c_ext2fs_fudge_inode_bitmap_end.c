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
typedef  scalar_t__ ext2fs_inode_bitmap ;
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int errcode_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_FUDGE_INODE_BITMAP_END ; 
 int ext2fs_fudge_generic_bmap_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

errcode_t ext2fs_fudge_inode_bitmap_end(ext2fs_inode_bitmap bitmap,
					ext2_ino_t end, ext2_ino_t *oend)
{
	__u64 tmp_oend;
	int retval;

	retval = ext2fs_fudge_generic_bmap_end((ext2fs_generic_bitmap) bitmap,
					       EXT2_ET_FUDGE_INODE_BITMAP_END,
					       end, &tmp_oend);
	if (oend)
		*oend = tmp_oend;
	return retval;
}