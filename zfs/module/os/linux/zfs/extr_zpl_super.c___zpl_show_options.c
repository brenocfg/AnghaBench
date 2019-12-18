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
struct TYPE_3__ {int z_flags; int z_acl_type; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct seq_file {int dummy; } ;

/* Variables and functions */
#define  ZFS_ACLTYPE_POSIXACL 128 
 int ZSB_XATTR ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int
__zpl_show_options(struct seq_file *seq, zfsvfs_t *zfsvfs)
{
	seq_printf(seq, ",%s",
	    zfsvfs->z_flags & ZSB_XATTR ? "xattr" : "noxattr");

#ifdef CONFIG_FS_POSIX_ACL
	switch (zfsvfs->z_acl_type) {
	case ZFS_ACLTYPE_POSIXACL:
		seq_puts(seq, ",posixacl");
		break;
	default:
		seq_puts(seq, ",noacl");
		break;
	}
#endif /* CONFIG_FS_POSIX_ACL */

	return (0);
}