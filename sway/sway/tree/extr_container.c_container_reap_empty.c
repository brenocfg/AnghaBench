#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {int dummy; } ;
struct sway_container {struct sway_container* parent; TYPE_1__* children; struct sway_workspace* workspace; scalar_t__ view; } ;
struct TYPE_2__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_begin_destroy (struct sway_container*) ; 
 int /*<<< orphan*/  workspace_consider_destroy (struct sway_workspace*) ; 

void container_reap_empty(struct sway_container *con) {
	if (con->view) {
		return;
	}
	struct sway_workspace *ws = con->workspace;
	while (con) {
		if (con->children->length) {
			return;
		}
		struct sway_container *parent = con->parent;
		container_begin_destroy(con);
		con = parent;
	}
	if (ws) {
		workspace_consider_destroy(ws);
	}
}