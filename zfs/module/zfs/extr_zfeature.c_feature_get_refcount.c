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
struct TYPE_5__ {size_t fi_feature; } ;
typedef  TYPE_1__ zfeature_info_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__* spa_feat_refcount_cache; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_FEATURE_DISABLED ; 
 int /*<<< orphan*/  VALID_FEATURE_FID (size_t) ; 

int
feature_get_refcount(spa_t *spa, zfeature_info_t *feature, uint64_t *res)
{
	ASSERT(VALID_FEATURE_FID(feature->fi_feature));
	if (spa->spa_feat_refcount_cache[feature->fi_feature] ==
	    SPA_FEATURE_DISABLED) {
		return (SET_ERROR(ENOTSUP));
	}
	*res = spa->spa_feat_refcount_cache[feature->fi_feature];
	return (0);
}