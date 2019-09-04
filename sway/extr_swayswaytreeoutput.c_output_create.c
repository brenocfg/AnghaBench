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
struct wlr_output {int /*<<< orphan*/  subpixel; struct sway_output* data; } ;
struct TYPE_5__ {void* workspaces; } ;
struct TYPE_4__ {int /*<<< orphan*/  destroy; } ;
struct sway_output {TYPE_2__ current; void* workspaces; int /*<<< orphan*/  link; TYPE_1__ events; int /*<<< orphan*/  detected_subpixel; struct wlr_output* wlr_output; int /*<<< orphan*/  node; } ;
struct TYPE_6__ {int /*<<< orphan*/  all_outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_OUTPUT ; 
 struct sway_output* calloc (int,int) ; 
 void* create_list () ; 
 int /*<<< orphan*/  node_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sway_output*) ; 
 TYPE_3__* root ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_init (int /*<<< orphan*/ *) ; 

struct sway_output *output_create(struct wlr_output *wlr_output) {
	struct sway_output *output = calloc(1, sizeof(struct sway_output));
	node_init(&output->node, N_OUTPUT, output);
	output->wlr_output = wlr_output;
	wlr_output->data = output;
	output->detected_subpixel = wlr_output->subpixel;

	wl_signal_init(&output->events.destroy);

	wl_list_insert(&root->all_outputs, &output->link);

	output->workspaces = create_list();
	output->current.workspaces = create_list();

	return output;
}