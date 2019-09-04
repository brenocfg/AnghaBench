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
struct sway_workspace_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  output; int /*<<< orphan*/  tiling; int /*<<< orphan*/  floating; } ;
struct sway_workspace {TYPE_1__ current; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct sway_workspace_state*,int) ; 
 int /*<<< orphan*/  output_damage_whole (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apply_workspace_state(struct sway_workspace *ws,
		struct sway_workspace_state *state) {
	output_damage_whole(ws->current.output);
	list_free(ws->current.floating);
	list_free(ws->current.tiling);
	memcpy(&ws->current, state, sizeof(struct sway_workspace_state));
	output_damage_whole(ws->current.output);
}