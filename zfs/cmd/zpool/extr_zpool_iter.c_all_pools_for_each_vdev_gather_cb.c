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

/* Variables and functions */
 int for_each_vdev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  for_each_vdev_run_cb ; 

__attribute__((used)) static int
all_pools_for_each_vdev_gather_cb(zpool_handle_t *zhp, void *cb_vcdl)
{
	return (for_each_vdev(zhp, for_each_vdev_run_cb, cb_vcdl));
}