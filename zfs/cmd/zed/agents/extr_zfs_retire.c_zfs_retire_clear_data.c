#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* zrr_next; } ;
typedef  TYPE_1__ zfs_retire_repaired_t ;
struct TYPE_6__ {TYPE_1__* zrd_repaired; } ;
typedef  TYPE_2__ zfs_retire_data_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  fmd_hdl_free (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static void
zfs_retire_clear_data(fmd_hdl_t *hdl, zfs_retire_data_t *zdp)
{
	zfs_retire_repaired_t *zrp;

	while ((zrp = zdp->zrd_repaired) != NULL) {
		zdp->zrd_repaired = zrp->zrr_next;
		fmd_hdl_free(hdl, zrp, sizeof (zfs_retire_repaired_t));
	}
}