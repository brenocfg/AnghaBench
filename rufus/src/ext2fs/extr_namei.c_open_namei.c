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
typedef  int /*<<< orphan*/  ext2_ino_t ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  scalar_t__ errcode_t ;

/* Variables and functions */
 scalar_t__ dir_namei (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t,int,char*,char const**,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ follow_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static errcode_t open_namei(ext2_filsys fs, ext2_ino_t root, ext2_ino_t base,
			    const char *pathname, size_t pathlen, int follow,
			    int link_count, char *buf, ext2_ino_t *res_inode)
{
	const char *base_name;
	int namelen;
	ext2_ino_t dir, inode;
	errcode_t retval;

#ifdef NAMEI_DEBUG
	printf("open_namei: root=%lu, dir=%lu, path=%.*s, lc=%d\n",
	       root, base, pathlen, pathname, link_count);
#endif
	retval = dir_namei(fs, root, base, pathname, pathlen,
			   link_count, buf, &base_name, &namelen, &dir);
	if (retval) return retval;
	if (!namelen) {                     /* special case: '/usr/' etc */
		*res_inode=dir;
		return 0;
	}
	retval = ext2fs_lookup (fs, dir, base_name, namelen, buf, &inode);
	if (retval)
		return retval;
	if (follow) {
		retval = follow_link(fs, root, dir, inode, link_count,
				     buf, &inode);
		if (retval)
			return retval;
	}
#ifdef NAMEI_DEBUG
	printf("open_namei: (link_count=%d) returns %lu\n",
	       link_count, inode);
#endif
	*res_inode = inode;
	return 0;
}