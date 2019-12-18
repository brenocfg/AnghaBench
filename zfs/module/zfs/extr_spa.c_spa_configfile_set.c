#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  spa_config_list; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_8__ {int /*<<< orphan*/ * scd_path; } ;
typedef  TYPE_2__ spa_config_dirent_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  SPA_ASYNC_CONFIG_UPDATE ; 
 int /*<<< orphan*/  ZPOOL_PROP_CACHEFILE ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_head (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  spa_async_request (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* spa_config_path ; 
 void* spa_strdup (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  zpool_prop_to_name (int /*<<< orphan*/ ) ; 

void
spa_configfile_set(spa_t *spa, nvlist_t *nvp, boolean_t need_sync)
{
	char *cachefile;
	spa_config_dirent_t *dp;

	if (nvlist_lookup_string(nvp, zpool_prop_to_name(ZPOOL_PROP_CACHEFILE),
	    &cachefile) != 0)
		return;

	dp = kmem_alloc(sizeof (spa_config_dirent_t),
	    KM_SLEEP);

	if (cachefile[0] == '\0')
		dp->scd_path = spa_strdup(spa_config_path);
	else if (strcmp(cachefile, "none") == 0)
		dp->scd_path = NULL;
	else
		dp->scd_path = spa_strdup(cachefile);

	list_insert_head(&spa->spa_config_list, dp);
	if (need_sync)
		spa_async_request(spa, SPA_ASYNC_CONFIG_UPDATE);
}