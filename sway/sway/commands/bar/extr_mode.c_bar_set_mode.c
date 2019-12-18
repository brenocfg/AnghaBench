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
struct cmd_results {int dummy; } ;
struct bar_config {char* mode; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_bar; int /*<<< orphan*/  reading; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ipc_event_barconfig_update (struct bar_config*) ; 
 scalar_t__ strcasecmp (char*,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cmd_results *bar_set_mode(struct bar_config *bar, const char *mode) {
	char *old_mode = bar->mode;
	if (strcasecmp("toggle", mode) == 0 && !config->reading) {
		if (strcasecmp("dock", bar->mode) == 0) {
			bar->mode = strdup("hide");
		} else{
			bar->mode = strdup("dock");
		}
	} else if (strcasecmp("dock", mode) == 0) {
		bar->mode = strdup("dock");
	} else if (strcasecmp("hide", mode) == 0) {
		bar->mode = strdup("hide");
	} else if (strcasecmp("invisible", mode) == 0) {
		bar->mode = strdup("invisible");
	} else if (strcasecmp("overlay", mode) == 0) {
		bar->mode = strdup("overlay");
	} else {
		return cmd_results_new(CMD_INVALID, "Invalid value %s", mode);
	}

	if (strcmp(old_mode, bar->mode) != 0) {
		if (!config->current_bar) {
			ipc_event_barconfig_update(bar);
		}
		sway_log(SWAY_DEBUG, "Setting mode: '%s' for bar: %s", bar->mode, bar->id);
	}

	// free old mode
	free(old_mode);
	return NULL;
}