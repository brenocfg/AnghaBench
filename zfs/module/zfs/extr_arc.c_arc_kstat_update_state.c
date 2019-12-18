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
struct TYPE_8__ {void* ui64; } ;
struct TYPE_9__ {TYPE_1__ value; } ;
typedef  TYPE_2__ kstat_named_t ;
struct TYPE_10__ {int /*<<< orphan*/ * arcs_esize; int /*<<< orphan*/  arcs_size; } ;
typedef  TYPE_3__ arc_state_t ;

/* Variables and functions */
 size_t ARC_BUFC_DATA ; 
 size_t ARC_BUFC_METADATA ; 
 void* zfs_refcount_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arc_kstat_update_state(arc_state_t *state, kstat_named_t *size,
    kstat_named_t *evict_data, kstat_named_t *evict_metadata)
{
	size->value.ui64 = zfs_refcount_count(&state->arcs_size);
	evict_data->value.ui64 =
	    zfs_refcount_count(&state->arcs_esize[ARC_BUFC_DATA]);
	evict_metadata->value.ui64 =
	    zfs_refcount_count(&state->arcs_esize[ARC_BUFC_METADATA]);
}