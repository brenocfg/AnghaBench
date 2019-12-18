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
struct TYPE_6__ {int /*<<< orphan*/  zri_cleanup_handlers; } ;
typedef  TYPE_1__ zcp_run_info_t ;
struct TYPE_7__ {int /*<<< orphan*/  zch_cleanup_arg; int /*<<< orphan*/  (* zch_cleanup_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ zcp_cleanup_handler_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 TYPE_2__* list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* zcp_run_info (int /*<<< orphan*/ *) ; 

void
zcp_cleanup(lua_State *state)
{
	zcp_run_info_t *ri = zcp_run_info(state);

	for (zcp_cleanup_handler_t *zch =
	    list_remove_head(&ri->zri_cleanup_handlers); zch != NULL;
	    zch = list_remove_head(&ri->zri_cleanup_handlers)) {
		zch->zch_cleanup_func(zch->zch_cleanup_arg);
		kmem_free(zch, sizeof (*zch));
	}
}