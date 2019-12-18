#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t vdev_ms_shift; int /*<<< orphan*/ ** vdev_ms; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_7__ {size_t sme_offset; size_t sme_vdev; scalar_t__ sme_type; scalar_t__ sme_run; } ;
typedef  TYPE_2__ space_map_entry_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  metaslab_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ SM_ALLOC ; 
 scalar_t__ SM_FREE ; 
 size_t metaslab_unflushed_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_1__*) ; 
 TYPE_1__* vdev_lookup_top (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
count_unflushed_space_cb(spa_t *spa, space_map_entry_t *sme,
    uint64_t txg, void *arg)
{
	int64_t *ualloc_space = arg;

	uint64_t offset = sme->sme_offset;
	uint64_t vdev_id = sme->sme_vdev;

	vdev_t *vd = vdev_lookup_top(spa, vdev_id);
	if (!vdev_is_concrete(vd))
		return (0);

	metaslab_t *ms = vd->vdev_ms[offset >> vd->vdev_ms_shift];
	ASSERT(sme->sme_type == SM_ALLOC || sme->sme_type == SM_FREE);

	if (txg < metaslab_unflushed_txg(ms))
		return (0);

	if (sme->sme_type == SM_ALLOC)
		*ualloc_space += sme->sme_run;
	else
		*ualloc_space -= sme->sme_run;

	return (0);
}