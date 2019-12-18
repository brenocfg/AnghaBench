#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  sk_km_lock; int /*<<< orphan*/  sk_key_mappings; } ;
struct TYPE_18__ {TYPE_1__ spa_keystore; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_19__ {int /*<<< orphan*/  km_refcnt; int /*<<< orphan*/  km_key; int /*<<< orphan*/  km_dsobj; } ;
typedef  TYPE_3__ dsl_key_mapping_t ;
struct TYPE_20__ {int /*<<< orphan*/  ds_object; int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_4__ dsl_dataset_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  RW_WRITER ; 
 TYPE_3__* avl_find (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 TYPE_3__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int spa_keystore_dsl_key_hold_dd (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_keystore_dsl_key_rele (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_refcount_add (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zfs_refcount_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 

int
spa_keystore_create_mapping(spa_t *spa, dsl_dataset_t *ds, void *tag,
    dsl_key_mapping_t **km_out)
{
	int ret;
	avl_index_t where;
	dsl_key_mapping_t *km, *found_km;
	boolean_t should_free = B_FALSE;

	/* Allocate and initialize the mapping */
	km = kmem_zalloc(sizeof (dsl_key_mapping_t), KM_SLEEP);
	zfs_refcount_create(&km->km_refcnt);

	ret = spa_keystore_dsl_key_hold_dd(spa, ds->ds_dir, km, &km->km_key);
	if (ret != 0) {
		zfs_refcount_destroy(&km->km_refcnt);
		kmem_free(km, sizeof (dsl_key_mapping_t));

		if (km_out != NULL)
			*km_out = NULL;
		return (ret);
	}

	km->km_dsobj = ds->ds_object;

	rw_enter(&spa->spa_keystore.sk_km_lock, RW_WRITER);

	/*
	 * If a mapping already exists, simply increment its refcount and
	 * cleanup the one we made. We want to allocate / free outside of
	 * the lock because this lock is also used by the zio layer to lookup
	 * key mappings. Otherwise, use the one we created. Normally, there will
	 * only be one active reference at a time (the objset owner), but there
	 * are times when there could be multiple async users.
	 */
	found_km = avl_find(&spa->spa_keystore.sk_key_mappings, km, &where);
	if (found_km != NULL) {
		should_free = B_TRUE;
		zfs_refcount_add(&found_km->km_refcnt, tag);
		if (km_out != NULL)
			*km_out = found_km;
	} else {
		zfs_refcount_add(&km->km_refcnt, tag);
		avl_insert(&spa->spa_keystore.sk_key_mappings, km, where);
		if (km_out != NULL)
			*km_out = km;
	}

	rw_exit(&spa->spa_keystore.sk_km_lock);

	if (should_free) {
		spa_keystore_dsl_key_rele(spa, km->km_key, km);
		zfs_refcount_destroy(&km->km_refcnt);
		kmem_free(km, sizeof (dsl_key_mapping_t));
	}

	return (0);
}