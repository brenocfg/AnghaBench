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
 int /*<<< orphan*/  ZPOOL_SCRIPTS_DIR ; 
 int asprintf (char**,char*,char const*,...) ; 
 char* getenv (char*) ; 
 char* strdup (char const*) ; 

char *
zpool_get_cmd_search_path(void)
{
	const char *env;
	char *sp = NULL;

	env = getenv("ZPOOL_SCRIPTS_PATH");
	if (env != NULL)
		return (strdup(env));

	env = getenv("HOME");
	if (env != NULL) {
		if (asprintf(&sp, "%s/.zpool.d:%s",
		    env, ZPOOL_SCRIPTS_DIR) != -1) {
			return (sp);
		}
	}

	if (asprintf(&sp, "%s", ZPOOL_SCRIPTS_DIR) != -1)
		return (sp);

	return (NULL);
}