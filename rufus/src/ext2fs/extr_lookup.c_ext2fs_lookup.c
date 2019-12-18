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
struct lookup_struct {char const* name; int len; scalar_t__ found; int /*<<< orphan*/ * inode; } ;
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  scalar_t__ errcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_CHECK_MAGIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EXT2_ET_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  EXT2_ET_MAGIC_EXT2FS_FILSYS ; 
 scalar_t__ ext2fs_dir_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct lookup_struct*) ; 
 int /*<<< orphan*/  lookup_proc ; 

errcode_t ext2fs_lookup(ext2_filsys fs, ext2_ino_t dir, const char *name,
			int namelen, char *buf, ext2_ino_t *inode)
{
	errcode_t	retval;
	struct lookup_struct ls;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	ls.name = name;
	ls.len = namelen;
	ls.inode = inode;
	ls.found = 0;

	retval = ext2fs_dir_iterate(fs, dir, 0, buf, lookup_proc, &ls);
	if (retval)
		return retval;

	return (ls.found) ? 0 : EXT2_ET_FILE_NOT_FOUND;
}