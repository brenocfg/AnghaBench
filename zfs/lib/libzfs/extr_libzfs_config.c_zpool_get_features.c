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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_FEATURE_STATS ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zpool_refresh_stats (int /*<<< orphan*/ *,scalar_t__*) ; 

nvlist_t *
zpool_get_features(zpool_handle_t *zhp)
{
	nvlist_t *config, *features;

	config = zpool_get_config(zhp, NULL);

	if (config == NULL || !nvlist_exists(config,
	    ZPOOL_CONFIG_FEATURE_STATS)) {
		int error;
		boolean_t missing = B_FALSE;

		error = zpool_refresh_stats(zhp, &missing);

		if (error != 0 || missing)
			return (NULL);

		config = zpool_get_config(zhp, NULL);
	}

	if (nvlist_lookup_nvlist(config, ZPOOL_CONFIG_FEATURE_STATS,
	    &features) != 0)
		return (NULL);

	return (features);
}