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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  sk_km_lock; int /*<<< orphan*/  sk_key_mappings; } ;
struct TYPE_10__ {TYPE_1__ spa_keystore; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_11__ {TYPE_4__* km_key; int /*<<< orphan*/  km_dsobj; } ;
typedef  TYPE_3__ dsl_key_mapping_t ;
struct TYPE_12__ {int /*<<< orphan*/  dck_holds; } ;
typedef  TYPE_4__ dsl_crypto_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_3__* avl_find (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_add (int /*<<< orphan*/ *,void*) ; 

int
spa_keystore_lookup_key(spa_t *spa, uint64_t dsobj, void *tag,
    dsl_crypto_key_t **dck_out)
{
	int ret;
	dsl_key_mapping_t search_km;
	dsl_key_mapping_t *found_km;

	ASSERT((tag != NULL && dck_out != NULL) ||
	    (tag == NULL && dck_out == NULL));

	/* init the search key mapping */
	search_km.km_dsobj = dsobj;

	rw_enter(&spa->spa_keystore.sk_km_lock, RW_READER);

	/* remove the mapping from the tree */
	found_km = avl_find(&spa->spa_keystore.sk_key_mappings, &search_km,
	    NULL);
	if (found_km == NULL) {
		ret = SET_ERROR(ENOENT);
		goto error_unlock;
	}

	if (found_km && tag)
		zfs_refcount_add(&found_km->km_key->dck_holds, tag);

	rw_exit(&spa->spa_keystore.sk_km_lock);

	if (dck_out != NULL)
		*dck_out = found_km->km_key;
	return (0);

error_unlock:
	rw_exit(&spa->spa_keystore.sk_km_lock);

	if (dck_out != NULL)
		*dck_out = NULL;
	return (ret);
}