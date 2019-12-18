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
struct TYPE_2__ {int /*<<< orphan*/  force; scalar_t__ hardforce; } ;
typedef  TYPE_1__ export_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  history_str ; 
 int /*<<< orphan*/  log_history ; 
 scalar_t__ zpool_disable_datasets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_export (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_export_force (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zpool_export_one(zpool_handle_t *zhp, void *data)
{
	export_cbdata_t *cb = data;

	if (zpool_disable_datasets(zhp, cb->force) != 0)
		return (1);

	/* The history must be logged as part of the export */
	log_history = B_FALSE;

	if (cb->hardforce) {
		if (zpool_export_force(zhp, history_str) != 0)
			return (1);
	} else if (zpool_export(zhp, cb->force, history_str) != 0) {
		return (1);
	}

	return (0);
}