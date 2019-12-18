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
typedef  int /*<<< orphan*/  zfs_process_func_t ;
struct TYPE_3__ {char const* dd_compare; char const* dd_new_devid; int /*<<< orphan*/  dd_found; int /*<<< orphan*/  dd_islabeled; int /*<<< orphan*/  dd_prop; int /*<<< orphan*/  dd_func; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ dev_data_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_DEVID ; 
 int /*<<< orphan*/  g_zfshdl ; 
 int /*<<< orphan*/  zfs_iter_pool ; 
 int /*<<< orphan*/  zpool_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static boolean_t
devid_iter(const char *devid, zfs_process_func_t func, boolean_t is_slice)
{
	dev_data_t data = { 0 };

	data.dd_compare = devid;
	data.dd_func = func;
	data.dd_prop = ZPOOL_CONFIG_DEVID;
	data.dd_found = B_FALSE;
	data.dd_islabeled = is_slice;
	data.dd_new_devid = devid;

	(void) zpool_iter(g_zfshdl, zfs_iter_pool, &data);

	return (data.dd_found);
}