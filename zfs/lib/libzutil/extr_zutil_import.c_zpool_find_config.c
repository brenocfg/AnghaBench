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
typedef  int /*<<< orphan*/  pool_config_ops_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  importargs_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ pool_match (int /*<<< orphan*/ *,char*) ; 
 char* strdup (char const*) ; 
 char* strpbrk (char*,char*) ; 
 int /*<<< orphan*/ * zpool_search_import (void*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int
zpool_find_config(void *hdl, const char *target, nvlist_t **configp,
    importargs_t *args, const pool_config_ops_t *pco)
{
	nvlist_t *pools;
	nvlist_t *match = NULL;
	nvlist_t *config = NULL;
	char *name = NULL, *sepp = NULL;
	char sep = '\0';
	int count = 0;
	char *targetdup = strdup(target);

	*configp = NULL;

	if ((sepp = strpbrk(targetdup, "/@")) != NULL) {
		sep = *sepp;
		*sepp = '\0';
	}

	pools = zpool_search_import(hdl, args, pco);

	if (pools != NULL) {
		nvpair_t *elem = NULL;
		while ((elem = nvlist_next_nvpair(pools, elem)) != NULL) {
			VERIFY0(nvpair_value_nvlist(elem, &config));
			if (pool_match(config, targetdup)) {
				count++;
				if (match != NULL) {
					/* multiple matches found */
					continue;
				} else {
					match = config;
					name = nvpair_name(elem);
				}
			}
		}
	}

	if (count == 0) {
		free(targetdup);
		return (ENOENT);
	}

	if (count > 1) {
		free(targetdup);
		return (EINVAL);
	}

	*configp = match;
	free(targetdup);

	return (0);
}