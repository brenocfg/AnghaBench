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
 int /*<<< orphan*/  is_vdev_cb ; 

__attribute__((used)) static int
is_vdev(zpool_handle_t *zhp, void *cb_data)
{
	return (for_each_vdev(zhp, is_vdev_cb, cb_data));
}