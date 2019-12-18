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
typedef  int /*<<< orphan*/  paths ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_INFO ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  log_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void log_distro(void) {
	const char *paths[] = {
		"/etc/lsb-release",
		"/etc/os-release",
		"/etc/debian_version",
		"/etc/redhat-release",
		"/etc/gentoo-release",
	};
	for (size_t i = 0; i < sizeof(paths) / sizeof(char *); ++i) {
		FILE *f = fopen(paths[i], "r");
		if (f) {
			sway_log(SWAY_INFO, "Contents of %s:", paths[i]);
			log_file(f);
			fclose(f);
		}
	}
}