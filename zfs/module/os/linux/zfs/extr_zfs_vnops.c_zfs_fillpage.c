#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  z_id; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_6__ {int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  scalar_t__ u_offset_t ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_READ_PREFETCH ; 
 int ECKSUM ; 
 int /*<<< orphan*/  EIO ; 
 TYPE_1__* ITOZ (struct inode*) ; 
 TYPE_2__* ITOZSB (struct inode*) ; 
 scalar_t__ PAGESIZE ; 
 int PAGE_SHIFT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dmu_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 scalar_t__ page_offset (struct page*) ; 

__attribute__((used)) static int
zfs_fillpage(struct inode *ip, struct page *pl[], int nr_pages)
{
	znode_t *zp = ITOZ(ip);
	zfsvfs_t *zfsvfs = ITOZSB(ip);
	objset_t *os;
	struct page *cur_pp;
	u_offset_t io_off, total;
	size_t io_len;
	loff_t i_size;
	unsigned page_idx;
	int err;

	os = zfsvfs->z_os;
	io_len = nr_pages << PAGE_SHIFT;
	i_size = i_size_read(ip);
	io_off = page_offset(pl[0]);

	if (io_off + io_len > i_size)
		io_len = i_size - io_off;

	/*
	 * Iterate over list of pages and read each page individually.
	 */
	page_idx = 0;
	for (total = io_off + io_len; io_off < total; io_off += PAGESIZE) {
		caddr_t va;

		cur_pp = pl[page_idx++];
		va = kmap(cur_pp);
		err = dmu_read(os, zp->z_id, io_off, PAGESIZE, va,
		    DMU_READ_PREFETCH);
		kunmap(cur_pp);
		if (err) {
			/* convert checksum errors into IO errors */
			if (err == ECKSUM)
				err = SET_ERROR(EIO);
			return (err);
		}
	}

	return (0);
}