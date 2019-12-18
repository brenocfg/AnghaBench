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
struct dir_context {int flags; char* buf; int (* func ) (int /*<<< orphan*/ ,int,struct ext2_dir_entry*,int,int,char*,void*) ;scalar_t__ errcode; void* priv_data; int /*<<< orphan*/  dir; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  TYPE_1__* ext2_filsys ;
typedef  scalar_t__ errcode_t ;
struct TYPE_7__ {int /*<<< orphan*/  blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_READ_ONLY ; 
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_ET_INLINE_DATA_CANT_ITERATE ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 scalar_t__ ext2fs_block_iterate3 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dir_context*) ; 
 scalar_t__ ext2fs_check_directory (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2fs_free_mem (char**) ; 
 scalar_t__ ext2fs_get_mem (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  ext2fs_inline_data_dir_iterate (TYPE_1__*,int /*<<< orphan*/ ,struct dir_context*) ; 
 int /*<<< orphan*/  ext2fs_process_dir_block ; 

errcode_t ext2fs_dir_iterate2(ext2_filsys fs,
			      ext2_ino_t dir,
			      int flags,
			      char *block_buf,
			      int (*func)(ext2_ino_t	dir,
					  int		entry,
					  struct ext2_dir_entry *dirent,
					  int	offset,
					  int	blocksize,
					  char	*buf,
					  void	*priv_data),
			      void *priv_data)
{
	struct		dir_context	ctx;
	errcode_t	retval;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	retval = ext2fs_check_directory(fs, dir);
	if (retval)
		return retval;

	ctx.dir = dir;
	ctx.flags = flags;
	if (block_buf)
		ctx.buf = block_buf;
	else {
		retval = ext2fs_get_mem(fs->blocksize, &ctx.buf);
		if (retval)
			return retval;
	}
	ctx.func = func;
	ctx.priv_data = priv_data;
	ctx.errcode = 0;
	retval = ext2fs_block_iterate3(fs, dir, BLOCK_FLAG_READ_ONLY, 0,
				       ext2fs_process_dir_block, &ctx);
	if (!block_buf)
		ext2fs_free_mem(&ctx.buf);
	if (retval == EXT2_ET_INLINE_DATA_CANT_ITERATE) {
		(void) ext2fs_inline_data_dir_iterate(fs, dir, &ctx);
		retval = 0;
	}
	if (retval)
		return retval;
	return ctx.errcode;
}