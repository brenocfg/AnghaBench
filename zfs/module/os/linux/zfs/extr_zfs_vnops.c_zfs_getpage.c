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
typedef  int /*<<< orphan*/  znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct page {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ITOZ (struct inode*) ; 
 int /*<<< orphan*/ * ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (int /*<<< orphan*/ *) ; 
 int zfs_fillpage (struct inode*,struct page**,int) ; 

int
zfs_getpage(struct inode *ip, struct page *pl[], int nr_pages)
{
	znode_t	 *zp  = ITOZ(ip);
	zfsvfs_t *zfsvfs = ITOZSB(ip);
	int	 err;

	if (pl == NULL)
		return (0);

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	err = zfs_fillpage(ip, pl, nr_pages);

	ZFS_EXIT(zfsvfs);
	return (err);
}