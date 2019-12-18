#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* rn_name; int /*<<< orphan*/  rn_labelpaths; scalar_t__ rn_order; int /*<<< orphan*/ * rn_hdl; int /*<<< orphan*/ * rn_avl; int /*<<< orphan*/ * rn_lock; scalar_t__ rn_vdev_guid; } ;
typedef  TYPE_1__ rdsk_node_t ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  libpc_handle_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ IMPORT_ORDER_SCAN_OFFSET ; 
 int asprintf (TYPE_1__**,char*,char const*,char const*) ; 
 scalar_t__ avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* zutil_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
zpool_find_import_scan_add_slice(libpc_handle_t *hdl, pthread_mutex_t *lock,
    avl_tree_t *cache, const char *path, const char *name, int order)
{
	avl_index_t where;
	rdsk_node_t *slice;

	slice = zutil_alloc(hdl, sizeof (rdsk_node_t));
	if (asprintf(&slice->rn_name, "%s/%s", path, name) == -1) {
		free(slice);
		return;
	}
	slice->rn_vdev_guid = 0;
	slice->rn_lock = lock;
	slice->rn_avl = cache;
	slice->rn_hdl = hdl;
	slice->rn_order = order + IMPORT_ORDER_SCAN_OFFSET;
	slice->rn_labelpaths = B_FALSE;

	pthread_mutex_lock(lock);
	if (avl_find(cache, slice, &where)) {
		free(slice->rn_name);
		free(slice);
	} else {
		avl_insert(cache, slice, where);
	}
	pthread_mutex_unlock(lock);
}