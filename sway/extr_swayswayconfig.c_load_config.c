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
struct swaynag_instance {int dummy; } ;
struct sway_config {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  SWAY_INFO ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int read_config (int /*<<< orphan*/ *,struct sway_config*,struct swaynag_instance*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool load_config(const char *path, struct sway_config *config,
		struct swaynag_instance *swaynag) {
	if (path == NULL) {
		sway_log(SWAY_ERROR, "Unable to find a config file!");
		return false;
	}

	sway_log(SWAY_INFO, "Loading config from %s", path);

	struct stat sb;
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		sway_log(SWAY_ERROR, "%s is a directory not a config file", path);
		return false;
	}

	FILE *f = fopen(path, "r");
	if (!f) {
		sway_log(SWAY_ERROR, "Unable to open %s for reading", path);
		return false;
	}

	bool config_load_success = read_config(f, config, swaynag);
	fclose(f);

	if (!config_load_success) {
		sway_log(SWAY_ERROR, "Error(s) loading config!");
	}

	return true;
}