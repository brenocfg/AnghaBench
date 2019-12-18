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
struct TYPE_3__ {int /*<<< orphan*/ * vfs_mntpoint; void* vfs_do_nbmand; void* vfs_nbmand; void* vfs_do_relatime; void* vfs_relatime; void* vfs_do_atime; void* vfs_atime; void* vfs_do_xattr; void* vfs_xattr; void* vfs_do_devices; void* vfs_devices; void* vfs_do_exec; void* vfs_exec; void* vfs_do_setuid; void* vfs_setuid; void* vfs_do_readonly; void* vfs_readonly; } ;
typedef  TYPE_1__ vfs_t ;
typedef  int /*<<< orphan*/  substring_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
#define  TOKEN_ATIME 146 
#define  TOKEN_DEVICES 145 
#define  TOKEN_DIRXATTR 144 
#define  TOKEN_EXEC 143 
#define  TOKEN_MNTPOINT 142 
#define  TOKEN_NBMAND 141 
#define  TOKEN_NOATIME 140 
#define  TOKEN_NODEVICES 139 
#define  TOKEN_NOEXEC 138 
#define  TOKEN_NONBMAND 137 
#define  TOKEN_NORELATIME 136 
#define  TOKEN_NOSETUID 135 
#define  TOKEN_NOXATTR 134 
#define  TOKEN_RELATIME 133 
#define  TOKEN_RO 132 
#define  TOKEN_RW 131 
#define  TOKEN_SAXATTR 130 
#define  TOKEN_SETUID 129 
#define  TOKEN_XATTR 128 
 void* ZFS_XATTR_DIR ; 
 void* ZFS_XATTR_OFF ; 
 void* ZFS_XATTR_SA ; 
 int /*<<< orphan*/ * match_strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfsvfs_parse_option(char *option, int token, substring_t *args, vfs_t *vfsp)
{
	switch (token) {
	case TOKEN_RO:
		vfsp->vfs_readonly = B_TRUE;
		vfsp->vfs_do_readonly = B_TRUE;
		break;
	case TOKEN_RW:
		vfsp->vfs_readonly = B_FALSE;
		vfsp->vfs_do_readonly = B_TRUE;
		break;
	case TOKEN_SETUID:
		vfsp->vfs_setuid = B_TRUE;
		vfsp->vfs_do_setuid = B_TRUE;
		break;
	case TOKEN_NOSETUID:
		vfsp->vfs_setuid = B_FALSE;
		vfsp->vfs_do_setuid = B_TRUE;
		break;
	case TOKEN_EXEC:
		vfsp->vfs_exec = B_TRUE;
		vfsp->vfs_do_exec = B_TRUE;
		break;
	case TOKEN_NOEXEC:
		vfsp->vfs_exec = B_FALSE;
		vfsp->vfs_do_exec = B_TRUE;
		break;
	case TOKEN_DEVICES:
		vfsp->vfs_devices = B_TRUE;
		vfsp->vfs_do_devices = B_TRUE;
		break;
	case TOKEN_NODEVICES:
		vfsp->vfs_devices = B_FALSE;
		vfsp->vfs_do_devices = B_TRUE;
		break;
	case TOKEN_DIRXATTR:
		vfsp->vfs_xattr = ZFS_XATTR_DIR;
		vfsp->vfs_do_xattr = B_TRUE;
		break;
	case TOKEN_SAXATTR:
		vfsp->vfs_xattr = ZFS_XATTR_SA;
		vfsp->vfs_do_xattr = B_TRUE;
		break;
	case TOKEN_XATTR:
		vfsp->vfs_xattr = ZFS_XATTR_DIR;
		vfsp->vfs_do_xattr = B_TRUE;
		break;
	case TOKEN_NOXATTR:
		vfsp->vfs_xattr = ZFS_XATTR_OFF;
		vfsp->vfs_do_xattr = B_TRUE;
		break;
	case TOKEN_ATIME:
		vfsp->vfs_atime = B_TRUE;
		vfsp->vfs_do_atime = B_TRUE;
		break;
	case TOKEN_NOATIME:
		vfsp->vfs_atime = B_FALSE;
		vfsp->vfs_do_atime = B_TRUE;
		break;
	case TOKEN_RELATIME:
		vfsp->vfs_relatime = B_TRUE;
		vfsp->vfs_do_relatime = B_TRUE;
		break;
	case TOKEN_NORELATIME:
		vfsp->vfs_relatime = B_FALSE;
		vfsp->vfs_do_relatime = B_TRUE;
		break;
	case TOKEN_NBMAND:
		vfsp->vfs_nbmand = B_TRUE;
		vfsp->vfs_do_nbmand = B_TRUE;
		break;
	case TOKEN_NONBMAND:
		vfsp->vfs_nbmand = B_FALSE;
		vfsp->vfs_do_nbmand = B_TRUE;
		break;
	case TOKEN_MNTPOINT:
		vfsp->vfs_mntpoint = match_strdup(&args[0]);
		if (vfsp->vfs_mntpoint == NULL)
			return (SET_ERROR(ENOMEM));

		break;
	default:
		break;
	}

	return (0);
}