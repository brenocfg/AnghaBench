#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  link; } ;
struct TYPE_6__ {int /*<<< orphan*/  link; } ;
struct TYPE_10__ {int /*<<< orphan*/  link; } ;
struct sway_view_child {TYPE_3__* impl; TYPE_2__ view_unmap; TYPE_1__ surface_destroy; TYPE_5__ surface_commit; TYPE_4__* view; scalar_t__ mapped; } ;
struct TYPE_9__ {int /*<<< orphan*/ * container; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* destroy ) (struct sway_view_child*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_view_child*) ; 
 int /*<<< orphan*/  stub1 (struct sway_view_child*) ; 
 int /*<<< orphan*/  view_child_damage (struct sway_view_child*,int) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

void view_child_destroy(struct sway_view_child *child) {
	if (child->mapped && child->view->container != NULL) {
		view_child_damage(child, true);
	}

	wl_list_remove(&child->surface_commit.link);
	wl_list_remove(&child->surface_destroy.link);
	wl_list_remove(&child->view_unmap.link);

	if (child->impl && child->impl->destroy) {
		child->impl->destroy(child);
	} else {
		free(child);
	}
}