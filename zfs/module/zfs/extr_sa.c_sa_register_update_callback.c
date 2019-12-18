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
typedef  int /*<<< orphan*/  sa_update_cb_t ;
struct TYPE_6__ {TYPE_1__* os_sa; } ;
typedef  TYPE_2__ objset_t ;
struct TYPE_5__ {int /*<<< orphan*/  sa_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_register_update_callback_locked (TYPE_2__*,int /*<<< orphan*/ *) ; 

void
sa_register_update_callback(objset_t *os, sa_update_cb_t *func)
{

	mutex_enter(&os->os_sa->sa_lock);
	sa_register_update_callback_locked(os, func);
	mutex_exit(&os->os_sa->sa_lock);
}