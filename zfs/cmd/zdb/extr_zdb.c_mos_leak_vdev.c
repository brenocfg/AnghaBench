#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ vic_births_object; scalar_t__ vic_mapping_object; } ;
struct TYPE_15__ {scalar_t__ vdev_dtl_object; scalar_t__ vdev_ms_array; scalar_t__ vdev_leaf_zap; size_t vdev_ms_count; scalar_t__ vdev_top_zap; size_t vdev_children; struct TYPE_15__** vdev_child; TYPE_7__** vdev_ms; TYPE_5__* vdev_obsolete_sm; TYPE_4__* vdev_indirect_mapping; TYPE_2__* vdev_checkpoint_sm; TYPE_1__ vdev_indirect_config; } ;
typedef  TYPE_6__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_16__ {int /*<<< orphan*/  ms_sm; } ;
typedef  TYPE_7__ metaslab_t ;
struct TYPE_14__ {scalar_t__ sm_object; } ;
struct TYPE_13__ {TYPE_3__* vim_phys; } ;
struct TYPE_12__ {scalar_t__ vimp_counts_object; } ;
struct TYPE_11__ {scalar_t__ sm_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  mos_leak_vdev_top_zap (TYPE_6__*) ; 
 int /*<<< orphan*/  mos_obj_refd (scalar_t__) ; 
 scalar_t__ space_map_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mos_leak_vdev(vdev_t *vd)
{
	mos_obj_refd(vd->vdev_dtl_object);
	mos_obj_refd(vd->vdev_ms_array);
	mos_obj_refd(vd->vdev_indirect_config.vic_births_object);
	mos_obj_refd(vd->vdev_indirect_config.vic_mapping_object);
	mos_obj_refd(vd->vdev_leaf_zap);
	if (vd->vdev_checkpoint_sm != NULL)
		mos_obj_refd(vd->vdev_checkpoint_sm->sm_object);
	if (vd->vdev_indirect_mapping != NULL) {
		mos_obj_refd(vd->vdev_indirect_mapping->
		    vim_phys->vimp_counts_object);
	}
	if (vd->vdev_obsolete_sm != NULL)
		mos_obj_refd(vd->vdev_obsolete_sm->sm_object);

	for (uint64_t m = 0; m < vd->vdev_ms_count; m++) {
		metaslab_t *ms = vd->vdev_ms[m];
		mos_obj_refd(space_map_object(ms->ms_sm));
	}

	if (vd->vdev_top_zap != 0) {
		mos_obj_refd(vd->vdev_top_zap);
		mos_leak_vdev_top_zap(vd);
	}

	for (uint64_t c = 0; c < vd->vdev_children; c++) {
		mos_leak_vdev(vd->vdev_child[c]);
	}
}