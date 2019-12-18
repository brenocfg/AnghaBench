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
struct workspace_config {TYPE_2__* outputs; } ;
struct sway_output {TYPE_1__* wlr_output; } ;
typedef  int /*<<< orphan*/  identifier ;
struct TYPE_4__ {int length; int /*<<< orphan*/ * items; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 struct sway_output* output_by_name_or_id (char const*) ; 
 int /*<<< orphan*/  output_get_identifier (char*,int,struct sway_output*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct workspace_config* workspace_find_config (char const*) ; 

__attribute__((used)) static bool workspace_valid_on_output(const char *output_name,
		const char *ws_name) {
	struct workspace_config *wsc = workspace_find_config(ws_name);
	char identifier[128];
	struct sway_output *output = output_by_name_or_id(output_name);
	if (!output) {
		return false;
	}
	output_name = output->wlr_output->name;
	output_get_identifier(identifier, sizeof(identifier), output);

	if (!wsc) {
		return true;
	}

	for (int i = 0; i < wsc->outputs->length; i++) {
		if (strcmp(wsc->outputs->items[i], "*") == 0 ||
				strcmp(wsc->outputs->items[i], output_name) == 0 ||
				strcmp(wsc->outputs->items[i], identifier) == 0) {
			return true;
		}
	}

	return false;
}