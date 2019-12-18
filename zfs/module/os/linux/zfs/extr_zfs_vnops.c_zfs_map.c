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
struct TYPE_4__ {int z_pflags; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct inode {int dummy; } ;
typedef  scalar_t__ offset_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EPERM ; 
 TYPE_1__* ITOZ (struct inode*) ; 
 int /*<<< orphan*/ * ITOZSB (struct inode*) ; 
 scalar_t__ MAXOFFSET_T ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 unsigned long VM_EXEC ; 
 unsigned long VM_READ ; 
 unsigned long VM_WRITE ; 
 int ZFS_APPENDONLY ; 
 int ZFS_AV_QUARANTINED ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int ZFS_IMMUTABLE ; 
 int ZFS_READONLY ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 

int
zfs_map(struct inode *ip, offset_t off, caddr_t *addrp, size_t len,
    unsigned long vm_flags)
{
	znode_t  *zp = ITOZ(ip);
	zfsvfs_t *zfsvfs = ITOZSB(ip);

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	if ((vm_flags & VM_WRITE) && (zp->z_pflags &
	    (ZFS_IMMUTABLE | ZFS_READONLY | ZFS_APPENDONLY))) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EPERM));
	}

	if ((vm_flags & (VM_READ | VM_EXEC)) &&
	    (zp->z_pflags & ZFS_AV_QUARANTINED)) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EACCES));
	}

	if (off < 0 || len > MAXOFFSET_T - off) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(ENXIO));
	}

	ZFS_EXIT(zfsvfs);
	return (0);
}