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
struct TYPE_5__ {int /*<<< orphan*/  zrd_hdl; } ;
typedef  TYPE_1__ zfs_retire_data_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  fmd_hdl_free (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__* fmd_hdl_getspecific (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_retire_clear_data (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
_zfs_retire_fini(fmd_hdl_t *hdl)
{
	zfs_retire_data_t *zdp = fmd_hdl_getspecific(hdl);

	if (zdp != NULL) {
		zfs_retire_clear_data(hdl, zdp);
		libzfs_fini(zdp->zrd_hdl);
		fmd_hdl_free(hdl, zdp, sizeof (zfs_retire_data_t));
	}
}