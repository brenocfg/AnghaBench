#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_3__ {scalar_t__ doi_bonus_size; } ;
typedef  TYPE_1__ dmu_object_info_t ;

/* Variables and functions */
 scalar_t__ SPACE_MAP_SIZE_V0 ; 
 int /*<<< orphan*/  SPA_FEATURE_SPACEMAP_HISTOGRAM ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_object_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_object_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * dmu_objset_spa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_decr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
space_map_free_obj(objset_t *os, uint64_t smobj, dmu_tx_t *tx)
{
	spa_t *spa = dmu_objset_spa(os);
	if (spa_feature_is_enabled(spa, SPA_FEATURE_SPACEMAP_HISTOGRAM)) {
		dmu_object_info_t doi;

		VERIFY0(dmu_object_info(os, smobj, &doi));
		if (doi.doi_bonus_size != SPACE_MAP_SIZE_V0) {
			spa_feature_decr(spa,
			    SPA_FEATURE_SPACEMAP_HISTOGRAM, tx);
		}
	}

	VERIFY0(dmu_object_free(os, smobj, tx));
}