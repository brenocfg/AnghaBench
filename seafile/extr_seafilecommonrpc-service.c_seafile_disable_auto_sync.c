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
struct TYPE_2__ {int /*<<< orphan*/  sync_mgr; } ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 TYPE_1__* seaf ; 
 int seaf_sync_manager_disable_auto_sync (int /*<<< orphan*/ ) ; 

int
seafile_disable_auto_sync (GError **error)
{
    return seaf_sync_manager_disable_auto_sync (seaf->sync_mgr);
}