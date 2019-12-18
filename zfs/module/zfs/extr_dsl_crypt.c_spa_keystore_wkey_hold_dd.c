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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  sk_wkeys_lock; } ;
struct TYPE_6__ {TYPE_1__ spa_keystore; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  dsl_wrapping_key_t ;
typedef  int /*<<< orphan*/  dsl_dir_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int dsl_dir_get_encryption_root_ddobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int spa_keystore_wkey_hold_ddobj_impl (TYPE_2__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
spa_keystore_wkey_hold_dd(spa_t *spa, dsl_dir_t *dd, void *tag,
    dsl_wrapping_key_t **wkey_out)
{
	int ret;
	dsl_wrapping_key_t *wkey;
	uint64_t rddobj;
	boolean_t locked = B_FALSE;

	if (!RW_WRITE_HELD(&spa->spa_keystore.sk_wkeys_lock)) {
		rw_enter(&spa->spa_keystore.sk_wkeys_lock, RW_READER);
		locked = B_TRUE;
	}

	/* get the ddobj that the keylocation property was inherited from */
	ret = dsl_dir_get_encryption_root_ddobj(dd, &rddobj);
	if (ret != 0)
		goto error;

	/* lookup the wkey in the avl tree */
	ret = spa_keystore_wkey_hold_ddobj_impl(spa, rddobj, tag, &wkey);
	if (ret != 0)
		goto error;

	/* unlock the wkey tree if we locked it */
	if (locked)
		rw_exit(&spa->spa_keystore.sk_wkeys_lock);

	*wkey_out = wkey;
	return (0);

error:
	if (locked)
		rw_exit(&spa->spa_keystore.sk_wkeys_lock);

	*wkey_out = NULL;
	return (ret);
}