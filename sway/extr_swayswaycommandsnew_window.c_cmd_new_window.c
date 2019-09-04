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
struct TYPE_2__ {scalar_t__ reading; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_INFO ; 
 struct cmd_results* cmd_default_border (int,char**) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  config_add_swaynag_warning (char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

struct cmd_results *cmd_new_window(int argc, char **argv) {
	sway_log(SWAY_INFO, "Warning: new_window is deprecated. "
		"Use default_border instead.");
	if (config->reading) {
		config_add_swaynag_warning("new_window is deprecated. "
			"Use default_border instead.");
	}
	return cmd_default_border(argc, argv);
}