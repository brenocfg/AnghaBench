#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int (* zpool_iter_f ) (int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  libzfs_pool_iter; int /*<<< orphan*/  libzfs_ns_avl; } ;
typedef  TYPE_1__ libzfs_handle_t ;
struct TYPE_10__ {int /*<<< orphan*/  cn_name; } ;
typedef  TYPE_2__ config_node_t ;

/* Variables and functions */
 scalar_t__ namespace_reload (TYPE_1__*) ; 
 TYPE_2__* uu_avl_first (int /*<<< orphan*/ ) ; 
 TYPE_2__* uu_avl_next (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ zpool_open_silent (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ zpool_skip_pool (int /*<<< orphan*/ ) ; 

int
zpool_iter(libzfs_handle_t *hdl, zpool_iter_f func, void *data)
{
	config_node_t *cn;
	zpool_handle_t *zhp;
	int ret;

	/*
	 * If someone makes a recursive call to zpool_iter(), we want to avoid
	 * refreshing the namespace because that will invalidate the parent
	 * context.  We allow recursive calls, but simply re-use the same
	 * namespace AVL tree.
	 */
	if (!hdl->libzfs_pool_iter && namespace_reload(hdl) != 0)
		return (-1);

	hdl->libzfs_pool_iter++;
	for (cn = uu_avl_first(hdl->libzfs_ns_avl); cn != NULL;
	    cn = uu_avl_next(hdl->libzfs_ns_avl, cn)) {

		if (zpool_skip_pool(cn->cn_name))
			continue;

		if (zpool_open_silent(hdl, cn->cn_name, &zhp) != 0) {
			hdl->libzfs_pool_iter--;
			return (-1);
		}

		if (zhp == NULL)
			continue;

		if ((ret = func(zhp, data)) != 0) {
			hdl->libzfs_pool_iter--;
			return (ret);
		}
	}
	hdl->libzfs_pool_iter--;

	return (0);
}