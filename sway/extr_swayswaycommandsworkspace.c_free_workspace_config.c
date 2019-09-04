#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct workspace_config {int /*<<< orphan*/  outputs; struct workspace_config* workspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct workspace_config*) ; 
 int /*<<< orphan*/  list_free_items_and_destroy (int /*<<< orphan*/ ) ; 

void free_workspace_config(struct workspace_config *wsc) {
	free(wsc->workspace);
	list_free_items_and_destroy(wsc->outputs);
	free(wsc);
}