#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  children; } ;
struct TYPE_4__ {int destroying; scalar_t__ ntxnrefs; } ;
struct sway_container {TYPE_3__* view; int /*<<< orphan*/  marks_urgent; int /*<<< orphan*/  marks_unfocused; int /*<<< orphan*/  marks_focused_inactive; int /*<<< orphan*/  marks_focused; int /*<<< orphan*/  marks; int /*<<< orphan*/  outputs; TYPE_2__ current; int /*<<< orphan*/  children; int /*<<< orphan*/  title_urgent; int /*<<< orphan*/  title_unfocused; int /*<<< orphan*/  title_focused_inactive; int /*<<< orphan*/  title_focused; struct sway_container* formatted_title; struct sway_container* title; TYPE_1__ node; } ;
struct TYPE_6__ {scalar_t__ destroying; struct sway_container* container; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_container*) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free_items_and_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 
 int /*<<< orphan*/  view_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  wlr_texture_destroy (int /*<<< orphan*/ ) ; 

void container_destroy(struct sway_container *con) {
	if (!sway_assert(con->node.destroying,
				"Tried to free container which wasn't marked as destroying")) {
		return;
	}
	if (!sway_assert(con->node.ntxnrefs == 0, "Tried to free container "
				"which is still referenced by transactions")) {
		return;
	}
	free(con->title);
	free(con->formatted_title);
	wlr_texture_destroy(con->title_focused);
	wlr_texture_destroy(con->title_focused_inactive);
	wlr_texture_destroy(con->title_unfocused);
	wlr_texture_destroy(con->title_urgent);
	list_free(con->children);
	list_free(con->current.children);
	list_free(con->outputs);

	list_free_items_and_destroy(con->marks);
	wlr_texture_destroy(con->marks_focused);
	wlr_texture_destroy(con->marks_focused_inactive);
	wlr_texture_destroy(con->marks_unfocused);
	wlr_texture_destroy(con->marks_urgent);

	if (con->view) {
		if (con->view->container == con) {
			con->view->container = NULL;
		}
		if (con->view->destroying) {
			view_destroy(con->view);
		}
	}

	free(con);
}