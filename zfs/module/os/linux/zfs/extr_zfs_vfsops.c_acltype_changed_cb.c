#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int z_acl_type; TYPE_1__* z_sb; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  s_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_POSIXACL ; 
#define  ZFS_ACLTYPE_OFF 129 
#define  ZFS_ACLTYPE_POSIXACL 128 

__attribute__((used)) static void
acltype_changed_cb(void *arg, uint64_t newval)
{
	zfsvfs_t *zfsvfs = arg;

	switch (newval) {
	case ZFS_ACLTYPE_OFF:
		zfsvfs->z_acl_type = ZFS_ACLTYPE_OFF;
		zfsvfs->z_sb->s_flags &= ~SB_POSIXACL;
		break;
	case ZFS_ACLTYPE_POSIXACL:
#ifdef CONFIG_FS_POSIX_ACL
		zfsvfs->z_acl_type = ZFS_ACLTYPE_POSIXACL;
		zfsvfs->z_sb->s_flags |= SB_POSIXACL;
#else
		zfsvfs->z_acl_type = ZFS_ACLTYPE_OFF;
		zfsvfs->z_sb->s_flags &= ~SB_POSIXACL;
#endif /* CONFIG_FS_POSIX_ACL */
		break;
	default:
		break;
	}
}