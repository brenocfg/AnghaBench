#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  z_sb; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
struct inode_operations {int dummy; } ;
struct inode {int dummy; } ;
struct file_operations {int dummy; } ;

/* Variables and functions */
 struct inode* ilookup (int /*<<< orphan*/ ,unsigned long) ; 
 struct inode* zfsctl_inode_alloc (TYPE_1__*,scalar_t__,struct file_operations const*,struct inode_operations const*) ; 

__attribute__((used)) static struct inode *
zfsctl_inode_lookup(zfsvfs_t *zfsvfs, uint64_t id,
    const struct file_operations *fops, const struct inode_operations *ops)
{
	struct inode *ip = NULL;

	while (ip == NULL) {
		ip = ilookup(zfsvfs->z_sb, (unsigned long)id);
		if (ip)
			break;

		/* May fail due to concurrent zfsctl_inode_alloc() */
		ip = zfsctl_inode_alloc(zfsvfs, id, fops, ops);
	}

	return (ip);
}