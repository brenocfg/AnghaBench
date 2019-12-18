#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint64_t ;
struct TYPE_26__ {void** os_next_write_raw; TYPE_1__* os_phys; int /*<<< orphan*/  os_phys_buf; } ;
typedef  TYPE_2__ objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_27__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_3__ dsl_pool_t ;
struct TYPE_28__ {int /*<<< orphan*/  ds_dbuf; int /*<<< orphan*/  ds_bp_rwlock; } ;
typedef  TYPE_4__ dsl_dataset_t ;
struct TYPE_29__ {int /*<<< orphan*/  dn_struct_rwlock; void* dn_checksum; void* dn_compress; } ;
typedef  TYPE_5__ dnode_t ;
struct TYPE_30__ {size_t tx_txg; TYPE_3__* tx_pool; } ;
typedef  TYPE_6__ dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_objset_type_t ;
typedef  void* boolean_t ;
struct TYPE_25__ {int /*<<< orphan*/  os_local_mac; int /*<<< orphan*/  os_portable_mac; } ;

/* Variables and functions */
 scalar_t__ BP_IS_HOLE (int /*<<< orphan*/ ) ; 
 void* B_FALSE ; 
 void* B_TRUE ; 
 TYPE_5__* DMU_META_DNODE (TYPE_2__*) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 size_t TXG_MASK ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_FLAG_MUSTSUCCEED ; 
 int /*<<< orphan*/  ZIO_OBJSET_MAC_LEN ; 
 int /*<<< orphan*/  arc_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_add_ref (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dmu_objset_create_impl_dnstats (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,void*,TYPE_6__*) ; 
 int /*<<< orphan*/  dmu_objset_from_ds (TYPE_4__*,TYPE_2__**) ; 
 int /*<<< orphan*/  dnode_new_blkid (TYPE_5__*,void*,TYPE_6__*,void*,void*) ; 
 int /*<<< orphan*/  dsl_dataset_dirty (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  dsl_dataset_get_blkptr (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_dataset_sync (TYPE_4__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  dsl_dataset_sync_done (TYPE_4__*,TYPE_6__*) ; 
 void* fnvlist_lookup_uint64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_lookup_uint8_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zio_root (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_crypto_recv_raw_objset_sync(dsl_dataset_t *ds, dmu_objset_type_t ostype,
    nvlist_t *nvl, dmu_tx_t *tx)
{
	dsl_pool_t *dp = tx->tx_pool;
	objset_t *os;
	dnode_t *mdn;
	zio_t *zio;
	uint8_t *portable_mac;
	uint_t len;
	uint64_t compress, checksum, nlevels, blksz, ibs, maxblkid;
	boolean_t newds = B_FALSE;

	VERIFY0(dmu_objset_from_ds(ds, &os));
	mdn = DMU_META_DNODE(os);

	/*
	 * Fetch the values we need from the nvlist. "to_ivset_guid" must
	 * be set on the snapshot, which doesn't exist yet. The receive
	 * code will take care of this for us later.
	 */
	compress = fnvlist_lookup_uint64(nvl, "mdn_compress");
	checksum = fnvlist_lookup_uint64(nvl, "mdn_checksum");
	nlevels = fnvlist_lookup_uint64(nvl, "mdn_nlevels");
	blksz = fnvlist_lookup_uint64(nvl, "mdn_blksz");
	ibs = fnvlist_lookup_uint64(nvl, "mdn_indblkshift");
	maxblkid = fnvlist_lookup_uint64(nvl, "mdn_maxblkid");
	VERIFY0(nvlist_lookup_uint8_array(nvl, "portable_mac", &portable_mac,
	    &len));

	/* if we haven't created an objset for the ds yet, do that now */
	rrw_enter(&ds->ds_bp_rwlock, RW_READER, FTAG);
	if (BP_IS_HOLE(dsl_dataset_get_blkptr(ds))) {
		(void) dmu_objset_create_impl_dnstats(dp->dp_spa, ds,
		    dsl_dataset_get_blkptr(ds), ostype, nlevels, blksz,
		    ibs, tx);
		newds = B_TRUE;
	}
	rrw_exit(&ds->ds_bp_rwlock, FTAG);

	/*
	 * Set the portable MAC. The local MAC will always be zero since the
	 * incoming data will all be portable and user accounting will be
	 * deferred until the next mount. Afterwards, flag the os to be
	 * written out raw next time.
	 */
	arc_release(os->os_phys_buf, &os->os_phys_buf);
	bcopy(portable_mac, os->os_phys->os_portable_mac, ZIO_OBJSET_MAC_LEN);
	bzero(os->os_phys->os_local_mac, ZIO_OBJSET_MAC_LEN);
	os->os_next_write_raw[tx->tx_txg & TXG_MASK] = B_TRUE;

	/* set metadnode compression and checksum */
	mdn->dn_compress = compress;
	mdn->dn_checksum = checksum;

	rw_enter(&mdn->dn_struct_rwlock, RW_WRITER);
	dnode_new_blkid(mdn, maxblkid, tx, B_FALSE, B_TRUE);
	rw_exit(&mdn->dn_struct_rwlock);

	/*
	 * We can't normally dirty the dataset in syncing context unless
	 * we are creating a new dataset. In this case, we perform a
	 * pseudo txg sync here instead.
	 */
	if (newds) {
		dsl_dataset_dirty(ds, tx);
	} else {
		zio = zio_root(dp->dp_spa, NULL, NULL, ZIO_FLAG_MUSTSUCCEED);
		dsl_dataset_sync(ds, zio, tx);
		VERIFY0(zio_wait(zio));

		/* dsl_dataset_sync_done will drop this reference. */
		dmu_buf_add_ref(ds->ds_dbuf, ds);
		dsl_dataset_sync_done(ds, tx);
	}
}