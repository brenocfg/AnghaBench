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

/* Variables and functions */
 int /*<<< orphan*/  KILL_PROCESS_GROUP_GROUP_ENV_VAR ; 
 int /*<<< orphan*/  SUBREAPER_ENV_VAR ; 
 int /*<<< orphan*/  VERBOSITY_ENV_VAR ; 
 int /*<<< orphan*/  atoi (char*) ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_process_group ; 
 int /*<<< orphan*/  subreaper ; 
 int /*<<< orphan*/  verbosity ; 

int parse_env() {
#if HAS_SUBREAPER
	if (getenv(SUBREAPER_ENV_VAR) != NULL) {
		subreaper++;
	}
#endif

	if (getenv(KILL_PROCESS_GROUP_GROUP_ENV_VAR) != NULL) {
		kill_process_group++;
	}

	char* env_verbosity = getenv(VERBOSITY_ENV_VAR);
	if (env_verbosity != NULL) {
		verbosity = atoi(env_verbosity);
	}

	return 0;
}