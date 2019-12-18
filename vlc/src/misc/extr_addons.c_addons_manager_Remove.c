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
typedef  int /*<<< orphan*/  addons_manager_t ;
typedef  int /*<<< orphan*/  addon_uuid_t ;

/* Variables and functions */
 int addons_manager_Install (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

int addons_manager_Remove( addons_manager_t *p_manager, const addon_uuid_t uuid )
{
    return addons_manager_Install( p_manager, uuid );
}