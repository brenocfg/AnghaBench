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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 char* BOGUS_SUFFIX ; 
 int ZFS_IMPORT_CHECKPOINT ; 
 int ZFS_IMPORT_MISSING_LOG ; 
 int ZFS_IMPORT_SKIP_MMP ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 int asprintf (char**,char*,char*,char*) ; 
 int /*<<< orphan*/  fatal (char*,char*,int) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int spa_get_stats (char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_import (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* strchr (char*,char) ; 
 char* strndup (char*,size_t) ; 
 int /*<<< orphan*/  zdb_set_skip_mmp (char*) ; 

__attribute__((used)) static char *
import_checkpointed_state(char *target, nvlist_t *cfg, char **new_path)
{
	int error = 0;
	char *poolname, *bogus_name = NULL;

	/* If the target is not a pool, the extract the pool name */
	char *path_start = strchr(target, '/');
	if (path_start != NULL) {
		size_t poolname_len = path_start - target;
		poolname = strndup(target, poolname_len);
	} else {
		poolname = target;
	}

	if (cfg == NULL) {
		zdb_set_skip_mmp(poolname);
		error = spa_get_stats(poolname, &cfg, NULL, 0);
		if (error != 0) {
			fatal("Tried to read config of pool \"%s\" but "
			    "spa_get_stats() failed with error %d\n",
			    poolname, error);
		}
	}

	if (asprintf(&bogus_name, "%s%s", poolname, BOGUS_SUFFIX) == -1)
		return (NULL);
	fnvlist_add_string(cfg, ZPOOL_CONFIG_POOL_NAME, bogus_name);

	error = spa_import(bogus_name, cfg, NULL,
	    ZFS_IMPORT_MISSING_LOG | ZFS_IMPORT_CHECKPOINT |
	    ZFS_IMPORT_SKIP_MMP);
	if (error != 0) {
		fatal("Tried to import pool \"%s\" but spa_import() failed "
		    "with error %d\n", bogus_name, error);
	}

	if (new_path != NULL && path_start != NULL) {
		if (asprintf(new_path, "%s%s", bogus_name, path_start) == -1) {
			if (path_start != NULL)
				free(poolname);
			return (NULL);
		}
	}

	if (target != poolname)
		free(poolname);

	return (bogus_name);
}