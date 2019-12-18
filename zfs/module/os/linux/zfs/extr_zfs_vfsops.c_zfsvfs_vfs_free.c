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
struct TYPE_4__ {int /*<<< orphan*/ * vfs_mntpoint; } ;
typedef  TYPE_1__ vfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kmem_strfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zfsvfs_vfs_free(vfs_t *vfsp)
{
	if (vfsp != NULL) {
		if (vfsp->vfs_mntpoint != NULL)
			kmem_strfree(vfsp->vfs_mntpoint);

		kmem_free(vfsp, sizeof (vfs_t));
	}
}