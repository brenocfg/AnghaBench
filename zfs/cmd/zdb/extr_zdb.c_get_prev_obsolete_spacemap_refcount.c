#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  space_map_phys_t ;
struct TYPE_6__ {scalar_t__ scip_prev_obsolete_sm_object; } ;
struct TYPE_7__ {int /*<<< orphan*/  spa_meta_objset; TYPE_1__ spa_condensing_indirect_phys; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_8__ {int doi_bonus_size; } ;
typedef  TYPE_3__ dmu_object_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_object_info (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 

__attribute__((used)) static int
get_prev_obsolete_spacemap_refcount(spa_t *spa)
{
	uint64_t prev_obj =
	    spa->spa_condensing_indirect_phys.scip_prev_obsolete_sm_object;
	if (prev_obj != 0) {
		dmu_object_info_t doi;
		VERIFY0(dmu_object_info(spa->spa_meta_objset, prev_obj, &doi));
		if (doi.doi_bonus_size == sizeof (space_map_phys_t)) {
			return (1);
		}
	}
	return (0);
}