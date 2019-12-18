#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  size_t spa_feature_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_5__ {int /*<<< orphan*/ ** ds_feature; int /*<<< orphan*/  ds_object; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_7__ {int /*<<< orphan*/ * dp_meta_objset; int /*<<< orphan*/ * dp_spa; } ;
struct TYPE_6__ {int fi_flags; int /*<<< orphan*/  fi_guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int ZFEATURE_FLAG_PER_DATASET ; 
 TYPE_4__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_decr (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 TYPE_2__* spa_feature_table ; 
 int /*<<< orphan*/  zap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dsl_dataset_deactivate_feature_impl(dsl_dataset_t *ds, spa_feature_t f,
    dmu_tx_t *tx)
{
	spa_t *spa = dmu_tx_pool(tx)->dp_spa;
	objset_t *mos = dmu_tx_pool(tx)->dp_meta_objset;
	uint64_t dsobj = ds->ds_object;

	VERIFY(spa_feature_table[f].fi_flags & ZFEATURE_FLAG_PER_DATASET);

	VERIFY0(zap_remove(mos, dsobj, spa_feature_table[f].fi_guid, tx));
	spa_feature_decr(spa, f, tx);
	ds->ds_feature[f] = NULL;
}