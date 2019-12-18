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
struct TYPE_8__ {int /*<<< orphan*/  sk_dk_lock; int /*<<< orphan*/  sk_dsl_keys; } ;
struct TYPE_9__ {TYPE_1__ spa_keystore; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_10__ {int /*<<< orphan*/  dck_holds; } ;
typedef  TYPE_3__ dsl_crypto_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_crypto_key_free (TYPE_3__*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_refcount_remove (int /*<<< orphan*/ *,void*) ; 

void
spa_keystore_dsl_key_rele(spa_t *spa, dsl_crypto_key_t *dck, void *tag)
{
	rw_enter(&spa->spa_keystore.sk_dk_lock, RW_WRITER);

	if (zfs_refcount_remove(&dck->dck_holds, tag) == 0) {
		avl_remove(&spa->spa_keystore.sk_dsl_keys, dck);
		dsl_crypto_key_free(dck);
	}

	rw_exit(&spa->spa_keystore.sk_dk_lock);
}