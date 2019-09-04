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
struct TYPE_2__ {char* font; int pango_markup; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  config_update_font_height (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_args (char**,int) ; 
 void* strdup (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

struct cmd_results *cmd_font(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "font", EXPECTED_AT_LEAST, 1))) {
		return error;
	}
	char *font = join_args(argv, argc);
	free(config->font);

	if (strncmp(font, "pango:", 6) == 0) {
		config->pango_markup = true;
		config->font = strdup(font + 6);
	} else {
		config->pango_markup = false;
		config->font = strdup(font);
	}

	free(font);
	config_update_font_height(true);
	return cmd_results_new(CMD_SUCCESS, NULL);
}