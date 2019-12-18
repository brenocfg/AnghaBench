#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  size_t uint_t ;
typedef  void* uint64_t ;
struct TYPE_5__ {int cb_name_flags; scalar_t__ cb_print_status; int /*<<< orphan*/  cb_verbose; } ;
typedef  TYPE_1__ status_cbdata_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 char* VDEV_ALLOC_CLASS_LOGS ; 
 int VDEV_NAME_TYPE_ID ; 
 char const* VDEV_TYPE_INDIRECT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ALLOCATION_BIAS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_LOG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char const*) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  print_import_config (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_status_config (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* zpool_vdev_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
print_class_vdevs(zpool_handle_t *zhp, status_cbdata_t *cb, nvlist_t *nv,
    const char *class)
{
	uint_t c, children;
	nvlist_t **child;
	boolean_t printed = B_FALSE;

	assert(zhp != NULL || !cb->cb_verbose);

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_CHILDREN, &child,
	    &children) != 0)
		return;

	for (c = 0; c < children; c++) {
		uint64_t is_log = B_FALSE;
		char *bias = NULL;
		char *type = NULL;

		(void) nvlist_lookup_uint64(child[c], ZPOOL_CONFIG_IS_LOG,
		    &is_log);

		if (is_log) {
			bias = VDEV_ALLOC_CLASS_LOGS;
		} else {
			(void) nvlist_lookup_string(child[c],
			    ZPOOL_CONFIG_ALLOCATION_BIAS, &bias);
			(void) nvlist_lookup_string(child[c],
			    ZPOOL_CONFIG_TYPE, &type);
		}

		if (bias == NULL || strcmp(bias, class) != 0)
			continue;
		if (!is_log && strcmp(type, VDEV_TYPE_INDIRECT) == 0)
			continue;

		if (!printed) {
			(void) printf("\t%s\t\n", gettext(class));
			printed = B_TRUE;
		}

		char *name = zpool_vdev_name(g_zfs, zhp, child[c],
		    cb->cb_name_flags | VDEV_NAME_TYPE_ID);
		if (cb->cb_print_status)
			print_status_config(zhp, cb, name, child[c], 2,
			    B_FALSE);
		else
			print_import_config(cb, name, child[c], 2);
		free(name);
	}
}