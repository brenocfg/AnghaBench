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
typedef  int /*<<< orphan*/  log_vars ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_INFO ; 
 int /*<<< orphan*/  getenv (char const*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_env(void) {
	const char *log_vars[] = {
		"LD_LIBRARY_PATH",
		"LD_PRELOAD",
		"PATH",
		"SWAYSOCK",
	};
	for (size_t i = 0; i < sizeof(log_vars) / sizeof(char *); ++i) {
		sway_log(SWAY_INFO, "%s=%s", log_vars[i], getenv(log_vars[i]));
	}
}