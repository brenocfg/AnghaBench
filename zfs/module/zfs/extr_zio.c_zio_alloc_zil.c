#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_alloc_list_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_15__ {int spa_alloc_count; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_16__ {scalar_t__ os_encrypted; TYPE_1__* os_dsl_dataset; } ;
typedef  TYPE_3__ objset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_14__ {int /*<<< orphan*/  ds_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BP_SET_BYTEORDER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_CHECKSUM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_COMPRESS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_CRYPT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_DEDUP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_LEVEL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_LSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  BP_SET_PSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  BP_SET_TYPE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OT_INTENT_LOG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  METASLAB_FASTWRITE ; 
 scalar_t__ SPA_VERSION_SLIM_ZIL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_HOST_BYTEORDER ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_ZILOG ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_ZILOG2 ; 
 int /*<<< orphan*/  ZIO_COMPRESS_OFF ; 
 int ZIO_DATA_IV_LEN ; 
 int ZIO_DATA_SALT_LEN ; 
 int cityhash4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_id (TYPE_3__*) ; 
 int metaslab_alloc (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  metaslab_trace_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_trace_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_crypt_get_salt (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_log_class (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_name (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_normal_class (TYPE_2__*) ; 
 scalar_t__ spa_syncing_txg (TYPE_2__*) ; 
 scalar_t__ spa_version (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  zio_crypt_encode_params_bp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_crypt_generate_iv (int /*<<< orphan*/ *) ; 

int
zio_alloc_zil(spa_t *spa, objset_t *os, uint64_t txg, blkptr_t *new_bp,
    uint64_t size, boolean_t *slog)
{
	int error = 1;
	zio_alloc_list_t io_alloc_list;

	ASSERT(txg > spa_syncing_txg(spa));

	metaslab_trace_init(&io_alloc_list);

	/*
	 * Block pointer fields are useful to metaslabs for stats and debugging.
	 * Fill in the obvious ones before calling into metaslab_alloc().
	 */
	BP_SET_TYPE(new_bp, DMU_OT_INTENT_LOG);
	BP_SET_PSIZE(new_bp, size);
	BP_SET_LEVEL(new_bp, 0);

	/*
	 * When allocating a zil block, we don't have information about
	 * the final destination of the block except the objset it's part
	 * of, so we just hash the objset ID to pick the allocator to get
	 * some parallelism.
	 */
	error = metaslab_alloc(spa, spa_log_class(spa), size, new_bp, 1,
	    txg, NULL, METASLAB_FASTWRITE, &io_alloc_list, NULL,
	    cityhash4(0, 0, 0, os->os_dsl_dataset->ds_object) %
	    spa->spa_alloc_count);
	if (error == 0) {
		*slog = TRUE;
	} else {
		error = metaslab_alloc(spa, spa_normal_class(spa), size,
		    new_bp, 1, txg, NULL, METASLAB_FASTWRITE,
		    &io_alloc_list, NULL, cityhash4(0, 0, 0,
		    os->os_dsl_dataset->ds_object) % spa->spa_alloc_count);
		if (error == 0)
			*slog = FALSE;
	}
	metaslab_trace_fini(&io_alloc_list);

	if (error == 0) {
		BP_SET_LSIZE(new_bp, size);
		BP_SET_PSIZE(new_bp, size);
		BP_SET_COMPRESS(new_bp, ZIO_COMPRESS_OFF);
		BP_SET_CHECKSUM(new_bp,
		    spa_version(spa) >= SPA_VERSION_SLIM_ZIL
		    ? ZIO_CHECKSUM_ZILOG2 : ZIO_CHECKSUM_ZILOG);
		BP_SET_TYPE(new_bp, DMU_OT_INTENT_LOG);
		BP_SET_LEVEL(new_bp, 0);
		BP_SET_DEDUP(new_bp, 0);
		BP_SET_BYTEORDER(new_bp, ZFS_HOST_BYTEORDER);

		/*
		 * encrypted blocks will require an IV and salt. We generate
		 * these now since we will not be rewriting the bp at
		 * rewrite time.
		 */
		if (os->os_encrypted) {
			uint8_t iv[ZIO_DATA_IV_LEN];
			uint8_t salt[ZIO_DATA_SALT_LEN];

			BP_SET_CRYPT(new_bp, B_TRUE);
			VERIFY0(spa_crypt_get_salt(spa,
			    dmu_objset_id(os), salt));
			VERIFY0(zio_crypt_generate_iv(iv));

			zio_crypt_encode_params_bp(new_bp, salt, iv);
		}
	} else {
		zfs_dbgmsg("%s: zil block allocation failure: "
		    "size %llu, error %d", spa_name(spa), size, error);
	}

	return (error);
}