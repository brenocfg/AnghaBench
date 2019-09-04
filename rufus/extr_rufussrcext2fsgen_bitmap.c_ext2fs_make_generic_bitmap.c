#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ext2fs_struct_generic_bitmap_32 {int dummy; } ;
typedef  TYPE_1__* ext2fs_generic_bitmap_32 ;
typedef  scalar_t__ ext2fs_generic_bitmap ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  int errcode_t ;
typedef  void* __u32 ;
struct TYPE_7__ {int magic; int start; int real_end; struct TYPE_7__* bitmap; struct TYPE_7__* description; int /*<<< orphan*/  base_error_code; void* end; int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_BAD_BLOCK_MARK ; 
 int /*<<< orphan*/  EXT2_ET_BAD_GENERIC_MARK ; 
 int /*<<< orphan*/  EXT2_ET_BAD_INODE_MARK ; 
#define  EXT2_ET_MAGIC_BLOCK_BITMAP 129 
#define  EXT2_ET_MAGIC_INODE_BITMAP 128 
 int /*<<< orphan*/  ext2fs_free_mem (TYPE_1__**) ; 
 int ext2fs_get_mem (size_t,TYPE_1__**) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strcpy (TYPE_1__*,char const*) ; 
 int strlen (char const*) ; 

errcode_t ext2fs_make_generic_bitmap(errcode_t magic, ext2_filsys fs,
				     __u32 start, __u32 end, __u32 real_end,
				     const char *descr, char *init_map,
				     ext2fs_generic_bitmap *ret)
{
	ext2fs_generic_bitmap_32 bitmap;
	errcode_t		retval;
	size_t			size;

	retval = ext2fs_get_mem(sizeof(struct ext2fs_struct_generic_bitmap_32),
				&bitmap);
	if (retval)
		return retval;

	bitmap->magic = magic;
	bitmap->fs = fs;
	bitmap->start = start;
	bitmap->end = end;
	bitmap->real_end = real_end;
	switch (magic) {
	case EXT2_ET_MAGIC_INODE_BITMAP:
		bitmap->base_error_code = EXT2_ET_BAD_INODE_MARK;
		break;
	case EXT2_ET_MAGIC_BLOCK_BITMAP:
		bitmap->base_error_code = EXT2_ET_BAD_BLOCK_MARK;
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

	size = (size_t) (((bitmap->real_end - bitmap->start) / 8) + 1);
	/* Round up to allow for the BT x86 instruction */
	size = (size + 7) & ~3;
	retval = ext2fs_get_mem(size, &bitmap->bitmap);
	if (retval) {
		ext2fs_free_mem(&bitmap->description);
		ext2fs_free_mem(&bitmap);
		return retval;
	}

	if (init_map)
		memcpy(bitmap->bitmap, init_map, size);
	else
		memset(bitmap->bitmap, 0, size);
	*ret = (ext2fs_generic_bitmap) bitmap;
	return 0;
}