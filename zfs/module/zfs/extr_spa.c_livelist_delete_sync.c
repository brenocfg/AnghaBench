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
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {scalar_t__ spa_livelists_to_delete; int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_6__ {scalar_t__ ll_obj; scalar_t__ zap_obj; TYPE_1__* spa; } ;
typedef  TYPE_2__ livelist_delete_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_POOL_DELETED_CLONES ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  SPA_FEATURE_LIVELIST ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_deadlist_free (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_decr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_notify_waiters (TYPE_1__*) ; 
 int /*<<< orphan*/  zap_count (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  zap_destroy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_remove_int (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
livelist_delete_sync(void *arg, dmu_tx_t *tx)
{
	livelist_delete_arg_t *lda = arg;
	spa_t *spa = lda->spa;
	uint64_t ll_obj = lda->ll_obj;
	uint64_t zap_obj = lda->zap_obj;
	objset_t *mos = spa->spa_meta_objset;
	uint64_t count;

	/* free the livelist and decrement the feature count */
	VERIFY0(zap_remove_int(mos, zap_obj, ll_obj, tx));
	dsl_deadlist_free(mos, ll_obj, tx);
	spa_feature_decr(spa, SPA_FEATURE_LIVELIST, tx);
	VERIFY0(zap_count(mos, zap_obj, &count));
	if (count == 0) {
		/* no more livelists to delete */
		VERIFY0(zap_remove(mos, DMU_POOL_DIRECTORY_OBJECT,
		    DMU_POOL_DELETED_CLONES, tx));
		VERIFY0(zap_destroy(mos, zap_obj, tx));
		spa->spa_livelists_to_delete = 0;
		spa_notify_waiters(spa);
	}
}