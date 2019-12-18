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
struct TYPE_8__ {int /*<<< orphan*/  notify; } ;
struct TYPE_5__ {int /*<<< orphan*/  new_node; } ;
struct sway_root {TYPE_4__ output_layout_change; TYPE_3__* output_layout; void* scratchpad; void* outputs; TYPE_1__ events; int /*<<< orphan*/  drag_icons; int /*<<< orphan*/  xwayland_unmanaged; int /*<<< orphan*/  all_outputs; int /*<<< orphan*/  node; } ;
struct TYPE_6__ {int /*<<< orphan*/  change; } ;
struct TYPE_7__ {TYPE_2__ events; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ROOT ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 struct sway_root* calloc (int,int) ; 
 void* create_list () ; 
 int /*<<< orphan*/  node_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sway_root*) ; 
 int /*<<< orphan*/  output_layout_handle_change ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  wl_signal_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* wlr_output_layout_create () ; 

struct sway_root *root_create(void) {
	struct sway_root *root = calloc(1, sizeof(struct sway_root));
	if (!root) {
		sway_log(SWAY_ERROR, "Unable to allocate sway_root");
		return NULL;
	}
	node_init(&root->node, N_ROOT, root);
	root->output_layout = wlr_output_layout_create();
	wl_list_init(&root->all_outputs);
#if HAVE_XWAYLAND
	wl_list_init(&root->xwayland_unmanaged);
#endif
	wl_list_init(&root->drag_icons);
	wl_signal_init(&root->events.new_node);
	root->outputs = create_list();
	root->scratchpad = create_list();

	root->output_layout_change.notify = output_layout_handle_change;
	wl_signal_add(&root->output_layout->events.change,
		&root->output_layout_change);
	return root;
}