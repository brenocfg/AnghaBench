#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ext2fs_inode_bitmap ;
typedef  int /*<<< orphan*/  ext2fs_generic_bitmap ;
typedef  TYPE_1__* ext2_filsys ;
typedef  int /*<<< orphan*/  errcode_t ;
typedef  unsigned int __u64 ;
struct TYPE_8__ {unsigned int s_inodes_count; } ;
struct TYPE_7__ {unsigned int group_desc_count; int flags; int /*<<< orphan*/  default_bitmap_type; TYPE_5__* super; int /*<<< orphan*/  write_bitmaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_ET_CANT_USE_LEGACY_BITMAPS ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_INODE_BITMAP ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_INODE_BITMAP64 ; 
 int EXT2_FLAG_64BITS ; 
 unsigned int EXT2_INODES_PER_GROUP (TYPE_5__*) ; 
 int /*<<< orphan*/  ext2fs_alloc_generic_bmap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2fs_make_generic_bitmap (int /*<<< orphan*/ ,TYPE_1__*,unsigned int,unsigned int,unsigned int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2fs_write_bitmaps ; 

errcode_t ext2fs_allocate_inode_bitmap(ext2_filsys fs,
				       const char *descr,
				       ext2fs_inode_bitmap *ret)
{
	__u64		start, end, real_end;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	fs->write_bitmaps = ext2fs_write_bitmaps;

	start = 1;
	end = fs->super->s_inodes_count;
	real_end = (EXT2_INODES_PER_GROUP(fs->super) * fs->group_desc_count);

	/* Are we permitted to use new-style bitmaps? */
	if (fs->flags & EXT2_FLAG_64BITS)
		return (ext2fs_alloc_generic_bmap(fs,
				EXT2_ET_MAGIC_INODE_BITMAP64,
				fs->default_bitmap_type,
				start, end, real_end, descr, ret));

	/* Otherwise, check to see if the file system is small enough
	 * to use old-style 32-bit bitmaps */
	if ((end > ~0U) || (real_end > ~0U))
		return EXT2_ET_CANT_USE_LEGACY_BITMAPS;

	return (ext2fs_make_generic_bitmap(EXT2_ET_MAGIC_INODE_BITMAP, fs,
					 start, end, real_end,
					 descr, 0,
					 (ext2fs_generic_bitmap *) ret));
}