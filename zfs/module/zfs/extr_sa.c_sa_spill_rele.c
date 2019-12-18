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
struct TYPE_3__ {int /*<<< orphan*/  sa_lock; int /*<<< orphan*/ * sa_spill_tab; int /*<<< orphan*/ * sa_spill; int /*<<< orphan*/  sa_os; } ;
typedef  TYPE_1__ sa_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_idx_tab_rele (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
sa_spill_rele(sa_handle_t *hdl)
{
	mutex_enter(&hdl->sa_lock);
	if (hdl->sa_spill) {
		sa_idx_tab_rele(hdl->sa_os, hdl->sa_spill_tab);
		dmu_buf_rele(hdl->sa_spill, NULL);
		hdl->sa_spill = NULL;
		hdl->sa_spill_tab = NULL;
	}
	mutex_exit(&hdl->sa_lock);
}