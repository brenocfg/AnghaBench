#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  sk_dsl_keys; int /*<<< orphan*/  sk_dk_lock; } ;
struct TYPE_9__ {TYPE_1__ spa_keystore; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_10__ {int /*<<< orphan*/  dck_holds; int /*<<< orphan*/  dck_obj; } ;
typedef  TYPE_3__ dsl_crypto_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_3__* avl_find (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_add (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int
spa_keystore_dsl_key_hold_impl(spa_t *spa, uint64_t dckobj, void *tag,
    dsl_crypto_key_t **dck_out)
{
	int ret;
	dsl_crypto_key_t search_dck;
	dsl_crypto_key_t *found_dck;

	ASSERT(RW_LOCK_HELD(&spa->spa_keystore.sk_dk_lock));

	/* init the search key */
	search_dck.dck_obj = dckobj;

	/* find the matching key in the keystore */
	found_dck = avl_find(&spa->spa_keystore.sk_dsl_keys, &search_dck, NULL);
	if (!found_dck) {
		ret = SET_ERROR(ENOENT);
		goto error;
	}

	/* increment the refcount */
	zfs_refcount_add(&found_dck->dck_holds, tag);

	*dck_out = found_dck;
	return (0);

error:
	*dck_out = NULL;
	return (ret);
}