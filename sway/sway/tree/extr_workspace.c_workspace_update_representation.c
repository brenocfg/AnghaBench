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
struct sway_workspace {int /*<<< orphan*/ * representation; int /*<<< orphan*/  tiling; int /*<<< orphan*/  layout; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 size_t container_build_representation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ *,char*) ; 

void workspace_update_representation(struct sway_workspace *ws) {
	size_t len = container_build_representation(ws->layout, ws->tiling, NULL);
	free(ws->representation);
	ws->representation = calloc(len + 1, sizeof(char));
	if (!sway_assert(ws->representation, "Unable to allocate title string")) {
		return;
	}
	container_build_representation(ws->layout, ws->tiling, ws->representation);
}