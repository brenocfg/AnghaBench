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
 int DEFAULT_IMPORT_PATH_SIZE ; 
 int ENOENT ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strtok (char*,char*) ; 
 char** zpool_default_import_path ; 

__attribute__((used)) static int
zfs_path_order(char *name, int *order)
{
	int i = 0, error = ENOENT;
	char *dir, *env, *envdup;

	env = getenv("ZPOOL_IMPORT_PATH");
	if (env) {
		envdup = strdup(env);
		dir = strtok(envdup, ":");
		while (dir) {
			if (strncmp(name, dir, strlen(dir)) == 0) {
				*order = i;
				error = 0;
				break;
			}
			dir = strtok(NULL, ":");
			i++;
		}
		free(envdup);
	} else {
		for (i = 0; i < DEFAULT_IMPORT_PATH_SIZE; i++) {
			if (strncmp(name, zpool_default_import_path[i],
			    strlen(zpool_default_import_path[i])) == 0) {
				*order = i;
				error = 0;
				break;
			}
		}
	}

	return (error);
}