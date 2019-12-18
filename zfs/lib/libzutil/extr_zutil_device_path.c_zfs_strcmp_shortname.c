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
 int MAXPATHLEN ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int snprintf (char*,int,char*,char*,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdup (char*) ; 
 int strlen (char const*) ; 
 char* strtok (char*,char*) ; 
 int zfs_append_partition (char*,int) ; 
 char** zpool_default_search_paths (size_t*) ; 

__attribute__((used)) static int
zfs_strcmp_shortname(const char *name, const char *cmp_name, int wholedisk)
{
	int path_len, cmp_len, i = 0, error = ENOENT;
	char *dir, *env, *envdup = NULL;
	char path_name[MAXPATHLEN];
	const char * const *zpool_default_import_path;
	size_t count;

	zpool_default_import_path = zpool_default_search_paths(&count);

	cmp_len = strlen(cmp_name);
	env = getenv("ZPOOL_IMPORT_PATH");

	if (env) {
		envdup = strdup(env);
		dir = strtok(envdup, ":");
	} else {
		dir =  (char *)zpool_default_import_path[i];
	}

	while (dir) {
		/* Trim trailing directory slashes from ZPOOL_IMPORT_PATH */
		if (env) {
			while (dir[strlen(dir)-1] == '/')
				dir[strlen(dir)-1] = '\0';
		}

		path_len = snprintf(path_name, MAXPATHLEN, "%s/%s", dir, name);
		if (wholedisk)
			path_len = zfs_append_partition(path_name, MAXPATHLEN);

		if ((path_len == cmp_len) && strcmp(path_name, cmp_name) == 0) {
			error = 0;
			break;
		}

		if (env) {
			dir = strtok(NULL, ":");
		} else if (++i < count) {
			dir = (char *)zpool_default_import_path[i];
		} else {
			dir = NULL;
		}
	}

	if (env)
		free(envdup);

	return (error);
}