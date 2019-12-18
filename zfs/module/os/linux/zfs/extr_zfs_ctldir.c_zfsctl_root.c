#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode_t ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* z_ctldir; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZTOZSB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  zfs_has_ctldir (int /*<<< orphan*/ *) ; 

struct inode *
zfsctl_root(znode_t *zp)
{
	ASSERT(zfs_has_ctldir(zp));
	igrab(ZTOZSB(zp)->z_ctldir);
	return (ZTOZSB(zp)->z_ctldir);
}