#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ vdev_path; } ;
typedef  TYPE_2__ spa_mmp_history_t ;
struct TYPE_7__ {int /*<<< orphan*/  pl_list; } ;
struct TYPE_9__ {unsigned int size; TYPE_1__ procfs_list; } ;
typedef  TYPE_3__ spa_history_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kmem_strfree (scalar_t__) ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_remove_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_mmp_history_truncate(spa_history_list_t *shl, unsigned int size)
{
	spa_mmp_history_t *smh;
	while (shl->size > size) {
		smh = list_remove_head(&shl->procfs_list.pl_list);
		if (smh->vdev_path)
			kmem_strfree(smh->vdev_path);
		kmem_free(smh, sizeof (spa_mmp_history_t));
		shl->size--;
	}

	if (size == 0)
		ASSERT(list_is_empty(&shl->procfs_list.pl_list));

}