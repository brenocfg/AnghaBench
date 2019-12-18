#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  spa_feature_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_dataset_deactivate_feature_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unload_zfeature (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
dsl_dataset_deactivate_feature(dsl_dataset_t *ds, spa_feature_t f, dmu_tx_t *tx)
{
	unload_zfeature(ds, f);
	dsl_dataset_deactivate_feature_impl(ds, f, tx);
}