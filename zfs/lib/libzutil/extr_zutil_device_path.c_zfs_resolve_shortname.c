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
 int ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const* const,char const*) ; 
 char* strdup (char*) ; 
 char* strtok (char*,char*) ; 
 char** zpool_default_search_paths (size_t*) ; 

int
zfs_resolve_shortname(const char *name, char *path, size_t len)
{
	int i, error = -1;
	char *dir, *env, *envdup;

	env = getenv("ZPOOL_IMPORT_PATH");
	errno = ENOENT;

	if (env) {
		envdup = strdup(env);
		dir = strtok(envdup, ":");
		while (dir && error) {
			(void) snprintf(path, len, "%s/%s", dir, name);
			error = access(path, F_OK);
			dir = strtok(NULL, ":");
		}
		free(envdup);
	} else {
		const char * const *zpool_default_import_path;
		size_t count;

		zpool_default_import_path = zpool_default_search_paths(&count);

		for (i = 0; i < count && error < 0; i++) {
			(void) snprintf(path, len, "%s/%s",
			    zpool_default_import_path[i], name);
			error = access(path, F_OK);
		}
	}

	return (error ? ENOENT : 0);
}