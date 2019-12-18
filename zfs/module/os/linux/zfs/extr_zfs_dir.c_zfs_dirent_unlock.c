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
struct TYPE_5__ {int /*<<< orphan*/  z_lock; TYPE_2__* z_dirlocks; int /*<<< orphan*/  z_name_lock; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_6__ {int dl_sharecnt; scalar_t__ dl_namesize; int /*<<< orphan*/  dl_cv; struct TYPE_6__* dl_name; struct TYPE_6__* dl_next; int /*<<< orphan*/  dl_namelock; TYPE_1__* dl_dzp; } ;
typedef  TYPE_2__ zfs_dirlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

void
zfs_dirent_unlock(zfs_dirlock_t *dl)
{
	znode_t *dzp = dl->dl_dzp;
	zfs_dirlock_t **prev_dl, *cur_dl;

	mutex_enter(&dzp->z_lock);

	if (!dl->dl_namelock)
		rw_exit(&dzp->z_name_lock);

	if (dl->dl_sharecnt > 1) {
		dl->dl_sharecnt--;
		mutex_exit(&dzp->z_lock);
		return;
	}
	prev_dl = &dzp->z_dirlocks;
	while ((cur_dl = *prev_dl) != dl)
		prev_dl = &cur_dl->dl_next;
	*prev_dl = dl->dl_next;
	cv_broadcast(&dl->dl_cv);
	mutex_exit(&dzp->z_lock);

	if (dl->dl_namesize != 0)
		kmem_free(dl->dl_name, dl->dl_namesize);
	cv_destroy(&dl->dl_cv);
	kmem_free(dl, sizeof (*dl));
}