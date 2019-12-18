#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  longlong_t ;

/* Variables and functions */
 size_t SPA_FEATURE_SPACEMAP_HISTOGRAM ; 
 int /*<<< orphan*/  feature_get_refcount (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ get_checkpoint_refcount (int /*<<< orphan*/ ) ; 
 scalar_t__ get_dtl_refcount (int /*<<< orphan*/ ) ; 
 scalar_t__ get_log_spacemap_refcount (TYPE_1__*) ; 
 scalar_t__ get_metaslab_refcount (int /*<<< orphan*/ ) ; 
 scalar_t__ get_obsolete_refcount (int /*<<< orphan*/ ) ; 
 scalar_t__ get_prev_obsolete_spacemap_refcount (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spa_feature_table ; 

__attribute__((used)) static int
verify_spacemap_refcounts(spa_t *spa)
{
	uint64_t expected_refcount = 0;
	uint64_t actual_refcount;

	(void) feature_get_refcount(spa,
	    &spa_feature_table[SPA_FEATURE_SPACEMAP_HISTOGRAM],
	    &expected_refcount);
	actual_refcount = get_dtl_refcount(spa->spa_root_vdev);
	actual_refcount += get_metaslab_refcount(spa->spa_root_vdev);
	actual_refcount += get_obsolete_refcount(spa->spa_root_vdev);
	actual_refcount += get_prev_obsolete_spacemap_refcount(spa);
	actual_refcount += get_checkpoint_refcount(spa->spa_root_vdev);
	actual_refcount += get_log_spacemap_refcount(spa);

	if (expected_refcount != actual_refcount) {
		(void) printf("space map refcount mismatch: expected %lld != "
		    "actual %lld\n",
		    (longlong_t)expected_refcount,
		    (longlong_t)actual_refcount);
		return (2);
	}
	return (0);
}