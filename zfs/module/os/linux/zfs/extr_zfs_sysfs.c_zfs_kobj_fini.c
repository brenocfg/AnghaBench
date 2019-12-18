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
struct TYPE_4__ {scalar_t__ zko_child_count; int /*<<< orphan*/  zko_kobj; struct TYPE_4__* zko_children; } ;
typedef  TYPE_1__ zfs_mod_kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zfs_kobj_fini(zfs_mod_kobj_t *zkobj)
{
	/* finalize any child kobjects */
	if (zkobj->zko_child_count != 0) {
		ASSERT(zkobj->zko_children);
		for (int i = 0; i < zkobj->zko_child_count; i++)
			zfs_kobj_fini(&zkobj->zko_children[i]);
	}

	/* kobject_put() will call zfs_kobj_release() to release memory */
	kobject_del(&zkobj->zko_kobj);
	kobject_put(&zkobj->zko_kobj);
}