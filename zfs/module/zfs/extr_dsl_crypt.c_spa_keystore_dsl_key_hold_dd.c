#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  sk_dk_lock; int /*<<< orphan*/  sk_dsl_keys; } ;
struct TYPE_10__ {TYPE_1__ spa_keystore; int /*<<< orphan*/  spa_meta_objset; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  dsl_wrapping_key_t ;
struct TYPE_11__ {int /*<<< orphan*/  dd_crypto_obj; } ;
typedef  TYPE_3__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dsl_crypto_key_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_crypto_key_free (int /*<<< orphan*/ *) ; 
 int dsl_crypto_key_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_wrapping_key_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int spa_keystore_dsl_key_hold_impl (TYPE_2__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 
 int spa_keystore_wkey_hold_dd (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
spa_keystore_dsl_key_hold_dd(spa_t *spa, dsl_dir_t *dd, void *tag,
    dsl_crypto_key_t **dck_out)
{
	int ret;
	avl_index_t where;
	dsl_crypto_key_t *dck_io = NULL, *dck_ks = NULL;
	dsl_wrapping_key_t *wkey = NULL;
	uint64_t dckobj = dd->dd_crypto_obj;

	/* Lookup the key in the tree of currently loaded keys */
	rw_enter(&spa->spa_keystore.sk_dk_lock, RW_READER);
	ret = spa_keystore_dsl_key_hold_impl(spa, dckobj, tag, &dck_ks);
	rw_exit(&spa->spa_keystore.sk_dk_lock);
	if (ret == 0) {
		*dck_out = dck_ks;
		return (0);
	}

	/* Lookup the wrapping key from the keystore */
	ret = spa_keystore_wkey_hold_dd(spa, dd, FTAG, &wkey);
	if (ret != 0) {
		*dck_out = NULL;
		return (SET_ERROR(EACCES));
	}

	/* Read the key from disk */
	ret = dsl_crypto_key_open(spa->spa_meta_objset, wkey, dckobj,
	    tag, &dck_io);
	if (ret != 0) {
		dsl_wrapping_key_rele(wkey, FTAG);
		*dck_out = NULL;
		return (ret);
	}

	/*
	 * Add the key to the keystore.  It may already exist if it was
	 * added while performing the read from disk.  In this case discard
	 * it and return the key from the keystore.
	 */
	rw_enter(&spa->spa_keystore.sk_dk_lock, RW_WRITER);
	ret = spa_keystore_dsl_key_hold_impl(spa, dckobj, tag, &dck_ks);
	if (ret != 0) {
		avl_find(&spa->spa_keystore.sk_dsl_keys, dck_io, &where);
		avl_insert(&spa->spa_keystore.sk_dsl_keys, dck_io, where);
		*dck_out = dck_io;
	} else {
		dsl_crypto_key_free(dck_io);
		*dck_out = dck_ks;
	}

	/* Release the wrapping key (the dsl key now has a reference to it) */
	dsl_wrapping_key_rele(wkey, FTAG);
	rw_exit(&spa->spa_keystore.sk_dk_lock);

	return (0);
}