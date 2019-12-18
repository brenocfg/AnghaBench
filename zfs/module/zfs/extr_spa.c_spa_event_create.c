#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
struct TYPE_4__ {int /*<<< orphan*/ * resource; } ;
typedef  TYPE_1__ sysevent_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  FM_SYSEVENT_CLASS ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_event_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

sysevent_t *
spa_event_create(spa_t *spa, vdev_t *vd, nvlist_t *hist_nvl, const char *name)
{
	sysevent_t *ev = NULL;
#ifdef _KERNEL
	nvlist_t *resource;

	resource = zfs_event_create(spa, vd, FM_SYSEVENT_CLASS, name, hist_nvl);
	if (resource) {
		ev = kmem_alloc(sizeof (sysevent_t), KM_SLEEP);
		ev->resource = resource;
	}
#endif
	return (ev);
}