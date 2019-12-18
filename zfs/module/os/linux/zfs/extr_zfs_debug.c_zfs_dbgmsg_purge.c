#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int zdm_size; } ;
typedef  TYPE_1__ zfs_dbgmsg_t ;
struct TYPE_6__ {int /*<<< orphan*/  pl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 TYPE_1__* list_remove_head (int /*<<< orphan*/ *) ; 
 int zfs_dbgmsg_size ; 
 TYPE_2__ zfs_dbgmsgs ; 

__attribute__((used)) static void
zfs_dbgmsg_purge(int max_size)
{
	while (zfs_dbgmsg_size > max_size) {
		zfs_dbgmsg_t *zdm = list_remove_head(&zfs_dbgmsgs.pl_list);
		if (zdm == NULL)
			return;

		int size = zdm->zdm_size;
		kmem_free(zdm, size);
		zfs_dbgmsg_size -= size;
	}
}