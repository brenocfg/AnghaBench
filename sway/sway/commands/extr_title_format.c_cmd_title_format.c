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
struct sway_view {char* title_format; } ;
struct sway_container {struct sway_view* view; } ;
struct cmd_results {int dummy; } ;
struct TYPE_3__ {struct sway_container* container; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/  config_update_font_height (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_args (char**,int) ; 
 int /*<<< orphan*/  view_update_title (struct sway_view*,int) ; 

struct cmd_results *cmd_title_format(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "title_format", EXPECTED_AT_LEAST, 1))) {
		return error;
	}
	struct sway_container *container = config->handler_context.container;
	if (!container || !container->view) {
		return cmd_results_new(CMD_INVALID,
				"Only views can have a title_format");
	}
	struct sway_view *view = container->view;
	char *format = join_args(argv, argc);
	if (view->title_format) {
		free(view->title_format);
	}
	view->title_format = format;
	view_update_title(view, true);
	config_update_font_height(true);
	return cmd_results_new(CMD_SUCCESS, NULL);
}