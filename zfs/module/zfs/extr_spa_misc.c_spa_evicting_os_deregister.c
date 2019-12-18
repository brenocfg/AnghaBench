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
struct TYPE_3__ {int /*<<< orphan*/  spa_evicting_os_lock; int /*<<< orphan*/  spa_evicting_os_cv; int /*<<< orphan*/  spa_evicting_os_list; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
spa_evicting_os_deregister(spa_t *spa, objset_t *os)
{
	mutex_enter(&spa->spa_evicting_os_lock);
	list_remove(&spa->spa_evicting_os_list, os);
	cv_broadcast(&spa->spa_evicting_os_cv);
	mutex_exit(&spa->spa_evicting_os_lock);
}