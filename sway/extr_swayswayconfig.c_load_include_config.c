#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct swaynag_instance {int dummy; } ;
struct sway_config {char* current_config_path; TYPE_1__* config_chain; } ;
struct TYPE_3__ {int length; char** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*,int) ; 
 int /*<<< orphan*/  load_config (char*,struct sway_config*,struct swaynag_instance*) ; 
 char* malloc (int) ; 
 char* realpath (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool load_include_config(const char *path, const char *parent_dir,
		struct sway_config *config, struct swaynag_instance *swaynag) {
	// save parent config
	const char *parent_config = config->current_config_path;

	char *full_path;
	int len = strlen(path);
	if (len >= 1 && path[0] != '/') {
		len = len + strlen(parent_dir) + 2;
		full_path = malloc(len * sizeof(char));
		if (!full_path) {
			sway_log(SWAY_ERROR,
				"Unable to allocate full path to included config");
			return false;
		}
		snprintf(full_path, len, "%s/%s", parent_dir, path);
	} else {
		full_path = strdup(path);
	}

	char *real_path = realpath(full_path, NULL);
	free(full_path);

	if (real_path == NULL) {
		sway_log(SWAY_DEBUG, "%s not found.", path);
		return false;
	}

	// check if config has already been included
	int j;
	for (j = 0; j < config->config_chain->length; ++j) {
		char *old_path = config->config_chain->items[j];
		if (strcmp(real_path, old_path) == 0) {
			sway_log(SWAY_DEBUG,
				"%s already included once, won't be included again.",
				real_path);
			free(real_path);
			return false;
		}
	}

	config->current_config_path = real_path;
	list_add(config->config_chain, real_path);
	int index = config->config_chain->length - 1;

	if (!load_config(real_path, config, swaynag)) {
		free(real_path);
		config->current_config_path = parent_config;
		list_del(config->config_chain, index);
		return false;
	}

	// restore current_config_path
	config->current_config_path = parent_config;
	return true;
}