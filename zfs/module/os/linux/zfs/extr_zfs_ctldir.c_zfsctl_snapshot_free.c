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
struct TYPE_4__ {int /*<<< orphan*/  se_path; int /*<<< orphan*/  se_name; int /*<<< orphan*/  se_refcount; } ;
typedef  TYPE_1__ zfs_snapentry_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kmem_strfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zfsctl_snapshot_free(zfs_snapentry_t *se)
{
	zfs_refcount_destroy(&se->se_refcount);
	kmem_strfree(se->se_name);
	kmem_strfree(se->se_path);

	kmem_free(se, sizeof (zfs_snapentry_t));
}