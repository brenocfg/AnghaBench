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
struct TYPE_4__ {int /*<<< orphan*/  sk_wkeys_lock; int /*<<< orphan*/  sk_wkeys; } ;
struct TYPE_5__ {TYPE_1__ spa_keystore; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  dsl_wrapping_key_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * avl_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

int
spa_keystore_load_wkey_impl(spa_t *spa, dsl_wrapping_key_t *wkey)
{
	int ret;
	avl_index_t where;
	dsl_wrapping_key_t *found_wkey;

	rw_enter(&spa->spa_keystore.sk_wkeys_lock, RW_WRITER);

	/* insert the wrapping key into the keystore */
	found_wkey = avl_find(&spa->spa_keystore.sk_wkeys, wkey, &where);
	if (found_wkey != NULL) {
		ret = SET_ERROR(EEXIST);
		goto error_unlock;
	}
	avl_insert(&spa->spa_keystore.sk_wkeys, wkey, where);

	rw_exit(&spa->spa_keystore.sk_wkeys_lock);

	return (0);

error_unlock:
	rw_exit(&spa->spa_keystore.sk_wkeys_lock);
	return (ret);
}