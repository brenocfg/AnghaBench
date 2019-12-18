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
struct sway_workspace {int /*<<< orphan*/  output_priority; } ;
struct sway_output {int dummy; } ;
typedef  int /*<<< orphan*/  identifier ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_get_identifier (char*,int,struct sway_output*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ workspace_output_get_priority (struct sway_workspace*,struct sway_output*) ; 

void workspace_output_add_priority(struct sway_workspace *workspace,
		struct sway_output *output) {
	if (workspace_output_get_priority(workspace, output) < 0) {
		char identifier[128];
		output_get_identifier(identifier, sizeof(identifier), output);
		list_add(workspace->output_priority, strdup(identifier));
	}
}