#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct timezone {int dummy; } ;
struct ext2fs_struct_generic_bitmap_64 {int dummy; } ;
struct ext2_bitmap_ops {int (* new_bmap ) (TYPE_4__*,TYPE_3__*) ;} ;
typedef  TYPE_3__* ext2fs_generic_bitmap_64 ;
typedef  scalar_t__ ext2fs_generic_bitmap ;
typedef  int ext2_ino_t ;
typedef  TYPE_4__* ext2_filsys ;
typedef  int errcode_t ;
typedef  void* __u64 ;
struct TYPE_16__ {scalar_t__ cluster_ratio_bits; TYPE_1__* super; } ;
struct TYPE_14__ {int type; int /*<<< orphan*/  created; } ;
struct TYPE_15__ {int magic; struct TYPE_15__* description; struct ext2_bitmap_ops* bitmap_ops; int /*<<< orphan*/  base_error_code; scalar_t__ cluster_bits; void* real_end; void* end; void* start; TYPE_4__* fs; TYPE_2__ stats; } ;
struct TYPE_13__ {int s_inodes_count; } ;

/* Variables and functions */
 int EINVAL ; 
#define  EXT2FS_BMAP64_AUTODIR 132 
#define  EXT2FS_BMAP64_BITARRAY 131 
#define  EXT2FS_BMAP64_RBTREE 130 
 int /*<<< orphan*/  EXT2_ET_BAD_BLOCK_MARK ; 
 int /*<<< orphan*/  EXT2_ET_BAD_GENERIC_MARK ; 
 int /*<<< orphan*/  EXT2_ET_BAD_INODE_MARK ; 
#define  EXT2_ET_MAGIC_BLOCK_BITMAP64 129 
#define  EXT2_ET_MAGIC_INODE_BITMAP64 128 
 struct ext2_bitmap_ops ext2fs_blkmap64_bitarray ; 
 struct ext2_bitmap_ops ext2fs_blkmap64_rbtree ; 
 int /*<<< orphan*/  ext2fs_free_mem (TYPE_3__**) ; 
 int ext2fs_get_mem (scalar_t__,TYPE_3__**) ; 
 int ext2fs_get_memzero (int,TYPE_3__**) ; 
 int ext2fs_get_num_dirs (TYPE_4__*,int*) ; 
 int gettimeofday (int /*<<< orphan*/ *,struct timezone*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  strcpy (TYPE_3__*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int stub1 (TYPE_4__*,TYPE_3__*) ; 

errcode_t ext2fs_alloc_generic_bmap(ext2_filsys fs, errcode_t magic,
				    int type, __u64 start, __u64 end,
				    __u64 real_end,
				    const char *descr,
				    ext2fs_generic_bitmap *ret)
{
	ext2fs_generic_bitmap_64 bitmap;
	struct ext2_bitmap_ops	*ops;
	ext2_ino_t num_dirs;
	errcode_t retval;

	if (!type)
		type = EXT2FS_BMAP64_BITARRAY;

	switch (type) {
	case EXT2FS_BMAP64_BITARRAY:
		ops = &ext2fs_blkmap64_bitarray;
		break;
	case EXT2FS_BMAP64_RBTREE:
		ops = &ext2fs_blkmap64_rbtree;
		break;
	case EXT2FS_BMAP64_AUTODIR:
		retval = ext2fs_get_num_dirs(fs, &num_dirs);
		if (retval || num_dirs > (fs->super->s_inodes_count / 320))
			ops = &ext2fs_blkmap64_bitarray;
		else
			ops = &ext2fs_blkmap64_rbtree;
		break;
	default:
		return EINVAL;
	}

	retval = ext2fs_get_memzero(sizeof(struct ext2fs_struct_generic_bitmap_64),
				    &bitmap);
	if (retval)
		return retval;

#ifdef ENABLE_BMAP_STATS
	if (gettimeofday(&bitmap->stats.created,
			 (struct timezone *) NULL) == -1) {
		perror("gettimeofday");
		ext2fs_free_mem(&bitmap);
		return 1;
	}
	bitmap->stats.type = type;
#endif

	/* XXX factor out, repeated in copy_bmap */
	bitmap->magic = magic;
	bitmap->fs = fs;
	bitmap->start = start;
	bitmap->end = end;
	bitmap->real_end = real_end;
	bitmap->bitmap_ops = ops;
	bitmap->cluster_bits = 0;
	switch (magic) {
	case EXT2_ET_MAGIC_INODE_BITMAP64:
		bitmap->base_error_code = EXT2_ET_BAD_INODE_MARK;
		break;
	case EXT2_ET_MAGIC_BLOCK_BITMAP64:
		bitmap->base_error_code = EXT2_ET_BAD_BLOCK_MARK;
		bitmap->cluster_bits = fs->cluster_ratio_bits;
		break;
	default:
		bitmap->base_error_code = EXT2_ET_BAD_GENERIC_MARK;
	}
	if (descr) {
		retval = ext2fs_get_mem(strlen(descr)+1, &bitmap->description);
		if (retval) {
			ext2fs_free_mem(&bitmap);
			return retval;
		}
		strcpy(bitmap->description, descr);
	} else
		bitmap->description = 0;

	retval = bitmap->bitmap_ops->new_bmap(fs, bitmap);
	if (retval) {
		ext2fs_free_mem(&bitmap->description);
		ext2fs_free_mem(&bitmap);
		return retval;
	}

	*ret = (ext2fs_generic_bitmap) bitmap;
	return 0;
}