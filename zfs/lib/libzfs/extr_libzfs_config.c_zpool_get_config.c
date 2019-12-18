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
struct TYPE_3__ {int /*<<< orphan*/ * zpool_config; int /*<<< orphan*/ * zpool_old_config; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */

nvlist_t *
zpool_get_config(zpool_handle_t *zhp, nvlist_t **oldconfig)
{
	if (oldconfig)
		*oldconfig = zhp->zpool_old_config;
	return (zhp->zpool_config);
}