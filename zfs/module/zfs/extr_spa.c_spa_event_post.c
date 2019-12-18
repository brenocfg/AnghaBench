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
struct TYPE_4__ {int /*<<< orphan*/  resource; } ;
typedef  TYPE_1__ sysevent_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zfs_zevent_post (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_zevent_post_cb ; 

void
spa_event_post(sysevent_t *ev)
{
#ifdef _KERNEL
	if (ev) {
		zfs_zevent_post(ev->resource, NULL, zfs_zevent_post_cb);
		kmem_free(ev, sizeof (*ev));
	}
#endif
}