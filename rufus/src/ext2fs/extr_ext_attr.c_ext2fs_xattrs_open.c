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
struct ext2_xattr_handle {int capacity; TYPE_1__* fs; int /*<<< orphan*/  ino; scalar_t__ count; int /*<<< orphan*/  attrs; int /*<<< orphan*/  magic; } ;
struct ext2_xattr {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
struct TYPE_3__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_ET_MAGIC_EA_HANDLE ; 
 scalar_t__ EXT2_ET_MISSING_EA_FEATURE ; 
 int /*<<< orphan*/  ext2fs_free_mem (struct ext2_xattr_handle**) ; 
 scalar_t__ ext2fs_get_arrayzero (int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_get_memzero (int,struct ext2_xattr_handle**) ; 
 int /*<<< orphan*/  ext2fs_has_feature_inline_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_has_feature_xattr (int /*<<< orphan*/ ) ; 

errcode_t ext2fs_xattrs_open(ext2_filsys fs, ext2_ino_t ino,
			     struct ext2_xattr_handle **handle)
{
	struct ext2_xattr_handle *h;
	errcode_t err;

	if (!ext2fs_has_feature_xattr(fs->super) &&
	    !ext2fs_has_feature_inline_data(fs->super))
		return EXT2_ET_MISSING_EA_FEATURE;

	err = ext2fs_get_memzero(sizeof(*h), &h);
	if (err)
		return err;

	h->magic = EXT2_ET_MAGIC_EA_HANDLE;
	h->capacity = 4;
	err = ext2fs_get_arrayzero(h->capacity, sizeof(struct ext2_xattr),
				   &h->attrs);
	if (err) {
		ext2fs_free_mem(&h);
		return err;
	}
	h->count = 0;
	h->ino = ino;
	h->fs = fs;
	*handle = h;
	return 0;
}