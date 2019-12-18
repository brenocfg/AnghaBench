#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ z_relatime; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  uio_seg_t ;
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int dummy; } ;
struct file {unsigned int f_flags; TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CRED () ; 
 int /*<<< orphan*/  IS_NOATIME (struct inode*) ; 
 int /*<<< orphan*/  ITOZ (struct inode*) ; 
 TYPE_2__* ZTOZSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 unsigned int zfs_io_flags (struct kiocb*) ; 
 scalar_t__ zfs_relatime_need_update (struct inode*) ; 
 int /*<<< orphan*/  zpl_read_common_iovec (struct inode*,struct iovec const*,size_t,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t
zpl_iter_read_common(struct kiocb *kiocb, const struct iovec *iovp,
    unsigned long nr_segs, size_t count, uio_seg_t seg, size_t skip)
{
	cred_t *cr = CRED();
	struct file *filp = kiocb->ki_filp;
	struct inode *ip = filp->f_mapping->host;
	zfsvfs_t *zfsvfs = ZTOZSB(ITOZ(ip));
	ssize_t read;
	unsigned int f_flags = filp->f_flags;

	f_flags |= zfs_io_flags(kiocb);
	crhold(cr);
	read = zpl_read_common_iovec(filp->f_mapping->host, iovp, count,
	    nr_segs, &kiocb->ki_pos, seg, f_flags, cr, skip);
	crfree(cr);

	/*
	 * If relatime is enabled, call file_accessed() only if
	 * zfs_relatime_need_update() is true.  This is needed since datasets
	 * with inherited "relatime" property aren't necessarily mounted with
	 * MNT_RELATIME flag (e.g. after `zfs set relatime=...`), which is what
	 * relatime test in VFS by relatime_need_update() is based on.
	 */
	if (!IS_NOATIME(ip) && zfsvfs->z_relatime) {
		if (zfs_relatime_need_update(ip))
			file_accessed(filp);
	} else {
		file_accessed(filp);
	}

	return (read);
}