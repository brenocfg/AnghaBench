#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sway_view {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  destroy; } ;
struct TYPE_5__ {void* children; } ;
struct sway_container {float alpha; int /*<<< orphan*/  node; TYPE_2__ events; void* outputs; void* marks; TYPE_1__ current; void* children; struct sway_view* view; int /*<<< orphan*/  layout; } ;
struct TYPE_7__ {int /*<<< orphan*/  new_node; } ;
struct TYPE_8__ {TYPE_3__ events; } ;

/* Variables and functions */
 int /*<<< orphan*/  L_NONE ; 
 int /*<<< orphan*/  N_CONTAINER ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 struct sway_container* calloc (int,int) ; 
 void* create_list () ; 
 int /*<<< orphan*/  node_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sway_container*) ; 
 TYPE_4__* root ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl_signal_emit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_init (int /*<<< orphan*/ *) ; 

struct sway_container *container_create(struct sway_view *view) {
	struct sway_container *c = calloc(1, sizeof(struct sway_container));
	if (!c) {
		sway_log(SWAY_ERROR, "Unable to allocate sway_container");
		return NULL;
	}
	node_init(&c->node, N_CONTAINER, c);
	c->layout = L_NONE;
	c->view = view;
	c->alpha = 1.0f;

	if (!view) {
		c->children = create_list();
		c->current.children = create_list();
	}
	c->marks = create_list();
	c->outputs = create_list();

	wl_signal_init(&c->events.destroy);
	wl_signal_emit(&root->events.new_node, &c->node);

	return c;
}