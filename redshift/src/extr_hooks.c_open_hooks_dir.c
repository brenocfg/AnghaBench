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
struct passwd {char* pw_dir; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_HOOK_PATH ; 
 char* getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static DIR *
open_hooks_dir(char *hp)
{
	char *env;

	if ((env = getenv("XDG_CONFIG_HOME")) != NULL &&
	    env[0] != '\0') {
		snprintf(hp, MAX_HOOK_PATH, "%s/redshift/hooks", env);
		return opendir(hp);
	}

	if ((env = getenv("HOME")) != NULL &&
	    env[0] != '\0') {
		snprintf(hp, MAX_HOOK_PATH, "%s/.config/redshift/hooks", env);
		return opendir(hp);
	}

#ifndef _WIN32
	struct passwd *pwd = getpwuid(getuid());
	snprintf(hp, MAX_HOOK_PATH, "%s/.config/redshift/hooks", pwd->pw_dir);
	return opendir(hp);
#else
	return NULL;
#endif
}