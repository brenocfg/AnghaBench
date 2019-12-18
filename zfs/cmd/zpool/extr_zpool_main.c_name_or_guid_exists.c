#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ poolguid; int /*<<< orphan*/ * poolname; } ;
typedef  TYPE_1__ target_exists_args_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
name_or_guid_exists(zpool_handle_t *zhp, void *data)
{
	target_exists_args_t *args = data;
	nvlist_t *config = zpool_get_config(zhp, NULL);
	int found = 0;

	if (config == NULL)
		return (0);

	if (args->poolname != NULL) {
		char *pool_name;

		verify(nvlist_lookup_string(config, ZPOOL_CONFIG_POOL_NAME,
		    &pool_name) == 0);
		if (strcmp(pool_name, args->poolname) == 0)
			found = 1;
	} else {
		uint64_t pool_guid;

		verify(nvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_GUID,
		    &pool_guid) == 0);
		if (pool_guid == args->poolguid)
			found = 1;
	}
	zpool_close(zhp);

	return (found);
}