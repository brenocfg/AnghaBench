#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * zrd_hdl; } ;
typedef  TYPE_1__ zfs_retire_data_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  FMD_API_VERSION ; 
 int /*<<< orphan*/  FMD_SLEEP ; 
 scalar_t__ fmd_hdl_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmd_hdl_setspecific (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* fmd_hdl_zalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmd_info ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libzfs_init () ; 

void
_zfs_retire_init(fmd_hdl_t *hdl)
{
	zfs_retire_data_t *zdp;
	libzfs_handle_t *zhdl;

	if ((zhdl = libzfs_init()) == NULL)
		return;

	if (fmd_hdl_register(hdl, FMD_API_VERSION, &fmd_info) != 0) {
		libzfs_fini(zhdl);
		return;
	}

	zdp = fmd_hdl_zalloc(hdl, sizeof (zfs_retire_data_t), FMD_SLEEP);
	zdp->zrd_hdl = zhdl;

	fmd_hdl_setspecific(hdl, zdp);
}