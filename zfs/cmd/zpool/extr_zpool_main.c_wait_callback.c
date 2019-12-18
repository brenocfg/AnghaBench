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
typedef  int /*<<< orphan*/  zpool_wait_activity_t ;
typedef  int /*<<< orphan*/  zpool_handle_t ;

/* Variables and functions */
 int zpool_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wait_callback(zpool_handle_t *zhp, void *data)
{
	zpool_wait_activity_t *act = data;
	return (zpool_wait(zhp, *act));
}