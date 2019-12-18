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
struct TYPE_9__ {int /*<<< orphan*/  sk_wkeys_lock; int /*<<< orphan*/  sk_wkeys; } ;
struct TYPE_10__ {TYPE_1__ spa_keystore; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_11__ {int /*<<< orphan*/  wk_refcnt; int /*<<< orphan*/  wk_ddobj; } ;
typedef  TYPE_3__ dsl_wrapping_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_3__* avl_find (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_wrapping_key_free (TYPE_3__*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

int
spa_keystore_unload_wkey_impl(spa_t *spa, uint64_t ddobj)
{
	int ret;
	dsl_wrapping_key_t search_wkey;
	dsl_wrapping_key_t *found_wkey;

	/* init the search wrapping key */
	search_wkey.wk_ddobj = ddobj;

	rw_enter(&spa->spa_keystore.sk_wkeys_lock, RW_WRITER);

	/* remove the wrapping key from the keystore */
	found_wkey = avl_find(&spa->spa_keystore.sk_wkeys,
	    &search_wkey, NULL);
	if (!found_wkey) {
		ret = SET_ERROR(EACCES);
		goto error_unlock;
	} else if (zfs_refcount_count(&found_wkey->wk_refcnt) != 0) {
		ret = SET_ERROR(EBUSY);
		goto error_unlock;
	}
	avl_remove(&spa->spa_keystore.sk_wkeys, found_wkey);

	rw_exit(&spa->spa_keystore.sk_wkeys_lock);

	/* free the wrapping key */
	dsl_wrapping_key_free(found_wkey);

	return (0);

error_unlock:
	rw_exit(&spa->spa_keystore.sk_wkeys_lock);
	return (ret);
}