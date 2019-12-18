#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * libzfs_ns_avlpool; int /*<<< orphan*/ * libzfs_ns_avl; } ;
typedef  TYPE_1__ libzfs_handle_t ;
struct TYPE_7__ {struct TYPE_7__* cn_name; int /*<<< orphan*/  cn_config; } ;
typedef  TYPE_2__ config_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_avl_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* uu_avl_teardown (int /*<<< orphan*/ *,void**) ; 

void
namespace_clear(libzfs_handle_t *hdl)
{
	if (hdl->libzfs_ns_avl) {
		config_node_t *cn;
		void *cookie = NULL;

		while ((cn = uu_avl_teardown(hdl->libzfs_ns_avl,
		    &cookie)) != NULL) {
			nvlist_free(cn->cn_config);
			free(cn->cn_name);
			free(cn);
		}

		uu_avl_destroy(hdl->libzfs_ns_avl);
		hdl->libzfs_ns_avl = NULL;
	}

	if (hdl->libzfs_ns_avlpool) {
		uu_avl_pool_destroy(hdl->libzfs_ns_avlpool);
		hdl->libzfs_ns_avlpool = NULL;
	}
}