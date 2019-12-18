#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ zs_blkid; scalar_t__ zs_pf_blkid; scalar_t__ zs_ipf_blkid; int /*<<< orphan*/  zs_lock; int /*<<< orphan*/  zs_atime; } ;
typedef  TYPE_2__ zstream_t ;
struct TYPE_12__ {TYPE_9__* zf_dnode; int /*<<< orphan*/  zf_lock; int /*<<< orphan*/  zf_stream; } ;
typedef  TYPE_3__ zfetch_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_13__ {int dn_datablkshift; int dn_indblkshift; int /*<<< orphan*/  dn_struct_rwlock; TYPE_1__* dn_objset; } ;
struct TYPE_10__ {int /*<<< orphan*/ * os_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_FLAG_PREDICTIVE_PREFETCH ; 
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 int MIN (scalar_t__,scalar_t__) ; 
 int P2ROUNDUP (scalar_t__,int) ; 
 int /*<<< orphan*/  RW_READER ; 
 int SPA_BLKPTRSHIFT ; 
 int /*<<< orphan*/  ZFETCHSTAT_BUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_PRIORITY_ASYNC_READ ; 
 int /*<<< orphan*/  dbuf_prefetch (TYPE_9__*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_zfetch_stream_create (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  gethrtime () ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_indirect_vdevs_loaded (int /*<<< orphan*/ *) ; 
 int zfetch_max_distance ; 
 int zfetch_max_idistance ; 
 int /*<<< orphan*/  zfetchstat_hits ; 
 int /*<<< orphan*/  zfetchstat_misses ; 
 scalar_t__ zfs_prefetch_disable ; 

void
dmu_zfetch(zfetch_t *zf, uint64_t blkid, uint64_t nblks, boolean_t fetch_data,
    boolean_t have_lock)
{
	zstream_t *zs;
	int64_t pf_start, ipf_start, ipf_istart, ipf_iend;
	int64_t pf_ahead_blks, max_blks;
	int epbs, max_dist_blks, pf_nblks, ipf_nblks;
	uint64_t end_of_access_blkid;
	end_of_access_blkid = blkid + nblks;
	spa_t *spa = zf->zf_dnode->dn_objset->os_spa;

	if (zfs_prefetch_disable)
		return;
	/*
	 * If we haven't yet loaded the indirect vdevs' mappings, we
	 * can only read from blocks that we carefully ensure are on
	 * concrete vdevs (or previously-loaded indirect vdevs).  So we
	 * can't allow the predictive prefetcher to attempt reads of other
	 * blocks (e.g. of the MOS's dnode object).
	 */
	if (!spa_indirect_vdevs_loaded(spa))
		return;

	/*
	 * As a fast path for small (single-block) files, ignore access
	 * to the first block.
	 */
	if (blkid == 0)
		return;

	if (!have_lock)
		rw_enter(&zf->zf_dnode->dn_struct_rwlock, RW_READER);
	mutex_enter(&zf->zf_lock);

	/*
	 * Find matching prefetch stream.  Depending on whether the accesses
	 * are block-aligned, first block of the new access may either follow
	 * the last block of the previous access, or be equal to it.
	 */
	for (zs = list_head(&zf->zf_stream); zs != NULL;
	    zs = list_next(&zf->zf_stream, zs)) {
		if (blkid == zs->zs_blkid || blkid + 1 == zs->zs_blkid) {
			mutex_enter(&zs->zs_lock);
			/*
			 * zs_blkid could have changed before we
			 * acquired zs_lock; re-check them here.
			 */
			if (blkid == zs->zs_blkid) {
				break;
			} else if (blkid + 1 == zs->zs_blkid) {
				blkid++;
				nblks--;
				if (nblks == 0) {
					/* Already prefetched this before. */
					mutex_exit(&zs->zs_lock);
					mutex_exit(&zf->zf_lock);
					if (!have_lock) {
						rw_exit(&zf->zf_dnode->
						    dn_struct_rwlock);
					}
					return;
				}
				break;
			}
			mutex_exit(&zs->zs_lock);
		}
	}

	if (zs == NULL) {
		/*
		 * This access is not part of any existing stream.  Create
		 * a new stream for it.
		 */
		ZFETCHSTAT_BUMP(zfetchstat_misses);

		dmu_zfetch_stream_create(zf, end_of_access_blkid);
		mutex_exit(&zf->zf_lock);
		if (!have_lock)
			rw_exit(&zf->zf_dnode->dn_struct_rwlock);
		return;
	}

	/*
	 * This access was to a block that we issued a prefetch for on
	 * behalf of this stream. Issue further prefetches for this stream.
	 *
	 * Normally, we start prefetching where we stopped
	 * prefetching last (zs_pf_blkid).  But when we get our first
	 * hit on this stream, zs_pf_blkid == zs_blkid, we don't
	 * want to prefetch the block we just accessed.  In this case,
	 * start just after the block we just accessed.
	 */
	pf_start = MAX(zs->zs_pf_blkid, end_of_access_blkid);

	/*
	 * Double our amount of prefetched data, but don't let the
	 * prefetch get further ahead than zfetch_max_distance.
	 */
	if (fetch_data) {
		max_dist_blks =
		    zfetch_max_distance >> zf->zf_dnode->dn_datablkshift;
		/*
		 * Previously, we were (zs_pf_blkid - blkid) ahead.  We
		 * want to now be double that, so read that amount again,
		 * plus the amount we are catching up by (i.e. the amount
		 * read just now).
		 */
		pf_ahead_blks = zs->zs_pf_blkid - blkid + nblks;
		max_blks = max_dist_blks - (pf_start - end_of_access_blkid);
		pf_nblks = MIN(pf_ahead_blks, max_blks);
	} else {
		pf_nblks = 0;
	}

	zs->zs_pf_blkid = pf_start + pf_nblks;

	/*
	 * Do the same for indirects, starting from where we stopped last,
	 * or where we will stop reading data blocks (and the indirects
	 * that point to them).
	 */
	ipf_start = MAX(zs->zs_ipf_blkid, zs->zs_pf_blkid);
	max_dist_blks = zfetch_max_idistance >> zf->zf_dnode->dn_datablkshift;
	/*
	 * We want to double our distance ahead of the data prefetch
	 * (or reader, if we are not prefetching data).  Previously, we
	 * were (zs_ipf_blkid - blkid) ahead.  To double that, we read
	 * that amount again, plus the amount we are catching up by
	 * (i.e. the amount read now + the amount of data prefetched now).
	 */
	pf_ahead_blks = zs->zs_ipf_blkid - blkid + nblks + pf_nblks;
	max_blks = max_dist_blks - (ipf_start - end_of_access_blkid);
	ipf_nblks = MIN(pf_ahead_blks, max_blks);
	zs->zs_ipf_blkid = ipf_start + ipf_nblks;

	epbs = zf->zf_dnode->dn_indblkshift - SPA_BLKPTRSHIFT;
	ipf_istart = P2ROUNDUP(ipf_start, 1 << epbs) >> epbs;
	ipf_iend = P2ROUNDUP(zs->zs_ipf_blkid, 1 << epbs) >> epbs;

	zs->zs_atime = gethrtime();
	zs->zs_blkid = end_of_access_blkid;
	mutex_exit(&zs->zs_lock);
	mutex_exit(&zf->zf_lock);

	/*
	 * dbuf_prefetch() is asynchronous (even when it needs to read
	 * indirect blocks), but we still prefer to drop our locks before
	 * calling it to reduce the time we hold them.
	 */

	for (int i = 0; i < pf_nblks; i++) {
		dbuf_prefetch(zf->zf_dnode, 0, pf_start + i,
		    ZIO_PRIORITY_ASYNC_READ, ARC_FLAG_PREDICTIVE_PREFETCH);
	}
	for (int64_t iblk = ipf_istart; iblk < ipf_iend; iblk++) {
		dbuf_prefetch(zf->zf_dnode, 1, iblk,
		    ZIO_PRIORITY_ASYNC_READ, ARC_FLAG_PREDICTIVE_PREFETCH);
	}
	if (!have_lock)
		rw_exit(&zf->zf_dnode->dn_struct_rwlock);
	ZFETCHSTAT_BUMP(zfetchstat_hits);
}