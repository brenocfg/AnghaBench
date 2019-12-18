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
struct TYPE_4__ {int /*<<< orphan*/  se_refcount; int /*<<< orphan*/  se_taskqid; struct dentry* se_root_dentry; int /*<<< orphan*/  se_objsetid; int /*<<< orphan*/ * se_spa; void* se_path; void* se_name; } ;
typedef  TYPE_1__ zfs_snapentry_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  TASKQID_INVALID ; 
 void* kmem_strdup (char*) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zfs_snapentry_t *
zfsctl_snapshot_alloc(char *full_name, char *full_path, spa_t *spa,
    uint64_t objsetid, struct dentry *root_dentry)
{
	zfs_snapentry_t *se;

	se = kmem_zalloc(sizeof (zfs_snapentry_t), KM_SLEEP);

	se->se_name = kmem_strdup(full_name);
	se->se_path = kmem_strdup(full_path);
	se->se_spa = spa;
	se->se_objsetid = objsetid;
	se->se_root_dentry = root_dentry;
	se->se_taskqid = TASKQID_INVALID;

	zfs_refcount_create(&se->se_refcount);

	return (se);
}