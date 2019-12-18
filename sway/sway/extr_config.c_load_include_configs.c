#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char** we_wordv; size_t we_wordc; } ;
typedef  TYPE_1__ wordexp_t ;
struct swaynag_instance {int dummy; } ;
struct sway_config {int /*<<< orphan*/  current_config_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 scalar_t__ chdir (char const*) ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_include_config (char*,char const*,struct sway_config*,struct swaynag_instance*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wordexp (char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

void load_include_configs(const char *path, struct sway_config *config,
		struct swaynag_instance *swaynag) {
	char *wd = getcwd(NULL, 0);
	char *parent_path = strdup(config->current_config_path);
	const char *parent_dir = dirname(parent_path);

	if (chdir(parent_dir) < 0) {
		sway_log(SWAY_ERROR, "failed to change working directory");
		goto cleanup;
	}

	wordexp_t p;
	if (wordexp(path, &p, 0) == 0) {
		char **w = p.we_wordv;
		size_t i;
		for (i = 0; i < p.we_wordc; ++i) {
			load_include_config(w[i], parent_dir, config, swaynag);
		}
		wordfree(&p);
	}

	// Attempt to restore working directory before returning.
	if (chdir(wd) < 0) {
		sway_log(SWAY_ERROR, "failed to change working directory");
	}
cleanup:
	free(parent_path);
	free(wd);
}