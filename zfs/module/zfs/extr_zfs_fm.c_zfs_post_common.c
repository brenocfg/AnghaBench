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
typedef  int /*<<< orphan*/  vdev_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/ * zfs_event_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_zevent_post (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_zevent_post_cb ; 

__attribute__((used)) static void
zfs_post_common(spa_t *spa, vdev_t *vd, const char *type, const char *name,
    nvlist_t *aux)
{
#ifdef _KERNEL
	nvlist_t *resource;

	resource = zfs_event_create(spa, vd, type, name, aux);
	if (resource)
		zfs_zevent_post(resource, NULL, zfs_zevent_post_cb);
#endif
}