#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  void* boolean_t ;
struct TYPE_3__ {void* can_be_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int EEXIST ; 
 int FREAD ; 
 int /*<<< orphan*/  FTAG ; 
 int FWRITE ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_IMPORT_NORMAL ; 
 int /*<<< orphan*/  ZFS_IMPORT_SKIP_MMP ; 
 int /*<<< orphan*/  ZPOOL_PROP_READONLY ; 
 int /*<<< orphan*/  dmu_objset_register_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,...) ; 
 TYPE_1__ g_importargs ; 
 int /*<<< orphan*/  g_pool ; 
 void* g_readonly ; 
 int /*<<< orphan*/  kernel_init (int) ; 
 int /*<<< orphan*/  libzpool_config_ops ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_import (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  space_delta_cb ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  zfeature_checks_disable ; 
 int zpool_find_config (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_prop_to_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zhack_import(char *target, boolean_t readonly)
{
	nvlist_t *config;
	nvlist_t *props;
	int error;

	kernel_init(readonly ? FREAD : (FREAD | FWRITE));

	dmu_objset_register_type(DMU_OST_ZFS, space_delta_cb);

	g_readonly = readonly;
	g_importargs.can_be_active = readonly;
	g_pool = strdup(target);

	error = zpool_find_config(NULL, target, &config, &g_importargs,
	    &libzpool_config_ops);
	if (error)
		fatal(NULL, FTAG, "cannot import '%s'", target);

	props = NULL;
	if (readonly) {
		VERIFY(nvlist_alloc(&props, NV_UNIQUE_NAME, 0) == 0);
		VERIFY(nvlist_add_uint64(props,
		    zpool_prop_to_name(ZPOOL_PROP_READONLY), 1) == 0);
	}

	zfeature_checks_disable = B_TRUE;
	error = spa_import(target, config, props,
	    (readonly ?  ZFS_IMPORT_SKIP_MMP : ZFS_IMPORT_NORMAL));
	zfeature_checks_disable = B_FALSE;
	if (error == EEXIST)
		error = 0;

	if (error)
		fatal(NULL, FTAG, "can't import '%s': %s", target,
		    strerror(error));
}