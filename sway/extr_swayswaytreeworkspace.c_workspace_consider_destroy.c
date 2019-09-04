#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {scalar_t__ output; TYPE_2__* floating; TYPE_1__* tiling; } ;
struct TYPE_4__ {scalar_t__ length; } ;
struct TYPE_3__ {scalar_t__ length; } ;

/* Variables and functions */
 struct sway_workspace* output_get_active_workspace (scalar_t__) ; 
 int /*<<< orphan*/  workspace_begin_destroy (struct sway_workspace*) ; 

void workspace_consider_destroy(struct sway_workspace *ws) {
	if (ws->tiling->length || ws->floating->length) {
		return;
	}
	if (ws->output && output_get_active_workspace(ws->output) == ws) {
		return;
	}
	workspace_begin_destroy(ws);
}