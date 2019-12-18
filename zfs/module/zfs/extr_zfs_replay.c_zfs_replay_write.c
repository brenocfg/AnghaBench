#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ z_size; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_11__ {scalar_t__ z_replay_eof; } ;
typedef  TYPE_3__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {int lrc_reclen; } ;
struct TYPE_12__ {scalar_t__ lr_offset; scalar_t__ lr_length; int /*<<< orphan*/  lr_blkptr; TYPE_1__ lr_common; int /*<<< orphan*/  lr_foid; } ;
typedef  TYPE_4__ lr_write_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ BP_GET_LSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EIO ; 
 int ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  ZTOI (TYPE_2__*) ; 
 int /*<<< orphan*/  byteswap_uint64_array (TYPE_4__*,int) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcred ; 
 int zfs_zget (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int zpl_write_common (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_replay_write(void *arg1, void *arg2, boolean_t byteswap)
{
	zfsvfs_t *zfsvfs = arg1;
	lr_write_t *lr = arg2;
	char *data = (char *)(lr + 1);	/* data follows lr_write_t */
	znode_t	*zp;
	int error, written;
	uint64_t eod, offset, length;

	if (byteswap)
		byteswap_uint64_array(lr, sizeof (*lr));

	if ((error = zfs_zget(zfsvfs, lr->lr_foid, &zp)) != 0) {
		/*
		 * As we can log writes out of order, it's possible the
		 * file has been removed. In this case just drop the write
		 * and return success.
		 */
		if (error == ENOENT)
			error = 0;
		return (error);
	}

	offset = lr->lr_offset;
	length = lr->lr_length;
	eod = offset + length;	/* end of data for this write */

	/*
	 * This may be a write from a dmu_sync() for a whole block,
	 * and may extend beyond the current end of the file.
	 * We can't just replay what was written for this TX_WRITE as
	 * a future TX_WRITE2 may extend the eof and the data for that
	 * write needs to be there. So we write the whole block and
	 * reduce the eof. This needs to be done within the single dmu
	 * transaction created within vn_rdwr -> zfs_write. So a possible
	 * new end of file is passed through in zfsvfs->z_replay_eof
	 */

	zfsvfs->z_replay_eof = 0; /* 0 means don't change end of file */

	/* If it's a dmu_sync() block, write the whole block */
	if (lr->lr_common.lrc_reclen == sizeof (lr_write_t)) {
		uint64_t blocksize = BP_GET_LSIZE(&lr->lr_blkptr);
		if (length < blocksize) {
			offset -= offset % blocksize;
			length = blocksize;
		}
		if (zp->z_size < eod)
			zfsvfs->z_replay_eof = eod;
	}

	written = zpl_write_common(ZTOI(zp), data, length, &offset,
	    UIO_SYSSPACE, 0, kcred);
	if (written < 0)
		error = -written;
	else if (written < length)
		error = SET_ERROR(EIO); /* short write */

	iput(ZTOI(zp));
	zfsvfs->z_replay_eof = 0;	/* safety */

	return (error);
}