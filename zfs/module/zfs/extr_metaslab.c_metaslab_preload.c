#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_7__ {int /*<<< orphan*/  ms_lock; TYPE_1__* ms_group; } ;
typedef  TYPE_2__ metaslab_t ;
struct TYPE_8__ {int /*<<< orphan*/ * mc_spa; } ;
typedef  TYPE_3__ metaslab_class_t ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
struct TYPE_6__ {int /*<<< orphan*/  mg_lock; TYPE_3__* mg_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_load (TYPE_2__*) ; 
 int /*<<< orphan*/  metaslab_set_selected_txg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_syncing_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
metaslab_preload(void *arg)
{
	metaslab_t *msp = arg;
	metaslab_class_t *mc = msp->ms_group->mg_class;
	spa_t *spa = mc->mc_spa;
	fstrans_cookie_t cookie = spl_fstrans_mark();

	ASSERT(!MUTEX_HELD(&msp->ms_group->mg_lock));

	mutex_enter(&msp->ms_lock);
	(void) metaslab_load(msp);
	metaslab_set_selected_txg(msp, spa_syncing_txg(spa));
	mutex_exit(&msp->ms_lock);
	spl_fstrans_unmark(cookie);
}