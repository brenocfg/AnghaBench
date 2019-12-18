#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  uap_zhp; } ;
typedef  TYPE_1__ unavailpool_t ;
typedef  TYPE_1__ pendingdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_device_list ; 
 int /*<<< orphan*/  g_pool_list ; 
 int /*<<< orphan*/ * g_tpool ; 
 int /*<<< orphan*/  g_zfs_tid ; 
 int /*<<< orphan*/  g_zfshdl ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpool_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ ) ; 

void
zfs_slm_fini()
{
	unavailpool_t *pool;
	pendingdev_t *device;

	/* wait for zfs_enum_pools thread to complete */
	(void) pthread_join(g_zfs_tid, NULL);
	/* destroy the thread pool */
	if (g_tpool != NULL) {
		tpool_wait(g_tpool);
		tpool_destroy(g_tpool);
	}

	while ((pool = (list_head(&g_pool_list))) != NULL) {
		list_remove(&g_pool_list, pool);
		zpool_close(pool->uap_zhp);
		free(pool);
	}
	list_destroy(&g_pool_list);

	while ((device = (list_head(&g_device_list))) != NULL) {
		list_remove(&g_device_list, device);
		free(device);
	}
	list_destroy(&g_device_list);

	libzfs_fini(g_zfshdl);
}