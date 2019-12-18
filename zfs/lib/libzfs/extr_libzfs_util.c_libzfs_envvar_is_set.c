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
 char* getenv (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 int strnlen (char*,int) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
libzfs_envvar_is_set(char *envvar)
{
	char *env = getenv(envvar);
	if (env && (strtoul(env, NULL, 0) > 0 ||
	    (!strncasecmp(env, "YES", 3) && strnlen(env, 4) == 3) ||
	    (!strncasecmp(env, "ON", 2) && strnlen(env, 3) == 2)))
		return (1);

	return (0);
}