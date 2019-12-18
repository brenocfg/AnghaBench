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
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_2__ {int /*<<< orphan*/ * cb_vdev_names; int /*<<< orphan*/  cb_name_flags; } ;
typedef  TYPE_1__ iostat_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* zpool_vdev_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_vdev_cb(zpool_handle_t *zhp, nvlist_t *nv, void *cb_data)
{
	iostat_cbdata_t *cb = cb_data;
	char *name = NULL;
	int ret = 0;

	name = zpool_vdev_name(g_zfs, zhp, nv, cb->cb_name_flags);

	if (strcmp(name, cb->cb_vdev_names[0]) == 0)
		ret = 1; /* match */
	free(name);

	return (ret);
}