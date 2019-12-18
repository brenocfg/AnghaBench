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
typedef  int uint_t ;
typedef  scalar_t__ uint64_t ;
struct load_time_arg {scalar_t__ lt_guid; TYPE_1__* lt_time; scalar_t__ lt_found; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_2__ {scalar_t__ ertv_nsec; scalar_t__ ertv_sec; } ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOADED_TIME ; 
 int /*<<< orphan*/  ZPOOL_PROP_GUID ; 
 scalar_t__ nvlist_lookup_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__**,int*) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_prop_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zpool_find_load_time(zpool_handle_t *zhp, void *arg)
{
	struct load_time_arg *lta = arg;
	uint64_t pool_guid;
	uint64_t *tod;
	nvlist_t *config;
	uint_t nelem;

	if (lta->lt_found) {
		zpool_close(zhp);
		return (0);
	}

	pool_guid = zpool_get_prop_int(zhp, ZPOOL_PROP_GUID, NULL);
	if (pool_guid != lta->lt_guid) {
		zpool_close(zhp);
		return (0);
	}

	if ((config = zpool_get_config(zhp, NULL)) == NULL) {
		zpool_close(zhp);
		return (-1);
	}

	if (nvlist_lookup_uint64_array(config, ZPOOL_CONFIG_LOADED_TIME,
	    &tod, &nelem) == 0 && nelem == 2) {
		lta->lt_found = B_TRUE;
		lta->lt_time->ertv_sec = tod[0];
		lta->lt_time->ertv_nsec = tod[1];
	}

	zpool_close(zhp);

	return (0);
}